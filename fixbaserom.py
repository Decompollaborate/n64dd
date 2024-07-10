#!/usr/bin/env python3

from os import path
import argparse
import sys
import struct
import hashlib

CRC_VERSION = {
        # OoT
        "48ca05f4f7e96d83": ["OOT", "NER", "Nintendo 64 American \"0.9\""],
        "ec7011b77616d72b": ["OOT", "NE0", "Nintendo 64 American 1.0"],
        "d43da81f021e1e19": ["OOT", "NE1", "Nintendo 64 American 1.1"],
        "b044b569373c1985": ["OOT", "NP0", "Nintendo 64 PAL 1.0"],
        "693ba2aeb7f14e9f": ["OOT", "NE2", "Nintendo 64 American 1.2"],
        "b2055fbd0bab4e0c": ["OOT", "NP1", "Nintendo 64 PAL 1.1"],

        "f611f4bac584135c": ["OOT", "CJO", "GameCube Japanese"],
        "f43b45ba2f0e9b6f": ["OOT", "CJM", "GameCube Japanese Master Quest"],
        "f3dd35ba4152e075": ["OOT", "CEO", "GameCube American"],
        "f034001aae47ed06": ["OOT", "CEM", "GameCube American Master Quest"],
        "87121efe3149592c": ["OOT", "CPOD1", "GameCube PAL Debug (earlier build date)"],
        "917d18f669bc5453": ["OOT", "CPMD", "GameCube PAL Master Quest Debug"],
        "871e1c92509d8a96": ["OOT", "CPOD2", "GameCube PAL Debug (later build date)"],
        "09465ac3f8cb501b": ["OOT", "CPO", "GameCube PAL"],
        "1d4136f3af63eea9": ["OOT", "CPM", "GameCube PAL Master Quest"],
        "f7f52db82195e636": ["OOT", "CJC", "GameCube Japanese (Zelda Collection)"],

        "b1e1e07b051269dd": ["OOT", "IQS", "iQue Simplified Chinese"],
        "3d81fb3ebd843e34": ["OOT", "IQT", "iQue Traditional Chinese"],

        # MM
        "ec417312eb31de5f": ["MM", "NJ0", "Nintendo 64 Japanese 1.0"],
        "69ae04382c63f3f3": ["MM", "NJ1", "Nintendo 64 Japanese 1.1"],
        "bf79934539ff7a02": ["MM", "NEK", "Nintendo 64 American Kiosk Demo"],
        "5354631c03a2def0": ["MM", "NE0", "Nintendo 64 American"],
        "e97955c6bc338d38": ["MM", "NP0", "Nintendo 64 PAL 1.0"],
        "9fc385e53ecc05c7": ["MM", "NPD", "Nintendo 64 PAL Debug"],
        "0a5d8f8398c5371a": ["MM", "NP1", "Nintendo 64 PAL 1.1"],

        "b443eb084db31193": ["MM", "CE0", "GameCube American"],
        "6aecec4ff0924814": ["MM", "CP0", "GameCube PAL"],
        "8473d0c123120666": ["MM", "CJ0", "GameCube Japanese"],
}

VERSIONS_MD5S = {
    "OOT": {
        "NJR":            None,
        "NER":            "21f7b4a4ff463464bfc23498c1ab9da1", # a.k.a. NTSC 1.0 RC
        "NJ0":            "9f04c8e68534b870f707c247fa4b50fc",
        "NE0":            "5bd1fe107bf8106b2ab6650abecd54d6",
        "NJ1":            "1bf5f42b98c3e97948f01155f12e2d88",
        "NE1":            "721fdcc6f5f34be55c43a807f2a16af4",
        "NP0":            "e040de91a74b61e3201db0e2323f768a",
        "NJ2":            "2258052847bdd056c8406a9ef6427f13",
        "NE2":            "57a9719ad547c516342e1a15d5c28c3d",
        "NP1":            "d714580dd74c2c033f5e1b6dc0aeac77",
        "PAL WII 1.1":    None,
        "CJO":            "33fb7852c180b18ea0b9620b630f413f",
        "CJM":            "69895c5c78442260f6eafb2506dc482a",
        "CEO":            "cd09029edcfb7c097ac01986a0f83d3f",
        "CEM":            "da35577fe54579f6a266931cc75f512d",
        "CPOD1":          "ab1ca59d0039e3b34d82db650b54d7b9",
        "CPMD":           "f0b7f35375f9cc8ca1b2d59d78e35405",
        "CPOD2":          "3c10b67a76616ae2c162def7528724cf",
        "CPO":            "2c27b4e000e85fd78dbca551f1b1c965",
        "CPM":            "1618403427e4344a57833043db5ce3c3",
        "CJC":            "0c13e0449a28ea5b925cdb8af8d29768", # Zelda collection
        "IQS":            "0ab48b2d44a74b3bb2d384f6170c2742",
        "IQT":            "a475e9f8615513666a265c464708ae8f",
    },

    "MM": {
        "NJ0":            "15d1a2217cad61c39cfecbffa0703e25",
        "NJ1":            "c38a7f6f6b61862ea383a75cdf888279",
        "NEK":            "8f281800fba5ddcb1d2b377731fc0215",
        "NE0":            "2a0a8acb61538235bc1094d297fb6556",
        "NP0":            "13fab67e603b002ceaf0eea84130e973",
        "NPD":            "71fbae5d2b27926ea54e92ce2fc91622",
        "NP1":            "beccfded43a2f159d03555027462a950",
        "CE0":            "ac0751dbc23ab2ec0c3144203aca0003",
        "CP0":            "dbe9af0db46256e42b5c67902b696549",
        "CJ0":            "d3929aadf7640f8c5b4ce8321ad4393a",
    },
}

