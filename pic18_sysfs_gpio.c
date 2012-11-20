/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <linux/types.h>
#include <linux/kobject.h>

#include "pic18_io.h"
#include "pic18_sysfs_gpio.h"

ssize_t pic18_gpio_pgd_show(struct kobject *kobject, struct kobj_attribute *attribute, char *buffer)
{
    return sprintf(buffer, "%d\n", pic18_io_get_gpio_pgd());
}

ssize_t pic18_gpio_pgd_store(struct kobject *kobject, struct kobj_attribute *attribute, const char *buffer, size_t count)
{
    int gpio_pgd;

    sscanf(buffer, "%du", &gpio_pgd);
    pic18_io_set_gpio_pgd(gpio_pgd);

    return count;
}

ssize_t pic18_gpio_pgc_show(struct kobject *kobject, struct kobj_attribute *attribute, char *buffer)
{
    return sprintf(buffer, "%d\n", pic18_io_get_gpio_pgc());
}

ssize_t pic18_gpio_pgc_store(struct kobject *kobject, struct kobj_attribute *attribute, const char *buffer, size_t count)
{
    int gpio_pgc;

    sscanf(buffer, "%du", &gpio_pgc);
    pic18_io_set_gpio_pgc(gpio_pgc);

    return count;
}

ssize_t pic18_gpio_vpp_show(struct kobject *kobject, struct kobj_attribute *attribute, char *buffer)
{
    return sprintf(buffer, "%d\n", pic18_io_get_gpio_vpp());
}

ssize_t pic18_gpio_vpp_store(struct kobject *kobject, struct kobj_attribute *attribute, const char *buffer, size_t count)
{
    int gpio_vpp;

    sscanf(buffer, "%du", &gpio_vpp);
    pic18_io_set_gpio_vpp(gpio_vpp);

    return count;
}
