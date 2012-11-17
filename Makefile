#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

RM   = rm
MAKE = make

obj-m += pic18.o

KERNEL_RELEASE_VERSION = $(shell uname -r)

all:
	$(MAKE) -C /lib/modules/$(KERNEL_RELEASE_VERSION)/build M=$(PWD) modules

clean:
	$(MAKE) -C /lib/modules/$(KERNEL_RELEASE_VERSION)/build M=$(PWD) clean
	$(RM) -f *~