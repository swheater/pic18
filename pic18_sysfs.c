/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>

#include "pic18_io.h"
#include "pic18_sysfs_gpio.h"
#include "pic18_sysfs_flash.h"
#include "pic18_sysfs.h"

static struct kobject        *pic18_kobject;

static struct kobj_attribute pgd_attribute   = __ATTR(pgd, 0666, pic18_gpio_pgd_show, pic18_gpio_pgd_store);
static struct kobj_attribute pgc_attribute   = __ATTR(pgc, 0666, pic18_gpio_pgc_show, pic18_gpio_pgc_store);
static struct kobj_attribute vpp_attribute   = __ATTR(vpp, 0666, pic18_gpio_vpp_show, pic18_gpio_vpp_store);
static struct kobj_attribute flash_attribute = __ATTR(flash, 0666, pic18_flash_show, pic18_flash_store);

static struct attribute *attributes[] =
{
    &pgd_attribute.attr,
    &pgc_attribute.attr,
    &vpp_attribute.attr,
    &flash_attribute.attr,
    NULL,
};

static struct attribute_group attribute_group = { .attrs = attributes, };

int pic18_sysfs_init(void)
{
    int result;

    printk(KERN_INFO "pic18_sysfs: pic18_sysfs_init\n");

    pic18_kobject = kobject_create_and_add("pic18", kernel_kobj);
    if (! pic18_kobject)
        return 1;

    result = sysfs_create_group(pic18_kobject, &attribute_group);
    if (result)
        kobject_put(pic18_kobject);

    return result;
}

void pic18_sysfs_exit(void)
{
    printk(KERN_INFO "pic18_sysfs: pic18_sysfs_exit\n");

    kobject_put(pic18_kobject);
}
