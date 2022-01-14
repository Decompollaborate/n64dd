#!/usr/bin/env python3

import argparse
import sys
import os

def getSyms(version):
    undefinedSymbols = dict()
    definedSymbols = {0x80000400: "entrypoint"}

    contextFolder = os.path.join("oot", version, "context")
    for file in os.listdir(contextFolder):
        contPath = os.path.join(contextFolder, file)
        with open(contPath) as f:
            for line in f:
                line = line.strip()
                row = line.split(",")

                if not line.startswith("symbol,") and not line.startswith("function,") and not line.startswith("fake_function,"):
                    continue

                vram = int(row[2], 16)
                name = row[3]
                if row[-1] == "True":
                    definedSymbols[vram] = name
                elif row[-1] == "False":
                    undefinedSymbols[vram] = name
                elif line.startswith("fake_function,"):
                    undefinedSymbols[vram] = name

    return undefinedSymbols, definedSymbols

def main():
    parser = argparse.ArgumentParser(description="Parses the context files outputed by the disassembler and prints the undefined symbols to the screen in a linker script compatible format")
    parser.add_argument("-v", "--version", help="Version (default: ne0)", default="ne0", choices={"ner", "ne0", "ne1", "np0", "ne2", "np1"})
    args = parser.parse_args()

    version = args.version

    undefinedSymbols, definedSymbols = getSyms(version)

    for vram, name in sorted(undefinedSymbols.items()):
        if vram in definedSymbols and name in definedSymbols.values():
            continue
        print(f"{name} = 0x{vram:08X};")

if __name__ == "__main__":
    main()
