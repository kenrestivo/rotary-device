
ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
include Kbuild
else
# normal makefile
KDIR ?= /mnt/externalsata/raspberry/linux-kernel
default:
	$(MAKE) -C $(KDIR) M=$$PWD ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-  
endif


## install into /lib/modules/`uname -r`/kernel/drivers/input/misc
