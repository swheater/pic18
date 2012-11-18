/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <linux/kernel.h>
#include <linux/sysfs.h>

#include "pic18_io.h"

int pic18_sysfs_init(void)
{
    printk(KERN_INFO "pic18_sysfs: pic18_sysfs_init\n");

    return 0;
}

void pic18_sysfs_exit(void)
{
    printk(KERN_INFO "pic18_sysfs: pic18_sysfs_exit\n");
}
