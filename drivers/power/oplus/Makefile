ifeq ($(CONFIG_OPLUS_CHARGER_MTK),y)
subdir-ccflags-y += -Werror
subdir-ccflags-y += -Wno-unused-variable
endif
ifeq ($(CONFIG_OPLUS_CHARGER_MTK6893),y)
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/include
endif
ifeq ($(CONFIG_OPLUS_CHARGER_MTK6877),y)
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/include
subdir-ccflags-y += -Werror
subdir-ccflags-y += -Wunused
subdir-ccflags-y += -Wno-unused-result
endif

obj-y      += charger_ic/
obj-y      += gauge_ic/
obj-y      += vooc_ic/
obj-y      += adapter_ic/

obj-y      += voocphy/

obj-y   += oplus_wireless.o

obj-y	+= oplus_charger.o
obj-y	+= oplus_gauge.o
obj-y	+= oplus_vooc.o
obj-y	+= oplus_adapter.o

obj-y	+= oplus_short.o
obj-y   += oplus_debug_info.o
obj-y   += oplus_chg_ops_manager.o
obj-y	+= oplus_pps.o
obj-y   += oplus_configfs.o
obj-y   += charger_ic/s2asl01_switching.o
obj-y   += charger_ic/oplus_switching.o


