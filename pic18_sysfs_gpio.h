/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#ifndef _PIC18_SYSFS_GPIO_H_
#define _PIC18_SYSFS_GPIO_H_

#include <linux/types.h>
#include <linux/kobject.h>

extern ssize_t pic18_gpio_pgd_show(struct kobject *kobject, struct kobj_attribute *attribute, char *buffer);
extern ssize_t pic18_gpio_pgd_store(struct kobject *kobject, struct kobj_attribute *attribute, const char *buffer, size_t count);

extern ssize_t pic18_gpio_pgc_show(struct kobject *kobject, struct kobj_attribute *attribute, char *buffer);
extern ssize_t pic18_gpio_pgc_store(struct kobject *kobject, struct kobj_attribute *attribute, const char *buffer, size_t count);

extern ssize_t pic18_gpio_vpp_show(struct kobject *kobject, struct kobj_attribute *attribute, char *buffer);
extern ssize_t pic18_gpio_vpp_store(struct kobject *kobject, struct kobj_attribute *attribute, const char *buffer, size_t count);

#endif
