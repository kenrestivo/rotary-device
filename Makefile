export PATH := $(PATH):/mnt/externalsata/raspberry/build-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin




ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
include Kbuild
else
# normal makefile
KDIR ?= /mnt/externalsata/raspberry/linux-kernel
default:
	$(MAKE) -C $(KDIR) M=$$PWD ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- 
# Module specific targets
endif
