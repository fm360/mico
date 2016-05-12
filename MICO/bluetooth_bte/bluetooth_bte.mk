#
# $ Copyright Broadcom Corporation $
#

ifneq ($(wildcard $(CURDIR)Lib_bluetooth_bte.$(RTOS).NetX_Duo.$(HOST_ARCH).release.a),)
#$(error build from lib $(CURDIR)Lib_bluetooth_bte.ThreadX.NetX_Duo.$(HOST_ARCH).release.a)
include $(CURDIR)/bluetooth_bte_app.mk
$(NAME)_PREBUILT_LIBRARY := Lib_bluetooth_bte.ThreadX.NetX_Duo.$(HOST_ARCH).release.a

#ifdef USE_EXTERNAL_HCD
$(NAME)_RESOURCES += patchram/$(BT_CHIP)/$(BT_CHIP)$(BT_CHIP_REVISION).hcd
#endif

else
# Build from source (Broadcom internal)
#$(error build from source $(CURDIR)Lib_bluetooth_bte.$(RTOS).NetX_Duo.$(HOST_ARCH).release.a)
#$(error build from source broadcom internal only)
include $(CURDIR)/bluetooth_bte_src.mk
endif # ifneq ($(wildcard $(CURDIR)bt_stack.$(HOST_ARCH).release.a),)

#GLOBAL_INCLUDES := .
