#!/usr/bin/env python3

import argparse
import os.path

# Not actually macros, just look like them
_GAME_DIR_TEMPLATE = "{game}"
_VERSION_DIR_TEMPLATE = os.path.join(_GAME_DIR_TEMPLATE, "{version}")
_ROM_NAME_TEMPLATE = "{game}_{version}_uncompressed.z64"
_BASEROM_NAME_TEMPLATE = "baserom_" + _ROM_NAME_TEMPLATE
_BUILT_MAP_RELPATH_TEMPLATE = os.path.join("build", "{game}_{version}.map")
_EXPECTED_MAP_RELPATH_TEMPLATE = os.path.join("expected", _BUILT_MAP_RELPATH_TEMPLATE)

# The ones you should actually use
ROM_PATH_TEMPLATE = _ROM_NAME_TEMPLATE
BASEROM_PATH_TEMPLATE = os.path.join(_GAME_DIR_TEMPLATE, _BASEROM_NAME_TEMPLATE)
BUILT_MAP_PATH_TEMPLATE = os.path.join(_VERSION_DIR_TEMPLATE, _BUILT_MAP_RELPATH_TEMPLATE)
EXPECTED_MAP_PATH_TEMPLATE = os.path.join(_VERSION_DIR_TEMPLATE, _EXPECTED_MAP_RELPATH_TEMPLATE)

parser = argparse.ArgumentParser(
    description="Display various information about a symbol or address."
)
parser.add_argument(
    "name",
    type=str,
    default="",
    help="symbol name or VROM/VRAM address to lookup"
)
parser.add_argument(
    "-e",
    "--expected",
    dest="use_expected",
    action="store_true",
    help="use the map file in expected/build/ instead of build/"
)
parser.add_argument("--game", help="game folder to use", default="oot")
parser.add_argument("--version", help="version to use", default="ne0")
args = parser.parse_args()

game_version = {
    "game": args.game,
    "version": args.version,
}

mymap = BUILT_MAP_PATH_TEMPLATE.format(**game_version)
if args.use_expected:
    mymap = EXPECTED_MAP_PATH_TEMPLATE.format(**game_version)

if not os.path.isfile(mymap):
    print(f"{mymap} must exist.")
    exit(1)


def search_address(target_addr):
    is_ram = target_addr & 0x80000000
    ram_offset = None
    prev_ram = 0
    prev_rom = 0
    prev_sym = "<start of rom>"
    cur_file = "<no file>"
    prev_file = cur_file
    prev_line = ""
    with open(mymap) as f:
        for line in f:
            if "load address" in line:
                # Ignore .bss sections if we're looking for a ROM address
                if not is_ram and (".bss" in line or ".bss" in prev_line):
                    ram_offset = None
                    continue
                ram = int(line[16 : 16 + 18], 0)
                rom = int(line[59 : 59 + 18], 0)
                ram_offset = ram - rom
                continue

            prev_line = line

            if (
                ram_offset is None
                or "=" in line
                or "*fill*" in line
                or " 0x" not in line
            ):
                continue

            ram = int(line[16 : 16 + 18], 0)
            rom = ram - ram_offset
            sym = line.split()[-1]

            if "0x" in sym and "/" not in sym:
                ram_offset = None
                continue
            if "/" in sym:
                cur_file = sym
                continue

            if rom == target_addr or (is_ram and ram == target_addr):
                return f"{sym} (VRAM 0x{ram:X}, VROM 0x{rom:X}, {cur_file})"
            if rom > target_addr or (is_ram and ram > target_addr):
                offset = target_addr - prev_ram if is_ram else target_addr - prev_rom
                return f"at 0x{offset:X} bytes inside {prev_sym} (VRAM 0x{prev_ram:X}, VROM 0x{prev_rom:X}, {prev_file})"

            prev_ram = ram
            prev_rom = rom
            prev_sym = sym
            prev_file = cur_file

    return "at end of rom?"


def search_symbol(target_sym):
    ram_offset = None
    cur_file = "<no file>"
    prev_line = ""
    with open(mymap) as f:
        for line in f:
            if "load address" in line:
                ram = int(line[16 : 16 + 18], 0)
                rom = int(line[59 : 59 + 18], 0)
                ram_offset = ram - rom
                continue

            prev_line = line

            if (
                ram_offset is None
                or "=" in line
                or "*fill*" in line
                or " 0x" not in line
            ):
                continue

            ram = int(line[16 : 16 + 18], 0)
            rom = ram - ram_offset
            sym = line.split()[-1]

            if "0x" in sym and "/" not in sym:
                ram_offset = None
                continue
            elif "/" in sym:
                cur_file = sym
                continue

            if sym == target_sym:
                return (rom, cur_file, ram)

    return None


try:
    target_addr = int(args.name, 0)
    print(args.name, "is", search_address(target_addr))
except ValueError:
    sym_info = search_symbol(args.name)
    if sym_info is not None:
        sym_rom = sym_info[0]
        sym_file = sym_info[1]
        sym_ram = sym_info[2]
        print(f"Symbol {args.name} (VRAM: 0x{sym_ram:08X}, VROM: 0x{sym_rom:06X}, {sym_file})")
    else:
        print(f"Symbol {args.name} not found in map file {mymap}")
