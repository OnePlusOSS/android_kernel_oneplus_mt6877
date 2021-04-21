
	ifeq ($(CONFIG_OPLUS_CHARGER_MTK6877),y)
		MTK_PLATFORM := $(subst ",,$(CONFIG_MTK_PLATFORM))
		subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat/$(MTK_PLATFORM)/include
		subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat
		subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/pmic/include
		subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/typec/tcpc/inc
		subdir-ccflags-y += -I$(srctree)/drivers/power/supply/mediatek/misc/
		obj-y   += oplus_mp2650.o
		obj-y   += oplus_charge_pump.o
		obj-y   += oplus_usbtemp.o
		obj-y   += oplus_battery_mtk6877R.o

	endif

	obj-y   += oplus_short_ic.o