def getStrHash(byte_array):
    return str(hashlib.md5(byte_array).hexdigest())

def checkExistingRom(filename, game_version):
    if not path.exists(filename):
        return False

    with open(filename, mode="rb") as f:
        fileContent = bytearray(f.read())
        if getStrHash(fileContent) == VERSIONS_MD5S[game_version[0]][game_version[1]]:
            return True
    return False

def wordSwapFile(fileContent):
    words = str(int(len(fileContent)/4))
    little_byte_format = "<" + words + "I"
    big_byte_format = ">" + words + "I"
    tmp = struct.unpack_from(little_byte_format, fileContent, 0)
    struct.pack_into(big_byte_format, fileContent, 0, *tmp)
    return fileContent

def byteSwapFile(fileContent):
    halfwords = str(int(len(fileContent)/2))
    little_byte_format = "<" + halfwords + "H"
    big_byte_format = ">" + halfwords + "H"
    tmp = struct.unpack_from(little_byte_format, fileContent, 0)
    struct.pack_into(big_byte_format, fileContent, 0, *tmp)
    return fileContent

def perVersionFixes(fileContent, game_version):
    if game_version == ["OOT", "CPMD"]:
        # Strip the overdump
        print("Stripping overdump...")
        fileContent = fileContent[0:0x3600000]

        # Patch the header
        print("Patching header...")
        fileContent[0x3E] = 0x50

    if game_version == ["MM", "NPD"]:
        # Strip the overdump
        print("Stripping overdump...")
        fileContent = fileContent[0:0x205A220]

    return fileContent


def fixBaserom(rom):
    # Read in the original ROM
    print("Using '" + rom + "'.")
    with open(rom, mode="rb") as f:
        fileContent = bytearray(f.read())

    # Check if ROM needs to be byte/word swapped
    # Little-endian
    if fileContent[0] == 0x40:
        endian = "bad"
        header = wordSwapFile(fileContent[0:0x40])

    # Byte-swapped
    elif fileContent[0] == 0x37:
        endian = "ugly"
        header = byteSwapFile(fileContent[0:0x40])

    else:
        endian = "good"
        header = fileContent[0:0x40]

    language = chr(header[0x3E])
    crc = header[0x10:0x18].hex()

    game_version = CRC_VERSION[crc]

    if game_version == None:
        print("Does not appear to be a supported OoT or MM version: CRC not found.")
        sys.exit(1)

    if game_version[0] == "OOT" and language == "J":
        if game_version[1] == "NE0":
            game_version[1] = "NJ0"
            game_version[2] = "Nintendo 64 Japanese 1.0"
        elif game_version[1] == "NE1":
            game_version[1] = "NJ1"
            game_version[2] = "Nintendo 64 Japanese 1.1"
        elif game_version[1] == "NE2":
            game_version[1] = "NJ2"
            game_version[2] = "Nintendo 64 Japanese 1.2"

    print("Detected ROM for " + game_version[0] + ", version " + game_version[1] + " (" + game_version[2] + ")")

    game_edition = [i.lower() for i in game_version]
    outRom = path.join(game_edition[0], game_edition[0] + "_" + game_edition[1] + ".z64")

    # If there already exists a correct ROM, we don't need to change anything
    if checkExistingRom(outRom, game_version):
        print("There is already a valid copy of this ROM in place. Will not copy.")
        sys.exit(0)

    # byte/word swap rest
    fileContent = {
        "good": lambda x: x,
        "bad": wordSwapFile,
        "ugly": byteSwapFile,
    }[endian](fileContent)

    # Trim overdump
    fileContent = perVersionFixes(fileContent, game_version)

    # Find and check hash
    hash = getStrHash(fileContent)

    if hash != VERSIONS_MD5S[game_version[0]][game_version[1]]:
        print("Error: checksum incorrect after conversion.")
        sys.exit(1)

    # Move to new location

    print(f"Writing new ROM '{outRom}'.")
    with open(outRom, mode="wb") as file:
        file.write(bytes(fileContent))

    print("Done!")

def main():
    description = "Fixes and copies/renames an OoT/MM ROM."

    parser = argparse.ArgumentParser(description=description, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument("rom", help="Zelda64 ROM to fix and move.")
    args = parser.parse_args()

    fixBaserom(args.rom)


if __name__ == "__main__":
    main()
