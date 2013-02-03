/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "pic18_io.h"
#include "pic18_worker.h"
#include "pic18_sysfs.h"

MODULE_AUTHOR("Stuart Wheater");
MODULE_DESCRIPTION("Exposes a PIC microcontroller's Flash memory as a file.");
MODULE_LICENSE("GPL");

static int __init pic18_lifecycle_init(void)
{
    printk(KERN_INFO "pic18_lifecycle_init\n");

    if (pic18_sysfs_init())
        return 1;

    if (pic18_io_init())
    {
        pic18_sysfs_exit();
        return 2;
    }

    if (pic18_worker_init())
    {
        pic18_io_exit();
        pic18_sysfs_exit();
        return 2;
    }

    return 0;
}

static void __exit pic18_lifecycle_exit(void)
{
    printk(KERN_INFO "pic18_lifecycle_exit\n");

    pic18_worker_exit();
    pic18_io_exit();
    pic18_sysfs_exit();
}

module_init(pic18_lifecycle_init);
module_exit(pic18_lifecycle_exit);
