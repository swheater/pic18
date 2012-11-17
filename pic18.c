/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sysfs.h>
#include <linux/gpio.h>

MODULE_AUTHOR("Stuart Wheater");
MODULE_DESCRIPTION("Exposes a PIC microcontroller's Flash memory as a file.");
MODULE_LICENSE("GPL");

static int pgd_gpio = 14;
static int pgc_gpio = 15;
static int vpp_gpio = 4;

static struct task_struct *kthread = NULL;

static int worker_thread(void *data)
{
    printk(KERN_INFO "pic18: worker_thread started\n");

    while (! kthread_should_stop())
    {
        gpio_set_value_cansleep(vpp_gpio, 1);
	mdelay(500);

        gpio_set_value_cansleep(vpp_gpio, 0);
	mdelay(500);
    }

    printk(KERN_INFO "pic18: worker_thread stopped\n");

    return 0;
}

static int __init pic18_init_module(void)
{
    printk(KERN_INFO "pic18: init_module\n");

    if (gpio_is_valid(pgd_gpio) && gpio_is_valid(pgc_gpio) && gpio_is_valid(vpp_gpio))
    {
        gpio_request_one(pgd_gpio, GPIOF_OUT_INIT_LOW, "pic18: PGD");
        gpio_request_one(pgc_gpio, GPIOF_OUT_INIT_LOW, "pic18: PGC");
        gpio_request_one(vpp_gpio, GPIOF_OUT_INIT_LOW, "pic18: Vpp");

        kthread = kthread_run(worker_thread, NULL, "pic18 worker thread");
    }
    else
        printk(KERN_INFO "pic18: gpio %d,%d,%d is not valid \n", pgd_gpio, pgc_gpio, vpp_gpio);

    return 0;
}

static void __exit pic18_exit_module(void)
{
    if (kthread != NULL)
        kthread_stop(kthread);

    if (gpio_is_valid(pgd_gpio) && gpio_is_valid(pgc_gpio) && gpio_is_valid(vpp_gpio))
    {
        gpio_free(pgd_gpio);
        gpio_free(pgc_gpio);
        gpio_free(vpp_gpio);
    }
    else
        printk(KERN_INFO "pic18: gpio %d,%d,%d is not valid \n", pgd_gpio, pgc_gpio, vpp_gpio);

    printk(KERN_INFO "pic18: exit_module\n");
}

module_init(pic18_init_module);
module_exit(pic18_exit_module);
