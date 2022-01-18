#!/usr/bin/python3

from __future__ import annotations

import sys

class GlobalConfig:
    REMOVE_POINTERS: bool = False
    IGNORE_BRANCHES: bool = False # Ignores the address of every branch, jump and jal
    IGNORE_WORD_LIST: set = set() # Ignores words that starts in 0xXX

    WRITE_BINARY: bool = False # write to files splitted binaries

    ASM_COMMENT: bool = True
    FUNCTION_ASM_COUNT: bool = True

    ADD_NEW_SYMBOLS: bool = True
    PRODUCE_SYMBOLS_PLUS_OFFSET: bool = False

    TRUST_USER_FUNCTIONS: bool = True
    DISASSEMBLE_UNKNOWN_INSTRUCTIONS: bool = False
    DISASSEMBLE_RSP: bool = False

    STRING_GUESSER: bool = False

    QUIET: bool = False
    VERBOSE: bool = False
    PRINT_FUNCTION_ANALYSIS_DEBUG_INFO: bool = False
    PRINT_SYMBOL_FINDER_DEBUG_INFO: bool = False

def printQuietless(*args, **kwargs):
    if not GlobalConfig.QUIET:
        print(*args, **kwargs)

def epprintQuietless(*args, **kwargs):
    if not GlobalConfig.QUIET:
        print(*args, file=sys.stderr, **kwargs)


def printVerbose(*args, **kwargs):
    if not GlobalConfig.QUIET and GlobalConfig.VERBOSE:
        print(*args, **kwargs)

def eprintVerbose(*args, **kwargs):
    if not GlobalConfig.QUIET and GlobalConfig.VERBOSE:
        print(*args, file=sys.stderr, **kwargs)
