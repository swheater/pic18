/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <linux/types.h>
#include <linux/kobject.h>

#include "pic18_io.h"
#include "pic18_sysfs_flash.h"

ssize_t pic18_flash_show(struct kobject *kobject, struct kobj_attribute *attribute, char *buffer)
{
    return pic18_io_get_flash(buffer);
}

ssize_t pic18_flash_store(struct kobject *kobject, struct kobj_attribute *attribute, const char *buffer, size_t count)
{
    pic18_io_set_flash(buffer, count);

    return count;
}
