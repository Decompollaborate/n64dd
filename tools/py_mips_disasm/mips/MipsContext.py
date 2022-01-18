#!/usr/bin/python3

from __future__ import annotations

import ast
from sortedcontainers import SortedDict

from .GlobalConfig import GlobalConfig

from .Utils import *

class ContextFile:
    def __init__(self, name: str, vram: int):
        self.name: str = name
        self.vram: int = vram
        #self.references: List[int] = list()

class ContextSegment:
    def __init__(self, segmentName: str, segmentInputPath: str, segmentType: str, subsections):
        self.name: str = segmentName
        self.inputPath: str = segmentInputPath
        self.type: str = segmentType
        self.subsections: list = subsections

class ContextSymbol:
    def __init__(self, vram: int, name: str):
        self.vram: int = vram
        self.name: str = name
        self.type: str = ""
        self.arrayInfo: str = ""
        self.size: int = 4
        self.isDefined = False
        self.isUserDefined = False
        self.isBss = False
        self.referenceCounter: int = 0 # Only considers .text references
        self.isLateRodata: bool = False
        self.isMaybeString: bool = False

    def setTypeIfUnset(self, varType: str) -> bool:
        if self.type == "":
            self.type = varType
            return True
        return False

    def getSymbolPlusOffset(self, vramAddress: int):
        if self.vram == vramAddress:
            return self.name
        return f"{self.name} + 0x{vramAddress - self.vram:X}"

