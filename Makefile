#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

RM   = rm
MAKE = make

obj-m   := pic18.o
pic18-y := pic18_lifecycle.o pic18_sysfs.o pic18_worker.o pic18_io.o

KERNEL_RELEASE_VERSION = $(shell uname -r)

all:
	$(MAKE) -C /lib/modules/$(KERNEL_RELEASE_VERSION)/build M=$(PWD) modules

clean: tidy
	$(MAKE) -C /lib/modules/$(KERNEL_RELEASE_VERSION)/build M=$(PWD) clean

tidy:
	$(RM) -f *~
