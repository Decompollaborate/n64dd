CFLAGS := -Wall -Wextra -pedantic -std=c99 -g -O2
PROGRAMS := elf2rom mkldscript yaz0

ifeq ($(shell command -v clang >/dev/null 2>&1; echo $$?),0)
  CC := clang
else
  CC := gcc
endif

LLD ?= 0

ifeq ($(shell command -v ld.lld >/dev/null 2>&1; echo $$?),0)
  LLD := 1
endif

ifneq ($(LLD),0)
  CFLAGS += -fuse-ld=lld
endif

all: $(PROGRAMS)

clean:
	$(RM) $(PROGRAMS) $(addsuffix .exe,$(PROGRAMS))

distclean: clean

.PHONY: all clean distclean

elf2rom_SOURCES    := elf2rom.c elf32.c n64chksum.c util.c
mkldscript_SOURCES := mkldscript.c spec.c util.c
yaz0_SOURCES       := yaz0tool.c yaz0.c util.c

define COMPILE =
$(1): $($1_SOURCES)
	$(CC) $(CFLAGS) $$^ -o $$@
endef

$(foreach p,$(PROGRAMS),$(eval $(call COMPILE,$(p))))
