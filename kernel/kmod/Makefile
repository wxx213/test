
#makefile for the hello.c                                                       


obj-m := hello.o
CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := $(shell uname -r)
LINUX_KERNEL_PATH := /usr/src/linux-headers-$(LINUX_KERNEL)
all:
	$(MAKE) -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	rm -f *.ko
	rm -f *.o
	rm -f hello.mod.c modules.order Module.symvers
	rm -rf .hello.mod.o.cmd  .hello.o.cmd .tmp_versions .hello.ko.cmd