class Context:
    def __init__(self):
        self.files: Dict[int, ContextFile] = dict()
        self.segments: Dict[str, ContextSegment] = dict()

        self.funcsInFiles: Dict[str, List[int]] = dict()
        self.symbolToFile: Dict[int, str] = dict()

        self.funcAddresses: Dict[int, ContextSymbol] = dict()

        self.labels: Dict[int, ContextSymbol] = dict()
        # self.symbols: SortedDict[int, ContextSymbol]
        self.symbols = SortedDict()

        # Where the jump table is
        self.jumpTables: Dict[int, ContextSymbol] = dict()
        # The addresses each jump table has
        self.jumpTablesLabels: Dict[int, ContextSymbol] = dict()

        # Functions jumped into Using J instead of JAL
        self.fakeFunctions: Dict[int, ContextSymbol] = dict()

        self.constants: Dict[int, ContextSymbol] = dict()

        self.newPointersInData: Set[int] = set()

        # Stuff that looks like pointers, but the disassembler shouldn't count it as a pointer
        self.bannedSymbols: Set[int] = set()


    def getAnySymbol(self, vramAddress: int) -> ContextSymbol|None:
        if vramAddress in self.funcAddresses:
            return self.funcAddresses[vramAddress]

        if vramAddress in self.jumpTablesLabels:
            return self.jumpTablesLabels[vramAddress]

        if vramAddress in self.labels:
            return self.labels[vramAddress]

        if vramAddress in self.jumpTables:
            return self.jumpTables[vramAddress]

        if vramAddress in self.symbols:
            return self.symbols[vramAddress]

        if vramAddress in self.fakeFunctions:
            return self.fakeFunctions[vramAddress]

        return None

    # Like getAnySymbol, but it doesn't search in self.symbols
    def getAnyNonSymbol(self, vramAddress: int) -> ContextSymbol|None:
        if vramAddress in self.funcAddresses:
            return self.funcAddresses[vramAddress]

        if vramAddress in self.jumpTablesLabels:
            return self.jumpTablesLabels[vramAddress]

        if vramAddress in self.labels:
            return self.labels[vramAddress]

        if vramAddress in self.jumpTables:
            return self.jumpTables[vramAddress]

        if vramAddress in self.fakeFunctions:
            return self.fakeFunctions[vramAddress]

        return None

    def getGenericSymbol(self, vramAddress: int, tryPlusOffset: bool = True) -> ContextSymbol|None:
        if vramAddress in self.funcAddresses:
            return self.funcAddresses[vramAddress]

        if vramAddress in self.jumpTables:
            return self.jumpTables[vramAddress]

        if vramAddress in self.symbols:
            return self.symbols[vramAddress]

        if GlobalConfig.PRODUCE_SYMBOLS_PLUS_OFFSET and tryPlusOffset:
            rangeObj = self.symbols.irange(maximum=vramAddress, reverse=True)
            for vram in rangeObj:
                contextSym: ContextSymbol = self.symbols[vram]

                if vramAddress > vram and vramAddress < vram + contextSym.size:
                    return contextSym

                # Only one iteration
                break

        return None

    def getSymbol(self, vramAddress: int, tryPlusOffset: bool = True, checkUpperLimit: bool = True) -> ContextSymbol|None:
        if vramAddress in self.symbols:
            return self.symbols[vramAddress]

        if GlobalConfig.PRODUCE_SYMBOLS_PLUS_OFFSET and tryPlusOffset:
            rangeObj = self.symbols.irange(maximum=vramAddress, reverse=True)
            for vram in rangeObj:
                contextSym: ContextSymbol = self.symbols[vram]

                symbolSize = contextSym.size
                if vramAddress > vram:
                    if checkUpperLimit:
                        if vramAddress >= vram + symbolSize:
                            break
                    return contextSym

                # Only one iteration
                break
        return None

    def getGenericLabel(self, vramAddress: int) -> ContextSymbol|None:
        if vramAddress in self.funcAddresses:
            return self.funcAddresses[vramAddress]

        if vramAddress in self.jumpTablesLabels:
            return self.jumpTablesLabels[vramAddress]

        if vramAddress in self.labels:
            return self.labels[vramAddress]

        return None

    def getFunction(self, vramAddress: int) -> ContextSymbol|None:
        if vramAddress in self.funcAddresses:
            return self.funcAddresses[vramAddress]

        return None

    def getConstant(self, constantValue: int) -> ContextSymbol|None:
        if constantValue in self.constants:
            return self.constants[constantValue]

        return None


    def addFunction(self, filename: str|None, vramAddress: int, name: str):
        #if filename is not None and filename in self.files:
        #    if vramAddress not in self.files[filename].references:
        #        self.files[filename].references.append(vramAddress)
        if vramAddress not in self.funcAddresses:
            contextSymbol = ContextSymbol(vramAddress, name)
            contextSymbol.type = "@function"
            self.funcAddresses[vramAddress] = contextSymbol
        if vramAddress not in self.symbolToFile and filename is not None:
            self.symbolToFile[vramAddress] = filename

        if vramAddress in self.fakeFunctions:
            del self.fakeFunctions[vramAddress]

    def addBranchLabel(self, vramAddress: int, name: str):
        if vramAddress not in self.labels:
            contextSymbol = ContextSymbol(vramAddress, name)
            contextSymbol.type = "@branchlabel"
            self.labels[vramAddress] = contextSymbol

    def addJumpTable(self, vramAddress: int, name: str):
        if vramAddress not in self.jumpTables:
            contextSymbol = ContextSymbol(vramAddress, name)
            contextSymbol.type = "@jumptable"
            contextSymbol.isLateRodata = True
            self.jumpTables[vramAddress] = contextSymbol
            return contextSymbol
        return self.jumpTables[vramAddress]

    def addJumpTableLabel(self, vramAddress: int, name: str):
        if vramAddress not in self.jumpTables:
            contextSymbol = ContextSymbol(vramAddress, name)
            contextSymbol.type = "@jumptablelabel"
            self.jumpTablesLabels[vramAddress] = contextSymbol

    def addFakeFunction(self, vramAddress: int, name: str):
        if vramAddress not in self.fakeFunctions:
            contextSymbol = ContextSymbol(vramAddress, name)
            contextSymbol.type = "@fakefunction"
            self.fakeFunctions[vramAddress] = contextSymbol


    def fillDefaultBannedSymbols(self):
        banned = {0x80000010, 0x80000020}
        self.bannedSymbols |= banned

    def fillLibultraSymbols(self):
        libultraSyms = {
            0x80000300: ("osTvType",       "u32", 0x4),
            0x80000304: ("osRomType",      "u32", 0x4),
            0x80000308: ("osRomBase",      "u32", 0x4),
            0x8000030C: ("osResetType",    "u32", 0x4),
            0x80000310: ("osCicId",        "u32", 0x4),
            0x80000314: ("osVersion",      "u32", 0x4),
            0x80000304: ("osRomType",      "u32", 0x4),
            0x80000318: ("osMemSize",      "u32", 0x4),
            0x8000031C: ("osAppNmiBuffer", "u8",  0x40),
        }

        for vram, (name, type, size) in libultraSyms.items():
            contextSym = ContextSymbol(vram, name)
            contextSym.type = type
            contextSym.size = size
            contextSym.isDefined = True
            contextSym.isUserDefined = True
            self.symbols[vram] = contextSym

    def fillHardwareRegs(self):
        # OS hardware registers
        hardwareRegs = {
            # Signal Processor Registers
            0xA4040000: "D_A4040000", # SP_MEM_ADDR_REG
            0xA4040004: "D_A4040004", # SP_DRAM_ADDR_REG
            0xA4040008: "D_A4040008", # SP_RD_LEN_REG
            0xA404000C: "D_A404000C", # SP_WR_LEN_REG
            0xA4040010: "D_A4040010", # SP_STATUS_REG
            0xA4040014: "D_A4040014", # SP_DMA_FULL_REG
            0xA4040018: "D_A4040018", # SP_DMA_BUSY_REG
            0xA404001C: "D_A404001C", # SP_SEMAPHORE_REG

            0xA4080000: "D_A4080000", # SP PC

            # Display Processor Command Registers / Rasterizer Interface
            0xA4100000: "D_A4100000", # DPC_START_REG
            0xA4100004: "D_A4100004", # DPC_END_REG
            0xA4100008: "D_A4100008", # DPC_CURRENT_REG
            0xA410000C: "D_A410000C", # DPC_STATUS_REG
            0xA4100010: "D_A4100010", # DPC_CLOCK_REG
            0xA4100014: "D_A4100014", # DPC_BUFBUSY_REG
            0xA4100018: "D_A4100018", # DPC_PIPEBUSY_REG
            0xA410001C: "D_A410001C", # DPC_TMEM_REG

            # Display Processor Span Registers
            0xA4200000: "D_A4200000", # DPS_TBIST_REG / DP_TMEM_BIST
            0xA4200004: "D_A4200004", # DPS_TEST_MODE_REG
            0xA4200008: "D_A4200008", # DPS_BUFTEST_ADDR_REG
            0xA420000C: "D_A420000C", # DPS_BUFTEST_DATA_REG

            # MIPS Interface Registers
            0xA4300000: "D_A4300000", # MI_MODE_REG / MI_INIT_MODE_REG
            0xA4300004: "D_A4300004", # MI_VERSION_REG
            0xA4300008: "D_A4300008", # MI_INTR_REG
            0xA430000C: "D_A430000C", # MI_INTR_MASK_REG

            # Video Interface Registers
            0xA4400000: "D_A4400000", # VI_STATUS_REG / VI_CONTROL_REG
            0xA4400004: "D_A4400004", # VI_DRAM_ADDR_REG / VI_ORIGIN_REG
            0xA4400008: "D_A4400008", # VI_WIDTH_REG
            0xA440000C: "D_A440000C", # VI_INTR_REG
            0xA4400010: "D_A4400010", # VI_CURRENT_REG
            0xA4400014: "D_A4400014", # VI_BURST_REG / VI_TIMING_REG
            0xA4400018: "D_A4400018", # VI_V_SYNC_REG
            0xA440001C: "D_A440001C", # VI_H_SYNC_REG
            0xA4400020: "D_A4400020", # VI_LEAP_REG
            0xA4400024: "D_A4400024", # VI_H_START_REG
            0xA4400028: "D_A4400028", # VI_V_START_REG
            0xA440002C: "D_A440002C", # VI_V_BURST_REG
            0xA4400030: "D_A4400030", # VI_X_SCALE_REG
            0xA4400034: "D_A4400034", # VI_Y_SCALE_REG

            # Audio Interface Registers
            0xA4500000: "D_A4500000", # AI_DRAM_ADDR_REG
            0xA4500004: "D_A4500004", # AI_LEN_REG
            0xA4500008: "D_A4500008", # AI_CONTROL_REG
            0xA450000C: "D_A450000C", # AI_STATUS_REG
            0xA4500010: "D_A4500010", # AI_DACRATE_REG
            0xA4500014: "D_A4500014", # AI_BITRATE_REG

            # Peripheral/Parallel Interface Registers
            0xA4600000: "D_A4600000", # PI_DRAM_ADDR_REG
            0xA4600004: "D_A4600004", # PI_CART_ADDR_REG
            0xA4600005: "D_A4600005",
            0xA4600006: "D_A4600006",
            0xA4600007: "D_A4600007",
            0xA4600008: "D_A4600008", # PI_RD_LEN_REG
            0xA460000C: "D_A460000C", # PI_WR_LEN_REG
            0xA4600010: "D_A4600010", # PI_STATUS_REG
            0xA4600014: "D_A4600014", # PI_BSD_DOM1_LAT_REG # PI dom1 latency
            0xA4600018: "D_A4600018", # PI_BSD_DOM1_PWD_REG # PI dom1 pulse width
            0xA460001C: "D_A460001C", # PI_BSD_DOM1_PGS_REG # PI dom1 page size
            0xA4600020: "D_A4600020", # PI_BSD_DOM1_RLS_REG # PI dom1 release
            0xA4600024: "D_A4600024", # PI_BSD_DOM2_LAT_REG # PI dom2 latency
            0xA4600028: "D_A4600028", # PI_BSD_DOM2_LWD_REG # PI dom2 pulse width
            0xA460002C: "D_A460002C", # PI_BSD_DOM2_PGS_REG # PI dom2 page size
            0xA4600030: "D_A4600030", # PI_BSD_DOM2_RLS_REG # PI dom2 release

            # RDRAM Interface Registers
            0xA4700000: "D_A4700000", # RI_MODE_REG
            0xA4700004: "D_A4700004", # RI_CONFIG_REG
            0xA4700008: "D_A4700008", # RI_CURRENT_LOAD_REG
            0xA470000C: "D_A470000C", # RI_SELECT_REG
            0xA4700010: "D_A4700010", # RI_REFRESH_REG
            0xA4700014: "D_A4700014", # RI_LATENCY_REG
            0xA4700018: "D_A4700018", # RI_RERROR_REG
            0xA470001C: "D_A470001C", # RI_WERROR_REG

            # Serial Interface Registers
            0xA4800000: "D_A4800000", # SI_DRAM_ADDR_REG
            0xA4800004: "D_A4800004", # SI_PIF_ADDR_RD64B_REG
            0xA4800008: "D_A4800008", # reserved
            0xA480000C: "D_A480000C", # reserved
            0xA4800010: "D_A4800010", # SI_PIF_ADDR_WR64B_REG
            0xA4800014: "D_A4800014", # reserved
            0xA4800018: "D_A4800018", # SI_STATUS_REG
        }

        for vram, name in hardwareRegs.items():
            contextSym = ContextSymbol(vram, name)
            contextSym.type = "@hardwarereg"
            contextSym.size = 4
            contextSym.isDefined = True
            contextSym.isUserDefined = True
            self.symbols[vram] = contextSym


    def readFunctionMap(self, version: str):
        functionmap_filename = f"functionmap/{version}.csv"
        if not os.path.exists(functionmap_filename):
            return

        functionmap_file = readCsv(functionmap_filename)
        for row in functionmap_file:
            filename = row[0]
            vram = int(row[1], 16)
            func_name = row[2]

            if filename not in self.funcsInFiles:
                self.funcsInFiles[filename] = []
            self.funcsInFiles[filename].append(vram)
            contextFuncSymbol = ContextSymbol(vram, func_name)
            contextFuncSymbol.type = "@function"
            contextFuncSymbol.isUserDefined = True
            self.funcAddresses[vram] = contextFuncSymbol
            self.symbolToFile[vram] = filename

    def readMMAddressMaps(self, filesPath: str, functionsPath: str, variablesPath: str):
        with open(filesPath) as infile:
            files_spec = ast.literal_eval(infile.read())

        for segmentName, segmentInputPath, segmentType, subsections, subfiles  in files_spec:
            self.segments[segmentName] = ContextSegment(segmentName, segmentInputPath, segmentType, subsections)
            for vram, subname in subfiles.items():
                if subname == "":
                    subname = f"{segmentName}_{toHex(vram, 8)[2:]}"
                self.files[vram] = ContextFile(subname, vram)

        with open(functionsPath) as infile:
            functions_ast = ast.literal_eval(infile.read())

        for vram, funcData in functions_ast.items():
            funcName = funcData[0]
            self.addFunction(None, vram, funcName)
            self.funcAddresses[vram].isUserDefined = True

        with open(variablesPath) as infile:
            variables_ast = ast.literal_eval(infile.read())

        for vram, varData in variables_ast.items():
            varName, varType, varArrayInfo, varSize = varData
            contVar = ContextSymbol(vram, varName)
            contVar.type = varType
            contVar.arrayInfo = varArrayInfo
            contVar.size = varSize
            contVar.isUserDefined = True
            self.symbols[vram] = contVar

    def readVariablesCsv(self, filepath: str):
        if not os.path.exists(filepath):
            return

        variables_file = readCsv(filepath)
        for row in variables_file:
            if len(row) == 0:
                continue

            vramStr, varName, varType, varSizeStr = row

            vram = int(vramStr, 16)
            varSize = int(varSizeStr, 16)
            contVar = ContextSymbol(vram, varName)
            contVar.type = varType
            contVar.size = varSize
            contVar.isUserDefined = True
            self.symbols[vram] = contVar

    def readFunctionsCsv(self, filepath: str):
        if not os.path.exists(filepath):
            return

        functions_file = readCsv(filepath)
        for row in functions_file:
            if len(row) == 0:
                continue

            vramStr, funcName = row

            vram = int(vramStr, 16)
            self.addFunction(None, vram, funcName)
            self.funcAddresses[vram].isUserDefined = True

    def readConstantsCsv(self, filepath: str):
        if not os.path.exists(filepath):
            return

        constants_file = readCsv(filepath)
        for row in constants_file:
            if len(row) == 0:
                continue

            constantValueStr, constantName = row

            constantValue = int(constantValueStr, 16)
            self.constants[constantValue] = ContextSymbol(constantValue, constantName)


    def saveContextToFile(self, filepath: str):
        with open(filepath, "w") as f:
            for address, symbol in self.funcAddresses.items():
                file = self.symbolToFile.get(address, "")
                jal = (address & 0x00FFFFFF) >> 2
                jal = 0x0C000000 | jal
                f.write(f"function,{file},{toHex(address, 8)},{symbol.name},{toHex(jal, 8)},{symbol.isUserDefined},{symbol.isDefined}\n")

            for address, symbol in self.jumpTables.items():
                file = self.symbolToFile.get(address, "")
                f.write(f"jump_table,{file},{toHex(address, 8)},{symbol.name},\n")

            for address, symbol in self.jumpTablesLabels.items():
                file = self.symbolToFile.get(address, "")
                f.write(f"jump_table_label,{file},{toHex(address, 8)},{symbol.name},\n")

            for address, symbol in self.labels.items():
                file = self.symbolToFile.get(address, "")
                f.write(f"label,{file},{toHex(address, 8)},{symbol.name},\n")

            for address, symbol in self.symbols.items():
                if self.getAnyNonSymbol(address) is not None:
                    # Filter out symbols defined in other categories
                    continue
                file = self.symbolToFile.get(address, "")
                f.write(f"symbol,{file},{toHex(address, 8)},{symbol.name},{symbol.type},{symbol.size},{symbol.isUserDefined},{symbol.isDefined}\n")

            for address, symbol in self.fakeFunctions.items():
                file = self.symbolToFile.get(address, "")
                f.write(f"fake_function,{file},{toHex(address, 8)},{symbol.name},\n")

            for address, constant in self.constants.items():
                file = self.symbolToFile.get(address, "")
                f.write(f"constants,{file},{toHex(address, 8)},{constant.name},\n")

            for address in self.newPointersInData:
                file = self.symbolToFile.get(address, "")
                f.write(f"new_pointer_in_data,{file},{toHex(address, 8)},,\n")

            for address in self.bannedSymbols:
                file = self.symbolToFile.get(address, "")
                f.write(f"banned_symbol,{file},{toHex(address, 8)},,\n")
