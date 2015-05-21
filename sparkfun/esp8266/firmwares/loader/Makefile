SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# todo: define path depending on the platform
BUILT_IDE_DIR ?= ../../../../../build/macosx/work/Arduino.app/Contents/Java

GIT_REV := $(shell git rev-parse --short HEAD)

CPPFLAGS+=-Iinclude -Isrc/include -DREVISION_STRING=\"$(GIT_REV)\"
CFLAGS += -std=c99
CXXFLAGS += -std=c++0x

OBJ_FILES := main.o
					
OBJ_PATHS := $(addprefix $(SRC_DIR)/,$(OBJ_FILES))

TOOLS_DIR := $(BUILT_IDE_DIR)/hardware/tools/esp8266

XTENSA_TOOCHAIN := $(TOOLS_DIR)/xtensa-lx106-elf/bin
TOOLCHAIN_PREFIX := $(XTENSA_TOOCHAIN)/xtensa-lx106-elf-
CC := $(TOOLCHAIN_PREFIX)gcc
CXX := $(TOOLCHAIN_PREFIX)g++
AR := $(TOOLCHAIN_PREFIX)ar
LD := $(TOOLCHAIN_PREFIX)gcc
OBJCOPY := $(TOOLCHAIN_PREFIX)objcopy
SIZE := $(TOOLCHAIN_PREFIX)size
STRIP := $(TOOLCHAIN_PREFIX)strip
ESPTOOL := $(TOOLS_DIR)/esptool

XTENSA_LIBS ?= $(shell $(CC) -print-sysroot)

SDK_BASE ?= $(TOOLS_DIR)/sdk

CPPFLAGS += -I$(XTENSA_LIBS)/include \
		-I$(SDK_BASE)/include \
		-I$(SRC_DIR)

LDFLAGS  += -L$(XTENSA_LIBS)/lib \
		-L$(XTENSA_LIBS)/arch/lib \
		-L$(SDK_BASE)/lib

LIBS := c gcc hal phy net80211 wpa main pp lwip

#-Werror 
CFLAGS += -std=c99 -Os -g -Wpointer-arith -Wno-implicit-function-declaration -Wl,-EL -fno-inline-functions -nostdlib -mlongcalls -mno-text-section-literals  
CXXFLAGS += -c -Os -mlongcalls -mtext-section-literals -fno-exceptions -fno-rtti -std=c++11 -MMD


CPPFLAGS += -DESP_PLATFORM=1 -D__ets__ -DICACHE_FLASH

LDFLAGS	+= -nostdlib -Wl,--no-check-sections -u call_user_start -Wl,-static

LD_SCRIPT := loader.ld

APP_AR:=$(BIN_DIR)/loader.a
APP_OUT:=$(BIN_DIR)/loader.elf
APP_FW_S1 := $(BIN_DIR)/_loader_segm_1.bin
APP_FW_S2 := $(BIN_DIR)/_loader_segm_2.bin
APP_FW := $(BIN_DIR)/loader.bin

# $(LWIP_AR) : $(LWIP_OBJ_PATHS)
# 	for file in $(LWIP_OBJ_PATHS); do \
# 		$(OBJCOPY) \
# 		--rename-section .text=.irom0.text \
# 		--rename-section .literal=.irom0.literal \
# 		$$file; \
# 	done
# 	$(AR) cru $@ $^

$(APP_AR): $(OBJ_PATHS) $(SDK_DRIVER_OBJ_PATHS)
	$(AR) cru $@ $^

$(APP_AR): | $(BIN_DIR)

$(APP_OUT): $(APP_AR) $(LWIP_AR)
	$(LD) -T$(LD_SCRIPT) $(LDFLAGS) -Wl,--start-group $(addprefix -l,$(LIBS)) $(APP_AR) -Wl,--end-group -o $@
	$(SIZE) -A -x $@ | head -n 7


$(APP_FW_S1): $(APP_OUT)
	$(ESPTOOL) -eo $(APP_OUT) -bo $@ -bs .text -bs .data -bs .rodata -bc -ec

$(APP_FW_S2): $(APP_OUT)
	$(ESPTOOL) -eo $(APP_OUT) -es .irom0.text $@ -ec

$(APP_FW): $(APP_FW_S1) $(APP_FW_S2)
	dd if=/dev/zero ibs=4k count=56 | LC_ALL=C tr "\000" "\377" >$(APP_FW)
	dd if=$(APP_FW_S1) of=$(APP_FW) bs=4k seek=0 conv=notrunc
	dd if=$(APP_FW_S2) of=$(APP_FW) bs=4k seek=9 conv=notrunc

firmware: $(APP_FW_S1) $(APP_FW_S2) $(APP_FW)

all: firmware

.PHONY: all firmware


$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(SRC_DIR)/*.o
	rm -f $(SRC_DIR)/*.d
	rm -rf $(BIN_DIR)

.PHONY: clean

