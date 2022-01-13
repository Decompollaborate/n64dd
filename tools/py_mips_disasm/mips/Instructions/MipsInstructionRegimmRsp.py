#!/usr/bin/python3

from __future__ import annotations

from .MipsConstants import InstructionId

from ..Utils import *

from .MipsInstructionRegimm import InstructionRegimm
from ..MipsContext import Context


class InstructionRegimmRsp(InstructionRegimm):
    RemovedOpcodes: Dict[int, InstructionId] = {
        0b00_010: InstructionId.BLTZL,
        0b00_011: InstructionId.BGEZL,

        0b01_000: InstructionId.TGEI,
        0b01_001: InstructionId.TGEIU,
        0b01_010: InstructionId.TLTI,
        0b01_011: InstructionId.TLTIU,

        0b10_010: InstructionId.BLTZALL,
        0b10_011: InstructionId.BGEZALL,

        0b01_100: InstructionId.TEQI,
        0b01_110: InstructionId.TNEI,
    }

    def __init__(self, instr: int):
        super().__init__(instr)

        self.isRsp = True

        for opcode in self.RemovedOpcodes:
            if opcode in self.opcodesDict:
                del self.opcodesDict[opcode]

        self.processUniqueId()


    def getRegisterName(self, register: int) -> str:
        return self.getGprRspRegisterName(register)
