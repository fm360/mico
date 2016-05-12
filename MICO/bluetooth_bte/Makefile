#
# $ Copyright Broadcom Corporation $
#
NAME    := bluetooth_bte
ALWAYS_OPTIMISE := 1

BUILD_BTE_LIB = 1

SOURCE_ROOT :=../../

BT_CHIP              := 20702
BT_CHIP_REVISION     := B0

BYPASS_LIBRARY_POISON_CHECK=1

include bluetooth_bte_src.mk


CFLAGS += -I$(SOURCE_ROOT)WICED/WWD/include
CFLAGS += -I$(SOURCE_ROOT)WICED/WWD/include/network
CFLAGS += -I$(SOURCE_ROOT)WICED/platform/include
CFLAGS += -I$(SOURCE_ROOT)WICED
CFLAGS += -I$(SOURCE_ROOT)include
CFLAGS += -I$(SOURCE_ROOT)WICED/RTOS/$(RTOS)/WICED
CFLAGS += -I$(SOURCE_ROOT)WICED/RTOS/$(RTOS)/WWD
CFLAGS += -I$(SOURCE_ROOT)WICED/network/$(NETWORK)/WICED
CFLAGS += -I$(SOURCE_ROOT)WICED/network/$(NETWORK)/WWD
CFLAGS += -I$(SOURCE_ROOT)WICED/WWD/internal/bus_protocols/$(BUS)
CFLAGS += -I$(SOURCE_ROOT)WICED/WWD/internal/chips/43362A2
CFLAGS += -I$(SOURCE_ROOT)tools/prebuild_stubs
CFLAGS += -I$(SOURCE_ROOT)WICED/security/BESL/crypto
CFLAGS += -I$(SOURCE_ROOT)WICED/security/BESL/include
CFLAGS += -I$(SOURCE_ROOT)libraries/utilities/ring_buffer
CFLAGS += -I$(SOURCE_ROOT)libraries/bluetooth_bte/include
CFLAGS += -I$(SOURCE_ROOT)libraries/bluetooth/include

ifeq ($(HOST_ARCH),ARM_CM4)

CFLAGS += -I$(SOURCE_ROOT)WICED/platform/MCU/
CFLAGS += -I$(SOURCE_ROOT)WICED/platform/MCU/STM32F4xx/peripherals/
CFLAGS += -I$(SOURCE_ROOT)WICED/platform/MCU/STM32F4xx/
CFLAGS += -I$(SOURCE_ROOT)WICED/platform/MCU/STM32F4xx/peripherals/libraries/
CFLAGS += -I$(SOURCE_ROOT)WICED/platform/ARM_CM4/CMSIS/
CFLAGS += -I$(SOURCE_ROOT)WICED/platform/MCU/STM32F4xx/peripherals/libraries/inc/
CFLAGS += -I$(SOURCE_ROOT)platforms/WSDB751/
CFLAGS += -I$(SOURCE_ROOT)WICED/platform/MCU/STM32F4xx/WAF/

else

CFLAGS += -I$(SOURCE_ROOT)WICED/platform/MCU/
CFLAGS += -I$(SOURCE_ROOT)WICED/platform/ARM_CM3/CMSIS/
CFLAGS += -I$(SOURCE_ROOT)platforms/WSDB734AP6210/
CFLAGS += -I$(SOURCE_ROOT)WICED/platform/MCU/STM32F2xx/peripherals/
CFLAGS += -I$(SOURCE_ROOT)WICED/platform/MCU/STM32F2xx/
CFLAGS += -I$(SOURCE_ROOT)WICED/platform/MCU/STM32F2xx/peripherals/libraries/
CFLAGS += -I$(SOURCE_ROOT)WICED/platform/MCU/STM32F2xx/peripherals/libraries/inc/
CFLAGS += -I$(SOURCE_ROOT)WICED/platform/MCU/STM32F2xx/WAF/
endif

#GLOBAL_INCLUDES :=

SOURCES := $($(NAME)_SOURCES)
CFLAGS += $(addprefix -I,$(GLOBAL_INCLUDES)) $(addprefix -D,$(GLOBAL_DEFINES)) $(addprefix -I,$($(NAME)_INCLUDES)) $(addprefix -D,$($(NAME)_DEFINES)) $($(NAME)_CFLAGS)


KEEP_LIST_DIR := $(SOURCE_ROOT)libraries/bluetooth_bte

KEEP_LIST:= $(NAME)*.a \
            bluetooth_bte.mk

include $(SOURCE_ROOT)tools/makefiles/wiced_library.mk




