#!/usr/bin/python3

from __future__ import annotations

import argparse
import os
import sys
import struct
from multiprocessing import Pool, cpu_count, Manager
from typing import Dict, List
import zlib


ROM_FILE_NAME_V = '{}_{}.z64'
FILE_TABLE_OFFSET = {
    "OOT": {
        "NER":        0x07430, # a.k.a. NN0 RC
        "NE0":        0x07430,
        "NE1":        0x07430,
        "NP0":        0x07950,
        "NE2":        0x07960,
        "NP1":        0x07950,
        "CJO":        0x07170,
        "CJM":        0x07170,
        "CEO":        0x07170,
        "CEM":        0x07170,
        "CPOD1":      0x12F70,
        "CPMD":       0x12F70,
        "CPOD2":      0x12F70,
        "CPO":        0x07170,
        "CPM":        0x07170,
        "CJC":        0x07170, # Zelda collection
        "IQS":        0x0B7A0,
        "IQT":        0x0B240,
        # "GATEWAY":    0x0AC80, # fake
    },

    "MM": {
        "NJ0":    0x1C110,
        "NJ1":    0x1C050,
        "NEK":    0x1AB50,
        "NE0":    0x1A500,
        "NP0":    0x1A650,
        "NPD":    0x24F60,
        "NP1":    0x1A8D0,
        "CE0":    0x1AE90,
        "CP0":    0x1AE90,
        "CJ0":    0x1AE90,
    },
}
FILE_TABLE_OFFSET["OOT"]["NJR"]   = FILE_TABLE_OFFSET["OOT"]["NER"]
FILE_TABLE_OFFSET["OOT"]["NJ0"]   = FILE_TABLE_OFFSET["OOT"]["NE0"]
FILE_TABLE_OFFSET["OOT"]["NJ1"]   = FILE_TABLE_OFFSET["OOT"]["NE1"]
FILE_TABLE_OFFSET["OOT"]["NJ2"]   = FILE_TABLE_OFFSET["OOT"]["NE2"]
FILE_TABLE_OFFSET["OOT"]["PAL WII 1.1"]  = FILE_TABLE_OFFSET["OOT"]["NP1"]

FILE_NAMES: Dict[str, Dict[str, List[str] | None]] = {
    "OOT": {
        "NER":        None,
        "NE0":        None,
        "NE1":        None,
        "NP0":        None,
        "NE2":        None,
        "NP1":        None,
        "CJO":        None,
        "CJM":        None,
        "CEO":        None,
        "CEM":        None,
        "CPOD1":      None,
        "CPMD":       None,
        "CPOD2":      None,
        "CPO":        None,
        "CPM":        None,
        "CJC":        None, # Zelda collector's edition
        "IQS":        None,
        "IQT":        None,
        # "GATEWAY":    None, # fake
    },

    "MM": {
        "NJ0":    None,
        "NJ1":    None,
        "NEK":    None,
        "NE0":    None,
        "NP0":    None,
        "NPD":    None,
        "NP1":    None,
        "CE0":    None,
        "CP0":    None,
        "CJ0":    None,
    },
}
FILE_NAMES["OOT"]["NJR"]  = FILE_NAMES["OOT"]["NER"]
FILE_NAMES["OOT"]["NJ0"]  = FILE_NAMES["OOT"]["NE0"]
FILE_NAMES["OOT"]["NJ1"]  = FILE_NAMES["OOT"]["NE1"]
FILE_NAMES["OOT"]["NJ2"]  = FILE_NAMES["OOT"]["NE2"]
FILE_NAMES["OOT"]["PAL WII 1.1"] = FILE_NAMES["OOT"]["NP1"]

romData: bytes = None
Edition = "" # "cpm"
Version = "" # "CPM"
OnlyDma = False
OnlyBuild = False


def readFile(filepath):
    with open(filepath) as f:
        return [x.strip() for x in f.readlines()]

