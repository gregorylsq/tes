KERNELDIR := /usr/src/linux-headers-5.4.0-53-generic#/home/greg/linux_kernel/linux-source-5.4.0

CURRENT_PATH := $(shell pwd)

obj-m := hello.o

build: kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean
