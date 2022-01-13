#!/usr/bin/python3

from __future__ import annotations

import argparse

from py_mips_disasm.mips.Utils import *

from mips.MipsSplitEntry import readSplitsFromCsv

def split_fileSplits(game: str, seg: str):
    sections = ["text", "data", "rodata", "bss"]

    tablePerVersion = dict()

    for section in sections:
        csvPath = os.path.join(game, "tables", f"{seg}.{section}.csv")

        if not os.path.exists(csvPath):
            continue

        splits = readSplitsFromCsv(csvPath)
        # print(splits)

        for version, filesDict in splits.items():
            # print(version)

            if version == "":
                continue

            if version not in tablePerVersion:
                tablePerVersion[version] = dict()

            auxList = []

            for filename, splitDataList in filesDict.items():
                for splitData in splitDataList:
                    # print("\t", filename, splitData)
                    if splitData.offset < 0 or splitData.vram < 0 or splitData.filename == "":
                        continue
                    auxList.append((splitData.offset, splitData.vram, splitData.size, splitData.filename))

            if len(auxList) == 0:
                continue

            # fake extra to avoid problems
            auxList.append((0xFFFFFF, 0x80FFFFFF, 0, "end"))

            # Reading from the file may not be sorted by offset
            auxList.sort()

            tablePerVersion[version][section] = list()

            i = 0
            while i < len(auxList) - 1:
                offset, vram, size, filename = auxList[i]
                nextOffset, _, _, _ = auxList[i+1]

                end = offset + size
                if size <= 0:
                    end = nextOffset

                if end < nextOffset:
                    # Adds missing files
                    auxList.insert(i+1, (end, vram + (end - offset), -1, f"file_{end:06X}"))

                tablePerVersion[version][section].append((offset, vram, filename))

                i += 1


    for version, sectionedDict in tablePerVersion.items():
        sections = list(sectionedDict.keys())
        for i in range(len(sections)-1):
            currentSection = sections[i]
            nextSection = sections[i+1]
            lastOffsetCurrent = sectionedDict[currentSection][-1][0]
            firstOffsetNext = sectionedDict[nextSection][0][0]
            if lastOffsetCurrent == firstOffsetNext:
                del sectionedDict[currentSection][-1]

    for version, sectionedDict in tablePerVersion.items():
        isFirst = True
        dstFolder = os.path.join(game, version, "tables")
        os.makedirs(dstFolder, exist_ok=True)
        with open(os.path.join(dstFolder, f"files_{seg}.csv"), "w") as f:
            for section, data in sectionedDict.items():
                if isFirst:
                    isFirst = False
                else:
                    f.write("\n")

                f.write(f"offset,vram,.{section}\n")
                for row in data:
                    offset, vram, filename = row
                    f.writelines(f"{offset:X},{vram:X},{filename}\n")


def split_functions(game: str):
    csvPath = os.path.join(game, "tables", "functions.csv")

    tablePerVersion = dict()

    functions = readCsv(csvPath)
    header = functions[0][2:]
    for i in range(2, len(functions)):
        funcName, _, *data = functions[i]

        for headerIndex, version in enumerate(header):
            if version not in tablePerVersion:
                tablePerVersion[version] = []

            vram = data[headerIndex]
            if vram == "":
                continue

            tablePerVersion[version].append(f"{vram},{funcName}\n")

    for version, lines in tablePerVersion.items():
        dstFolder = os.path.join(game, version, "tables")
        os.makedirs(dstFolder, exist_ok=True)
        with open(os.path.join(dstFolder, "functions.csv"), "w") as f:
            f.writelines(lines)


def split_variables(game: str):
    csvPath = os.path.join(game, "tables", "variables.csv")

    tablePerVersion = dict()

    variables = readCsv(csvPath)
    header = variables[0][3:]
    for i in range(2, len(variables)):
        varName, type, _, *data = variables[i]

        for headerIndex, version in enumerate(header[::2]):
            if version not in tablePerVersion:
                tablePerVersion[version] = []

            # print(varName, version, data)
            vram, size = data[2*headerIndex : 2*headerIndex + 2]
            if vram == "":
                continue
            if size == "":
                size = "4"

            tablePerVersion[version].append(f"{vram},{varName},{type},0x{size}\n")

    for version, lines in tablePerVersion.items():
        dstFolder = os.path.join(game, version, "tables")
        os.makedirs(dstFolder, exist_ok=True)
        with open(os.path.join(dstFolder, "variables.csv"), "w") as f:
            f.writelines(lines)


def main():
    description = ""

    epilog = f"""\
    """
    parser = argparse.ArgumentParser(description=description, epilog=epilog, formatter_class=argparse.RawTextHelpFormatter)
    choices = ["oot", "mm"]
    parser.add_argument("game", help="Game to extract.", choices=choices)
    parser.add_argument("csv", help="") # TODO
    args = parser.parse_args()

    seg = os.path.split(args.csv)[-1].split('.')[0]

    if seg == "functions":
        split_functions(args.game)
    if seg == "variables":
        split_variables(args.game)
    else:
        split_fileSplits(args.game, seg)


if __name__ == "__main__":
    main()