def readFilelists():
    FILE_NAMES["OOT"]["CPMD"] = readFile("oot/filelists/filelist_pal_mq_dbg.txt")
    FILE_NAMES["OOT"]["CPM"]     = readFile("oot/filelists/filelist_pal_mq.txt")
    FILE_NAMES["OOT"]["CEM"]     = readFile("oot/filelists/filelist_usa_mq.txt")
    FILE_NAMES["OOT"]["NE0"]   = readFile("oot/filelists/filelist_ntsc_1.0.txt")
    FILE_NAMES["OOT"]["NP0"]    = readFile("oot/filelists/filelist_pal_1.0.txt")
    FILE_NAMES["OOT"]["CJC"]   = readFile("oot/filelists/filelist_jp_gc_ce.txt")
    FILE_NAMES["OOT"]["IQS"]    = readFile("oot/filelists/filelist_ique_cn.txt")

    FILE_NAMES["OOT"]["CJM"] = FILE_NAMES["OOT"]["CEM"]

    FILE_NAMES["OOT"]["CEO"] = FILE_NAMES["OOT"]["CJC"]
    FILE_NAMES["OOT"]["CJO"]  = FILE_NAMES["OOT"]["CEO"]
    FILE_NAMES["OOT"]["CPO"] = FILE_NAMES["OOT"]["CPM"]

    FILE_NAMES["OOT"]["NP1"] = FILE_NAMES["OOT"]["NP0"]

    FILE_NAMES["OOT"]["CPOD1"] = FILE_NAMES["OOT"]["CPMD"]
    FILE_NAMES["OOT"]["CPOD2"] = FILE_NAMES["OOT"]["CPMD"]

    FILE_NAMES["OOT"]["IQT"] = FILE_NAMES["OOT"]["IQS"]

    FILE_NAMES["OOT"]["NER"] = FILE_NAMES["OOT"]["NE0"]
    FILE_NAMES["OOT"]["NE1"] = FILE_NAMES["OOT"]["NE0"]
    FILE_NAMES["OOT"]["NE2"] = FILE_NAMES["OOT"]["NE0"]

    FILE_NAMES["OOT"]["NJR"]  = FILE_NAMES["OOT"]["NER"]
    FILE_NAMES["OOT"]["NJ0"]  = FILE_NAMES["OOT"]["NE0"]
    FILE_NAMES["OOT"]["NJ1"]  = FILE_NAMES["OOT"]["NE1"]
    FILE_NAMES["OOT"]["NJ2"]  = FILE_NAMES["OOT"]["NE2"]
    FILE_NAMES["OOT"]["PAL WII 1.1"] = FILE_NAMES["OOT"]["NP1"]

    FILE_NAMES["OOT"]["GATEWAY"] = FILE_NAMES["OOT"]["IQS"]

    # MM
    FILE_NAMES["MM"]["NJ0"] = readFile("mm/filelists/filelist_mm_jp_1.0.txt")
    FILE_NAMES["MM"]["NEK"] = readFile("mm/filelists/filelist_mm_usa_demo.txt")
    FILE_NAMES["MM"]["NE0"] = readFile("mm/filelists/filelist_mm_usa.txt")
    FILE_NAMES["MM"]["NPD"] = readFile("mm/filelists/filelist_mm_pal_dbg.txt")
    FILE_NAMES["MM"]["CE0"] = readFile("mm/filelists/filelist_mm_usa_gc.txt")
    FILE_NAMES["MM"]["CP0"] = readFile("mm/filelists/filelist_mm_pal_gc.txt")
    FILE_NAMES["MM"]["CJ0"] = readFile("mm/filelists/filelist_mm_jp_gc.txt")

    FILE_NAMES["MM"]["NJ1"]  = FILE_NAMES["MM"]["NJ0"]
    FILE_NAMES["MM"]["NP0"] = FILE_NAMES["MM"]["NPD"]
    FILE_NAMES["MM"]["NP1"] = FILE_NAMES["MM"]["NP0"]

def initialize_worker(rom_data: bytes, dmaTable: dict):
    global romData
    global globalDmaTable
    romData = rom_data
    globalDmaTable = dmaTable

