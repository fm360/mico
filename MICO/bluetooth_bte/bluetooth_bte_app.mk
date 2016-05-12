#
# $ Copyright Broadcom Corporation $
#
NAME := Lib_bluetooth_bte

################################################################################
# Supported variants                                                           #
################################################################################

SUPPORTED_BT_CHIPS           := 20702B0 43341B0 20710A1 4343A0 43438A0


################################################################################
# Default settings                                                             #
################################################################################

COMPLETE_BT_CHIP_NAME := BCM$(BT_CHIP)$(BT_CHIP_REVISION)

BTEDIR := BTE
PROTO_DISP_DIR := BTE/proto_disp

PROTODISP_INCLUDES := \
		$(PROTO_DISP_DIR)

BTEINCLUDES := \
		$(BTEDIR)/Components/hcis \
		$(BTEDIR)/Components/hcis/include \
		$(BTEDIR)/Components/stack/include \
		$(BTEDIR)/Components/stack/avrc \
		$(BTEDIR)/Components/stack/avct \
		$(BTEDIR)/Components/stack/avdt \
		$(BTEDIR)/Components/stack/a2dp \
		$(BTEDIR)/Components/stack/btm \
		$(BTEDIR)/Components/stack/brcm \
		$(BTEDIR)/Components/stack/l2cap \
		$(BTEDIR)/Components/stack/sdp \
		$(BTEDIR)/Components/stack/gap \
		$(BTEDIR)/Components/stack/gatt \
		$(BTEDIR)/Components/stack/gatt/legattdb/inc \
		$(BTEDIR)/Components/stack/smp \
		$(BTEDIR)/Components/stack/wbt \
		$(BTEDIR)/Components/stack/wiced \
		$(BTEDIR)/Components/rpc/include


$(NAME)_SOURCES := 	$(BTEDIR)/Projects/bte/embedded/wiced/lib/fwpatches/$(COMPLETE_BT_CHIP_NAME)/brcm_patch.c \
					$(BTEDIR)/Projects/bte/embedded/wiced/lib/wiced_post_reset.c \
					$(BTEDIR)/Projects/bte/embedded/wiced/lib/wiced_bt_hcd.c \
					$(BTEDIR)/Components/udrv/wiced/upio_wiced.c \
					$(BTEDIR)/Components/udrv/wiced/userial_wiced.c

$(NAME)_INCLUDES := \
					$(BTEDIR)/Projects/bte/embedded/wiced/lib \
					$(BTEINCLUDES)

$(NAME)_DEFINES := WICED_BTE_LIB

GLOBAL_DEFINES += 	BUILDCFG BLUETOOTH_BTE

GLOBAL_INCLUDES += \
					$(INCLUDE_PATH_PREFIX). \
					$(INCLUDE_PATH_PREFIX)include \
					$(INCLUDE_PATH_PREFIX)$(BTEDIR)/Components/gki/common \
					$(INCLUDE_PATH_PREFIX)$(BTEDIR)/Components/gki/wiced \
					$(INCLUDE_PATH_PREFIX)$(BTEDIR)/Components/udrv/include \
					$(INCLUDE_PATH_PREFIX)$(BTEDIR)/Projects/bte/main \
					$(INCLUDE_PATH_PREFIX)$(BTEDIR)/Projects/bte/embedded/wiced/include \
					$(INCLUDE_PATH_PREFIX)$(BTEDIR)/Components/stack/include \
					$(INCLUDE_PATH_PREFIX)$(PROTODISP_INCLUDES)
