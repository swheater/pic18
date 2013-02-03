/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#ifndef _PIC18_SYSFS_FLASH_H_
#define _PIC18_SYSFS_FLASH_H_

#include <linux/types.h>
#include <linux/kobject.h>

extern ssize_t pic18_flash_show(struct kobject *kobject, struct kobj_attribute *attribute, char *buffer);
extern ssize_t pic18_flash_store(struct kobject *kobject, struct kobj_attribute *attribute, const char *buffer, size_t count);

#endif
