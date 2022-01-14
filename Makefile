MAKEFLAGS += --no-builtin-rules

# Build options can either be changed by modifying the makefile, or by building with 'make SETTING=value'

GAME     ?= oot
VERSION  ?= ne0
# If COMPARE is 1, check the output md5sum after building
COMPARE ?= 1

MAKE = make
CPPFLAGS += -P


#### Tools ####
ifeq ($(shell type mips-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  MIPS_BINUTILS_PREFIX := mips-linux-gnu-
else
  $(error Please install or build mips-linux-gnu)
endif



AS         := $(MIPS_BINUTILS_PREFIX)as
LD         := $(MIPS_BINUTILS_PREFIX)ld
OBJCOPY    := $(MIPS_BINUTILS_PREFIX)objcopy
OBJDUMP    := $(MIPS_BINUTILS_PREFIX)objdump
MIPS_GCC   := $(MIPS_BINUTILS_PREFIX)gcc


CPP             := cpp
ELF2ROM         ?= ./tools/elf2rom
MKLDSCRIPT      ?= ./tools/mkldscript
DISASSEMBLER    ?= ./tools/py_mips_disasm/simpleDisasm.py

OPTFLAGS := 
ASFLAGS := -march=vr4300 -32 -Iinclude
MIPS_VERSION := -mips2


#### Files ####

BASE_DIR       := $(GAME)/$(VERSION)

# ROM image
BASE_ROM       := $(GAME)/$(GAME)_$(VERSION).z64
ROM            := $(GAME)_$(VERSION)_uncompressed.z64
ELF            := $(BASE_DIR)/build/$(ROM:.z64=.elf)
# description of ROM segments
SPEC           := $(BASE_DIR)/spec_$(VERSION)
LDSCRIPT       := $(BASE_DIR)/build/ldscript_$(VERSION).txt


ASM_DIRS       := $(shell find $(BASE_DIR)/asm/ -type d -not -path "$(BASE_DIR)/asm/functions*")

S_FILES        := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
BASEROM_FILES  := $(wildcard $(BASE_DIR)/baserom/*)
O_FILES        := $(subst $(BASE_DIR)/,$(BASE_DIR)/build/,$(S_FILES:.s=.o)) \
                  $(subst $(BASE_DIR)/,$(BASE_DIR)/build/,$(BASEROM_FILES:.bin=.o))

DISASM_LIST    := $(shell cat $(GAME)/tables/disasm_list.txt) \
                  $(shell [ -f $(BASE_DIR)/tables/disasm_list.txt ] && cat $(BASE_DIR)/tables/disasm_list.txt)

CSV_FILES      := $(DISASM_LIST:%=$(BASE_DIR)/tables/files_%.csv) \
                  $(BASE_DIR)/tables/functions.csv $(BASE_DIR)/tables/variables.csv
DISASM_TARGETS := $(DISASM_LIST:%=$(BASE_DIR)/asm/text/%/.disasm)


# create asm directories
$(shell mkdir -p $(BASE_DIR)/baserom/ $(BASE_DIR)/asm/text $(BASE_DIR)/asm/data)

# create build directories
$(shell mkdir -p $(BASE_DIR)/build/baserom $(foreach dir,$(ASM_DIRS),$(subst $(BASE_DIR)/,$(BASE_DIR)/build/,$(dir))))


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


## Disassembly
$(BASE_DIR)/asm/text/%/.disasm: $(BASE_DIR)/baserom/% $(BASE_DIR)/tables/variables.csv $(BASE_DIR)/tables/functions.csv $(BASE_DIR)/tables/files_%.csv
	$(RM) -rf $(BASE_DIR)/asm/text/$* $(BASE_DIR)/asm/data/$* $(BASE_DIR)/context/$*.txt
	$(DISASSEMBLER) $< $(BASE_DIR)/asm/text/$* -q --data-output $(BASE_DIR)/asm/data/$* --split-functions $(BASE_DIR)/asm/functions/$* --variables $(BASE_DIR)/tables/variables.csv --functions $(BASE_DIR)/tables/functions.csv --constants $(GAME)/tables/constants.csv --file-splits $(BASE_DIR)/tables/files_$*.csv  --save-context $(BASE_DIR)/context/$*.txt --constants $(BASE_DIR)/tables/constants_$*.csv
	@touch $@
