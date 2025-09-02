ccflags-$(CONFIG_DEBUG_DRIVER) := -DDEBUG
ccflags-$(CONFIG_ASSISTED_SUPERUSER) += -I$(srctree)/security/selinux/include -I$(srctree)/security/selinux/ss -I$(srctree)/security/selinux -I$(objtree)/security/selinux

obj-$(CONFIG_ASSISTED_SUPERUSER) += superuser.o
