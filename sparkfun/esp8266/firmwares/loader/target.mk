include $(TARGET_DIR)/lwip.mk

TARGET_OBJ_FILES := 	main.o \
			uart.o \
			interface_commands.o \
			info_commands.o \
			wifi_commands.o \
			ip_commands.o \
			ip_commands_info.o \
			ip_commands_common.o \
			ip_commands_socket.o \
			config_store.o \


TARGET_OBJ_PATHS := $(addprefix $(TARGET_DIR)/,$(TARGET_OBJ_FILES))

TOOLCHAIN_PREFIX ?= xtensa-lx106-elf-
XTENSA_TOOCHAIN := ../xtensa-lx106-elf/bin
CC := $(TOOLCHAIN_PREFIX)gcc
AR := $(TOOLCHAIN_PREFIX)ar
LD := $(TOOLCHAIN_PREFIX)gcc
OBJCOPY := $(TOOLCHAIN_PREFIX)objcopy


XTENSA_LIBS ?= $(shell $(CC) -print-sysroot)

ESPTOOL ?= ../esptool/esptool

SDK_BASE ?= ../esp_iot_sdk_v0.9.3

SDK_EXAMPLE_DIR := $(SDK_BASE)/examples/IoT_Demo

SDK_DRIVER_OBJ_FILES := 
SDK_DRIVER_OBJ_PATHS := $(addprefix $(SDK_AT_DIR)/driver/,$(SDK_DRIVER_OBJ_FILES))

CPPFLAGS += 	-I$(XTENSA_LIBS)/include \
		-I$(SDK_BASE)/include \
		-I$(TARGET_DIR) \
		-I$(LWIP_DIR)/include \
		-I$(SDK_EXAMPLE_DIR)/include

LDFLAGS  += 	-L$(XTENSA_LIBS)/lib \
		-L$(XTENSA_LIBS)/arch/lib \
		-L$(SDK_BASE)/lib

CFLAGS+=-std=c99
CPPFLAGS+=-DESP_PLATFORM=1

LIBS := c gcc hal phy net80211 wpa main json ssl pp

#-Werror 
CFLAGS += -Os -g -O2 -Wpointer-arith -Wno-implicit-function-declaration -Wl,-EL -fno-inline-functions -nostdlib -mlongcalls -mno-text-section-literals  -D__ets__ -DICACHE_FLASH

LDFLAGS	+= -nostdlib -Wl,--no-check-sections -u call_user_start -Wl,-static

LD_SCRIPT := $(SDK_BASE)/ld/eagle.app.v6.ld

LWIP_AR:=$(BIN_DIR)/lwipc.a

APP_AR:=$(BIN_DIR)/app.a
APP_OUT:=$(BIN_DIR)/app.out
APP_FW_1 := $(BIN_DIR)/0x00000.bin
APP_FW_2 := $(BIN_DIR)/0x40000.bin
FULL_FW := $(BIN_DIR)/firmware.bin

$(LWIP_AR) : $(LWIP_OBJ_PATHS)
	for file in $(LWIP_OBJ_PATHS); do \
		$(OBJCOPY) \
		--rename-section .text=.irom0.text \
		--rename-section .literal=.irom0.literal \
		$$file; \
	done
	$(AR) cru $@ $^

$(LWIP_AR): | $(BIN_DIR)

$(APP_AR): $(COMMON_OBJ_PATHS) $(TARGET_OBJ_PATHS) $(SDK_DRIVER_OBJ_PATHS)
	$(AR) cru $@ $^

$(APP_AR): | $(BIN_DIR)

$(APP_OUT): $(APP_AR) $(LWIP_AR)
	$(LD) -T$(LD_SCRIPT) $(LDFLAGS) -Wl,--start-group $(addprefix -l,$(LIBS)) $(APP_AR) $(LWIP_AR) -Wl,--end-group -o $@

$(APP_FW_1): $(APP_OUT)
	$(ESPTOOL) -eo $(APP_OUT) -bo $@ -bs .text -bs .data -bs .rodata -bc -ec

$(APP_FW_2): $(APP_OUT)
	$(ESPTOOL) -eo $(APP_OUT) -es .irom0.text $@ -ec

$(FULL_FW): $(APP_FW_1) $(APP_FW_2)
	dd if=/dev/zero ibs=4k count=124 | LC_ALL=C tr "\000" "\377" >$(FULL_FW)
	dd if=$(APP_FW_1) of=$(FULL_FW) bs=4k seek=0 conv=notrunc
	dd if=$(APP_FW_2) of=$(FULL_FW) bs=4k seek=64 conv=notrunc

firmware: $(APP_FW_1) $(APP_FW_2) $(FULL_FW)

all: firmware

clean-driver:
	rm -r $(SDK_DRIVER_OBJ_PATHS)

clean-lwip:
	rm -rf $(LWIP_OBJ_PATHS)
	rm -rf $(LWIP_AR)

clean: clean-lwip

#clean:	clean-driver

.PHONY: all firmware
