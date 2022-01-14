#!/usr/bin/env python3

import sys
import csv
import argparse
import struct

def printf(fmt, *args, **kwargs):
    print(fmt.format(*args), end="", **kwargs)

def fprintf(file, *args, **kwargs):
    printf(*args, file=file, **kwargs)


def constructSpec(dmadataFile, outFile):
    with open(dmadataFile, "r") as f:
        dmadata = list(csv.reader(f))
        # dmaTable = []
        # for entry in dmadata:
        #     dmaTable.append(entry)

        print("/*\n * ROM spec file\n */\n", file=outFile)

        i = 0
        while i < len(dmadata):
            entry = dmadata[i]

            print("beginseg", file=outFile)
            print("    name \"" + entry[0] + "\"", file=outFile)

            if int(entry[4],16) != 0:
                print("    compress", file=outFile)

            if ((int(entry[1],16) % 0x1000 == 0) and ((i == len(dmadata) - 1) or (int(dmadata[i+1][1],16) % 0x1000 == 0))):
                print("    romalign 0x1000", file=outFile)


            print("    include \"build/baserom/" + entry[0] + ".o\"", file=outFile )
            print("endseg", file=outFile)
            print("", file=outFile)
            i += 1

def main():
    description = "Construct a basic spec from dmadata"

    parser = argparse.ArgumentParser(description=description, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument("dmadataFile", help="dmadata file to read")
    parser.add_argument("--outFile", help="File to write to", default=sys.stdout)
    args = parser.parse_args()

    if args.outFile != sys.stdout:
        with open(args.outFile, "w") as f:
            constructSpec(args.dmadataFile, f)
    else:
        constructSpec(args.dmadataFile, args.outFile)


if __name__ == "__main__":
    main()

