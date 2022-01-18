#!/usr/bin/python3

from __future__ import annotations

import csv
import os
import hashlib
import json
import struct
from typing import List, Dict, Tuple, Set, Any, TextIO
import subprocess
import sys
import shutil

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

# https://stackoverflow.com/questions/1512457/determining-if-stdout-for-a-python-process-is-redirected
def isStdoutRedirected() -> bool:
    return not sys.stdout.isatty()

# Returns the md5 hash of a bytearray
def getStrHash(byte_array: bytearray) -> str:
    return str(hashlib.md5(byte_array).hexdigest())

def writeBytearrayToFile(filepath: str, array_of_bytes: bytearray):
    with open(filepath, mode="wb") as f:
       f.write(array_of_bytes)

def readFileAsBytearray(filepath: str) -> bytearray:
    if not os.path.exists(filepath):
        return bytearray(0)
    with open(filepath, mode="rb") as f:
        return bytearray(f.read())

def readFile(filepath: str) -> List[str]:
    with open(filepath) as f:
        return [x.strip() for x in f.readlines()]

def readJson(filepath):
    with open(filepath) as f:
        return json.load(f)

def removeExtraWhitespace(line: str) -> str:
    return" ".join(line.split())

def bytesToBEWords(array_of_bytes: bytearray) -> List[int]:
    words = len(array_of_bytes)//4
    big_endian_format = f">{words}I"
    return list(struct.unpack_from(big_endian_format, array_of_bytes, 0))

def beWordsToBytes(words_list: List[int], buffer: bytearray) -> bytearray:
    words = len(words_list)
    big_endian_format = f">{words}I"
    struct.pack_into(big_endian_format, buffer, 0, *words_list)
    return buffer

def wordToFloat(word: int) -> float:
    return struct.unpack('>f', struct.pack('>I', word))[0]

def qwordToDouble(qword: int) -> float:
    return struct.unpack('>d', struct.pack('>Q', qword))[0]

def runCommandGetOutput(command: str, args: List[str]) -> List[str] | None:
    try:
        output = subprocess.check_output([command, *args]).decode("utf-8")
        return output.strip().split("\n")
    except:
        return None

def toHex(number: int, digits: int) -> str:
    return "0x" + hex(number)[2:].zfill(digits).upper()

def from2Complement(number: int, bits: int) -> int:
    isNegative = number & (1 << (bits - 1))
    if isNegative:
        return -((~number + 1) & ((1 << bits) - 1))
    return number

def readVersionedFileAsBytearrray(file: str, version: str) -> bytearray:
    filename = f"baserom_{version}/{file}"
    return readFileAsBytearray(filename)

def readCsv(filepath: str) -> List[List[str]]:
    data: List[List[str]] = []
    with open(filepath) as f:
        lines = f.readlines()
        processedLines = [x.strip().split("#")[0] for x in lines]
        csvReader = csv.reader(processedLines)
        for row in csvReader:
            data.append(list(row))

    return data

def decodeString(buf: bytearray, offset: int) -> Tuple[str, int]:
    # Escape characters that are unlikely to be used
    bannedEscapeCharacters = [
        0x01,
        0x02,
        0x03,
        0x04,
        0x05,
        0x06,
        # 0x07, # '\a'
        0x08, # '\b'
        # 0x09, # '\t'
        # 0x0A, # '\n'
        0x0B, # '\v'
        # 0x0C, # '\f'
        # 0x0D, # '\r'
        0x0E,
        0x0F,
        0x10,
        0x11,
        0x12,
        0x13,
        0x14,
        0x15,
        0x16,
        0x17,
        0x18,
        0x19,
        0x1A,
        0x1B,
        0x1C,
        0x1D,
        0x1E,
        0x1F,
    ]
    dst = bytearray()
    i = 0
    while offset + i < len(buf) and buf[offset + i] != 0:
        dst.append(buf[offset + i])
        i += 1
    if offset + i > len(buf):
        # We reached the end of the buffer without reaching a 0.
        raise RuntimeError()

    for bannedChar in bannedEscapeCharacters:
        if bannedChar in dst:
            raise RuntimeError()

    result = dst.decode("EUC-JP").replace("\n", "\\n").replace("\r", "\\r").replace("\t", "\\t").replace('"', '\\"').replace("\f", "\\f").replace("\a", "\\a")
    return result, i
