/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <linux/kernel.h>
#include <linux/gpio.h>

#include "pic18_io.h"

#define INVALID_GPIO (-1)

static int pgd_gpio = 14;
static int pgc_gpio = 15;
static int vpp_gpio = 4;

static int pic18_gpio_request(int gpio, int flags, const char *label)
{
    if (gpio_is_valid(gpio))
    {
        if (gpio_request_one(gpio, flags, label))
        {
            printk(KERN_INFO "pic18_io: failed to request gpio %d (%s)\n", gpio, label);

            return INVALID_GPIO;
        }
    }
    else
    {
        printk(KERN_INFO "pic18_io: invalid gpio %d (%s)\n", gpio, label);

        return INVALID_GPIO;
    }

    return gpio;
}

static void pic18_gpio_free(int gpio, const char *label)
{
    if (gpio != INVALID_GPIO)
        gpio_free(gpio);
}

int pic18_io_init(void)
{
    printk(KERN_INFO "pic18_io: pic18_io_init\n");

    pgd_gpio = pic18_gpio_request(pgd_gpio, GPIOF_OUT_INIT_LOW, "PGD");
    pgc_gpio = pic18_gpio_request(pgc_gpio, GPIOF_OUT_INIT_LOW, "PGC");
    vpp_gpio = pic18_gpio_request(vpp_gpio, GPIOF_OUT_INIT_HIGH, "Vpp");

    return 0;
}

void pic18_io_setvpp(void)
{
    gpio_set_value(vpp_gpio, 1);
}

void pic18_io_clearvpp(void)
{
    gpio_set_value(vpp_gpio, 0);
}

void pic18_io_exit(void)
{
    printk(KERN_INFO "pic18_io: pic18_io_exit\n");

    pic18_gpio_free(pgd_gpio, "PGD");
    pic18_gpio_free(pgc_gpio, "PGC");
    pic18_gpio_free(vpp_gpio, "Vpp");
}