def read_uint32_be(offset):
    return struct.unpack('>I', romData[offset:offset+4])[0]

def write_empty_output_file(name, size):
    try:
        with open(name, 'wb+') as f:
            # Write a 0 to pad to the right size
            f.seek(size-1)
            f.write(bytearray([0]))
    except IOError:
        print('failed to write file ' + name)
        sys.exit(1)

def write_output_file(name, offset, size):
    try:
        with open(name, 'wb') as f:
            f.write(romData[offset:offset+size])
    except IOError:
        print('failed to write file ' + name)
        sys.exit(1)


def decompressZlib(data: bytearray) -> bytearray:
    decomp = zlib.decompressobj(-zlib.MAX_WBITS)
    output = bytearray()
    output.extend(decomp.decompress(data))
    while decomp.unconsumed_tail:
        output.extend(decomp.decompress(decomp.unconsumed_tail))
    output.extend(decomp.flush())
    return output

def writeBytearrayToFile(filepath: str, array_of_bytes: bytearray):
    with open(filepath, mode="wb") as f:
       f.write(array_of_bytes)

def readFileAsBytearray(filepath: str) -> bytearray:
    if not os.path.exists(filepath):
        return bytearray(0)
    with open(filepath, mode="rb") as f:
        return bytearray(f.read())


def ExtractFunc(i):
    versionName = FILE_NAMES[Game][Version][i]
    if versionName == "":
        print(f"Skipping {i} because it doesn't have a name.")
        return
    filename = os.path.join(Basedir, Edition, "baserom", versionName)
    entryOffset = FILE_TABLE_OFFSET[Game][Version] + 16 * i

    virtStart = read_uint32_be(entryOffset + 0)
    virtEnd   = read_uint32_be(entryOffset + 4)
    physStart = read_uint32_be(entryOffset + 8)
    physEnd   = read_uint32_be(entryOffset + 12)

    deleted = False
    if physStart == 0xFFFFFFFF and physEnd == 0xFFFFFFFF: # file deleted
        if (virtEnd - virtStart) == 0:
            return
        # physStart = virtStart
        # physEnd = 0
        compressed = False
        deleted = True
        size = virtEnd - virtStart

    elif physEnd == 0:  # uncompressed
        compressed = False
        size = virtEnd - virtStart
    else:             # compressed
        compressed = True
        size = physEnd - physStart

    globalDmaTable[versionName].append(virtStart)
    globalDmaTable[versionName].append(virtEnd)
    globalDmaTable[versionName].append(physStart)
    globalDmaTable[versionName].append(physEnd)

    if OnlyDma:
        return

    print('Extracting ' + filename + " (0x%08X, 0x%08X)" % (virtStart, virtEnd))

    if deleted:
        write_empty_output_file(filename, size)
    else:
        write_output_file(filename, physStart, size)

    if compressed:
        # print(f"decompressing {filename}")
        if Edition in ("iqt", "iqs"):
            data = readFileAsBytearray(filename)
            decompressed = decompressZlib(data)
            writeBytearrayToFile(filename, decompressed)
        else:
            exit_code = os.system('tools/yaz0 -d ' + filename + ' ' + filename)
            if exit_code != 0:
                pass
                #os.remove(filename)
                # exit(exit_code)

#####################################################################

def printBuildData(rom_data: bytes):
    buildDataOffset = FILE_TABLE_OFFSET[Game][Version] - 16*3
    buildTeam = ""
    i = 0
    while rom_data[buildDataOffset + i] != 0:
        buildTeam += chr(rom_data[buildDataOffset + i])
        i += 1

    while rom_data[buildDataOffset + i] == 0:
        i += 1

    buildDate = ""
    while rom_data[buildDataOffset + i] != 0:
        buildDate += chr(rom_data[buildDataOffset + i])
        i += 1

    i += 1

    buildMakeOption = ""
    while rom_data[buildDataOffset + i] != 0:
        buildMakeOption += chr(rom_data[buildDataOffset + i])
        i += 1

    print("========================================")
    print(f"| Build team:   {buildTeam}".ljust(39) + "|")
    print(f"| Build date:   {buildDate}".ljust(39) + "|")
    #print(f"| Make Option:  {buildMakeOption}".ljust(39) + "|")
    print("========================================")

