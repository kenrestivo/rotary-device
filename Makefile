export PATH := $(PATH):/mnt/sdcard/src-cache/raspberry-build/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin




ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
include Kbuild
else
# normal makefile
KDIR ?= /mnt/sdcard/src-cache/raspberry-kernel
default:
	$(MAKE) -C $(KDIR) M=$$PWD ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-  
endif
