MAKEFLAGS += --no-builtin-rules

# Build options can either be changed by modifying the makefile, or by building with 'make SETTING=value'

GAME     ?= oot
VERSION  ?= ne0
# If COMPARE is 1, check the output md5sum after building
COMPARE ?= 1
# If NON_MATCHING is 1, define the NON_MATCHING C flag when building
NON_MATCHING ?= 0
# if WERROR is 1, pass -Werror to CC_CHECK, so warnings would be treated as errors
WERROR ?= 0
# Keep .mdebug section in build
KEEP_MDEBUG ?= 0

ifeq ($(NON_MATCHING),1)
  CFLAGS := -DNON_MATCHING
  CPPFLAGS := -DNON_MATCHING
  COMPARE := 0
endif

MAKE = make
CPPFLAGS += -P

ifeq ($(OS),Windows_NT)
  DETECTED_OS=windows
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
    DETECTED_OS=linux
  endif
  ifeq ($(UNAME_S),Darwin)
    DETECTED_OS=macos
    MAKE=gmake
    CPPFLAGS += -xc++
  endif
endif

#### Tools ####
ifeq ($(shell type mips-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  MIPS_BINUTILS_PREFIX := mips-linux-gnu-
else
  $(error Please install or build mips-linux-gnu)
endif

CC       := tools/ido_recomp/$(DETECTED_OS)/7.1/cc
CC_OLD   := tools/ido_recomp/$(DETECTED_OS)/5.3/cc

AS         := $(MIPS_BINUTILS_PREFIX)as
LD         := $(MIPS_BINUTILS_PREFIX)ld
OBJCOPY    := $(MIPS_BINUTILS_PREFIX)objcopy
OBJDUMP    := $(MIPS_BINUTILS_PREFIX)objdump
MIPS_GCC   := $(MIPS_BINUTILS_PREFIX)gcc

IINC       := -Iinclude -Isrc

ifeq ($(KEEP_MDEBUG),0)
  RM_MDEBUG = $(OBJCOPY) --remove-section .mdebug $@
else
  RM_MDEBUG = @:
endif

# Check code syntax with host compiler
CHECK_WARNINGS := -Wall -Wextra -Wno-format-security -Wno-unknown-pragmas -Wno-unused-parameter -Wno-unused-variable -Wno-missing-braces -Wno-int-conversion -Wno-unused-but-set-variable -Wno-unused-label
CC_CHECK   := gcc -fno-builtin -fsyntax-only -funsigned-char -fdiagnostics-color -std=gnu89 -D _LANGUAGE_C -D NON_MATCHING $(IINC) -nostdinc $(CHECK_WARNINGS)
CC_CHECK += -m32


CPP             := cpp
ELF2ROM         ?= ./tools/elf2rom
MKLDSCRIPT      ?= ./tools/mkldscript
DISASSEMBLER    ?= ./tools/py_mips_disasm/simpleDisasm.py
ASM_PROCESSOR   ?= python3 tools/asm_processor/build.py

ASMPROCFLAGS := 
OPTFLAGS := -O2
ASFLAGS := -march=vr4300 -32 -Iinclude
MIPS_VERSION := -mips2

# we support Microsoft extensions such as anonymous structs, which the compiler does support but warns for their usage. Surpress the warnings with -woff.
CFLAGS += -G 0 -non_shared -Xfullwarn -Xcpluscomm $(IINC) -nostdinc -Wab,-r4300_mul -woff 624,649,838,712

ifneq ($(WERROR), 0)
  CC_CHECK += -Werror
endif

#### Files ####

BASE_DIR       := $(GAME)/$(VERSION)

# ROM image
BASE_ROM       := $(GAME)/$(GAME)_$(VERSION).z64
ROM            := $(GAME)_$(VERSION)_uncompressed.z64
ELF            := $(BASE_DIR)/build/$(ROM:.z64=.elf)
# description of ROM segments
SPEC           := $(BASE_DIR)/spec_$(VERSION)
LDSCRIPT       := $(BASE_DIR)/build/ldscript_$(VERSION).txt

# create asm directories
$(shell mkdir -p $(BASE_DIR)/baserom/ $(BASE_DIR)/asm/text $(BASE_DIR)/asm/data)

SRC_DIRS := $(shell find src -type d)
ASM_DIRS       := $(shell find $(BASE_DIR)/asm/ -type d -not -path "$(BASE_DIR)/asm/functions*")

C_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES        := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
BASEROM_FILES  := $(wildcard $(BASE_DIR)/baserom/*)
O_FILES        := $(subst src/,$(BASE_DIR)/build/src/,$(C_FILES:.c=.o)) \
                  $(subst $(BASE_DIR)/,$(BASE_DIR)/build/,$(S_FILES:.s=.o)) \
                  $(subst $(BASE_DIR)/,$(BASE_DIR)/build/,$(BASEROM_FILES:.bin=.o))

# Automatic dependency files
# (Only asm_processor dependencies are handled for now)
DEP_FILES := $(O_FILES:.o=.asmproc.d)

DISASM_LIST    := $(shell cat $(GAME)/tables/disasm_list.txt) \
                  $(shell [ -f $(BASE_DIR)/tables/disasm_list.txt ] && cat $(BASE_DIR)/tables/disasm_list.txt)

CSV_FILES      := $(DISASM_LIST:%=$(BASE_DIR)/tables/files_%.csv) \
                  $(BASE_DIR)/tables/functions.csv $(BASE_DIR)/tables/variables.csv
DISASM_TARGETS := $(DISASM_LIST:%=$(BASE_DIR)/asm/text/%/.disasm)


# create build directories
$(shell mkdir -p $(BASE_DIR)/build/baserom $(foreach dir,$(ASM_DIRS),$(subst $(BASE_DIR)/,$(BASE_DIR)/build/,$(dir))))
$(shell mkdir -p $(subst src/,$(BASE_DIR)/build/src/,$(SRC_DIRS)))


# directory flags
$(BASE_DIR)/build/src/n64dd_O2_g3/%.o: OPTFLAGS:= -O2 -g3

# file flags
$(BASE_DIR)/build/src/n64dd_O2_g3/n64dd_801C9B70.o: ASMPROCFLAGS:= --input-enc=utf-8 --output-enc=euc-jp

# cc & asm-
# Required to expand CC in the macro after it
CC_ALT := $(CC)
$(BASE_DIR)/build/src/%.o: CC = $(ASM_PROCESSOR) $(ASMPROCFLAGS) $(CC_ALT) -- $(AS) $(ASFLAGS) --


#### Main Targets ####

uncompressed: $(ROM)
ifeq ($(COMPARE),1)
	@md5sum $(ROM)
	@md5sum -c $(BASE_DIR)/checksum_uncompressed_$(VERSION).md5
endif

.PHONY: all splitcsvs disasm clean
.DEFAULT_GOAL := all
all: uncompressed


$(ROM): $(ELF)
	$(ELF2ROM) -cic 6105 $< $@

$(ELF): $(O_FILES) $(LDSCRIPT) $(BASE_DIR)/build/undefined_syms_$(VERSION).txt $(BASE_DIR)/build/libultra_syms.txt $(BASE_DIR)/build/hardware_regs.txt
	$(LD) -T $(BASE_DIR)/build/undefined_syms_$(VERSION).txt -T $(BASE_DIR)/build/libultra_syms.txt -T $(BASE_DIR)/build/hardware_regs.txt -T $(LDSCRIPT) --no-check-sections --accept-unknown-input-arch --emit-relocs -Map $(BASE_DIR)/build/$(GAME)_$(VERSION).map -o $@


#### Main commands ####

## Cleaning
clean:
	$(RM) -rf $(ROM) $(ELF) $(BASE_DIR)/build

asmclean:
	$(RM) -rf $(BASE_DIR)/asm $(BASE_DIR)/context


## Extraction step
setup:
	$(MAKE) -C tools
	./decompress_baserom.py $(GAME) $(VERSION)
	./extract_baserom.py $(GAME) $(VERSION)

## Assembly generation
disasm: splitcsvs $(DISASM_TARGETS)
	./tools/automators/gen_undefined_syms.py --version $(VERSION) > $(BASE_DIR)/undefined_syms_$(VERSION).txt
	@echo "Disassembly done!"

splitcsvs: $(CSV_FILES)

diff-init: uncompressed
	$(RM) -rf $(BASE_DIR)/expected/
	mkdir -p $(BASE_DIR)/expected/
	cp -r $(BASE_DIR)/build $(BASE_DIR)/expected/build

#### Various Recipes ####

$(BASE_DIR)/tables/%.csv: $(GAME)/tables/%.csv
	./tools/csvSplit.py $(GAME) $<

$(BASE_DIR)/tables/files_%.csv: $(GAME)/tables/%.*.csv
	./tools/csvSplit.py $(GAME) $<

## Linker Scripts
$(BASE_DIR)/build/undefined_syms_$(VERSION).txt: $(BASE_DIR)/undefined_syms_$(VERSION).txt
	$(CPP) $(CPPFLAGS) $< > $@

$(BASE_DIR)/build/libultra_syms.txt: libultra_syms.txt
	$(CPP) $(CPPFLAGS) $< > $@

$(BASE_DIR)/build/hardware_regs.txt: hardware_regs.txt
	$(CPP) $(CPPFLAGS) $< > $@

$(LDSCRIPT): $(SPEC)
	$(CPP) $(CPPFLAGS) $< > $(BASE_DIR)/build/spec_$(VERSION)
	$(MKLDSCRIPT) $(BASE_DIR)/build/spec_$(VERSION) $@

## Baserom
$(BASE_DIR)/build/baserom/%.o: $(BASE_DIR)/baserom/%.bin
	$(OBJCOPY) -I binary -O elf32-big $< $@

## Build assembly
$(BASE_DIR)/build/asm/text/%.o: $(BASE_DIR)/asm/text/%.s
	$(AS) $(ASFLAGS) $< -o $@

$(BASE_DIR)/build/asm/data/%.o: $(BASE_DIR)/asm/data/%.s
	iconv --from UTF-8 --to EUC-JP $< | $(AS) $(ASFLAGS) -o $@

## Build C files
$(BASE_DIR)/build/src/%.o: src/%.c
	$(CC_CHECK) $<
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<
	@$(OBJDUMP) -d $@ > $(@:.o=.s)
	$(RM_MDEBUG)


## Disassembly
$(BASE_DIR)/asm/text/%/.disasm: $(BASE_DIR)/baserom/%.bin $(BASE_DIR)/tables/variables.csv $(BASE_DIR)/tables/functions.csv $(BASE_DIR)/tables/files_%.csv
	$(RM) -rf $(BASE_DIR)/asm/text/$* $(BASE_DIR)/asm/data/$* $(BASE_DIR)/context/$*.txt
	$(DISASSEMBLER) $< $(BASE_DIR)/asm/text/$* -q --data-output $(BASE_DIR)/asm/data/$* --split-functions $(BASE_DIR)/asm/functions/$* --variables $(BASE_DIR)/tables/variables.csv --functions $(BASE_DIR)/tables/functions.csv --constants $(GAME)/tables/constants.csv --file-splits $(BASE_DIR)/tables/files_$*.csv  --save-context $(BASE_DIR)/context/$*.txt --constants $(BASE_DIR)/tables/constants_$*.csv
	@touch $@

-include $(DEP_FILES)
