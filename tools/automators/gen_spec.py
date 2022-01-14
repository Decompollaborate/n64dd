#!/usr/bin/env python3

import argparse
import sys
import os

def main():
    parser = argparse.ArgumentParser(description="Generates a spec seg based on a csv file")
    parser.add_argument("path", help="Path to a csv file with the splits of a file")
    parser.add_argument("-v", "--version", help="Version (default: ne0)", default="ne0", choices={"ner", "ne0", "ne1", "np0", "ne2", "np1"})
    args = parser.parse_args()

    version = args.version

    with open(args.path) as f:
        head, tail = os.path.split(args.path)
        n = tail.split("files_")[1].split(".csv")[0]

        print("beginseg")
        print(f'    name "{n}"')

        section = "text"
        fold = "asm"

        for line in f:
            line = line.strip()
            line = line.split("#")[0]

            if len(line) == 0:
                continue

            offset, vram, filename = line.split(",")
            if filename.startswith("."):
                if filename == ".end":
                    continue
                print()
                if filename == ".text":
                    section = "text"
                    fold = "asm/text"
                    print("    // text")
                elif filename == ".data":
                    section = "data"
                    fold = "asm/data"
                    print("    // data")
                elif filename == ".rodata":
                    section = "rodata"
                    fold = "asm/data"
                    print("    // rodata")
                elif filename == ".bss":
                    section = "bss"
                    fold = "asm/data"
                    print("    // bss")
                continue

            if filename == "[PADDING]":
                print("    pad_text")
            else:
                print(f'    include "oot/{version}/build/{fold}/{n}/{filename}.{section}.o"')

        print("endseg")


if __name__ == "__main__":
    main()