def writeDma(dmaTable):
    filetable = os.path.join(Basedir, Edition, "tables", "dma_addresses.csv")
    print(f"Creating {filetable}")
    with open(filetable, "w") as f:
        for filename, data in dmaTable.items():
            line = ",".join([filename] + list(map(lambda x: f"{x:X}", data)))
            if OnlyDma:
                print(line)
            f.write(line + "\n")

def extract_rom(j):
    print("Reading filelists...")
    readFilelists()

    file_names_table = FILE_NAMES[Game][Version]
    if file_names_table is None:
        print(f"'{Edition}' is not supported yet because the filelist is missing.")
        sys.exit(2)

    os.makedirs(os.path.join(Basedir, Edition, "baserom"), exist_ok=True)

    filename = os.path.join(Basedir, ROM_FILE_NAME_V.format(Basedir, Edition))

    # read baserom data
    try:
        with open(filename, 'rb') as f:
            rom_data = f.read()
    except IOError:
        print('Failed to read file ' + filename)
        sys.exit(1)

    if OnlyBuild:
        printBuildData(rom_data)
        sys.exit(0)

    if j:
        manager = Manager()
        dmaTable = manager.dict()
        for name in file_names_table:
            dmaTable[name] = manager.list()
    else:
        dmaTable = dict()
        for name in file_names_table:
            dmaTable[name] = list()

    # extract files
    if j:
        num_cores = cpu_count()
        print("Extracting rom with " + str(num_cores) + " CPU cores.")
        with Pool(num_cores, initialize_worker, (rom_data, dmaTable)) as p:
            p.map(ExtractFunc, range(len(file_names_table)))
    else:
        initialize_worker(rom_data, dmaTable)
        for i in range(len(file_names_table)):
            ExtractFunc(i)

    if not OnlyDma:
        printBuildData(rom_data)

    os.makedirs(os.path.join(Basedir, Edition, "tables"), exist_ok= True)

    writeDma(dmaTable)

def main():
    description = "Extracts files from the rom. Will try to read the rom 'version.z64', or 'baserom.z64' if that doesn't exist."

    edition_choices = {
        "oot": ", ".join(x.lower().replace(" ", "_") for x in FILE_TABLE_OFFSET["OOT"]),
        "mm": ", ".join(x.lower().replace(" ", "_") for x in FILE_TABLE_OFFSET["MM"]),
    }
    epilog = f"""\
Each `game` has different versions, and hence different edition options.
    For oot: {edition_choices["oot"]}
    For mm:  {edition_choices["mm"]}

For details on what these abbreviations mean, see the README.md.
    """
    parser = argparse.ArgumentParser(description=description, epilog=epilog, formatter_class=argparse.RawTextHelpFormatter)
    choices = ["oot", "mm"]
    parser.add_argument("game", help="Game to extract.", choices=choices)
    parser.add_argument("edition", help="Version of the game to extract.")
    parser.add_argument("-j", help="Enables multiprocessing.", action="store_true")
    parser.add_argument("--dma", help="Extract only the dma addresses", action="store_true")
    parser.add_argument("--build", help="Only print the build data", action="store_true")
    args = parser.parse_args()

    global Basedir
    global Game
    global Edition
    global Version
    global OnlyDma
    global OnlyBuild

    Basedir   = args.game
    Game      = args.game.upper()
    Edition   = args.edition
    Version   = Edition.upper().replace("_", " ")
    OnlyDma   = args.dma
    OnlyBuild = args.build

    if Edition not in edition_choices[args.game]:
        print(f"The selected edition '{Edition}' is not a valid option for the game '{args.game}'")
        exit(1)

    extract_rom(args.j)

if __name__ == "__main__":
    main()
