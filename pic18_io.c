/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <linux/types.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/gpio.h>

#include "pic18_io.h"

#define INVALID_GPIO (-1)

static int  pgd_gpio = 14;
static int  pgc_gpio = 15;
static int  vpp_gpio = 4;
static char flash[4096];

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

int pic18_io_get_gpio_pgd(void)
{
    return pgd_gpio;
}

void pic18_io_set_gpio_pgd(int gpio)
{
    pic18_gpio_free(pgd_gpio, "PGD");
    pgd_gpio = gpio;
    pgd_gpio = pic18_gpio_request(pgd_gpio, GPIOF_OUT_INIT_LOW, "PGD");
}

int pic18_io_get_gpio_pgc(void)
{
    return pgc_gpio;
}

void pic18_io_set_gpio_pgc(int gpio)
{
    pic18_gpio_free(pgc_gpio, "PGC");
    pgc_gpio = gpio;
    pgc_gpio = pic18_gpio_request(pgc_gpio, GPIOF_OUT_INIT_LOW, "PGC");
}

int pic18_io_get_gpio_vpp(void)
{
    return vpp_gpio;
}

void pic18_io_set_gpio_vpp(int gpio)
{
    pic18_gpio_free(vpp_gpio, "Vpp");
    vpp_gpio = gpio;
    vpp_gpio = pic18_gpio_request(vpp_gpio, GPIOF_OUT_INIT_HIGH, "Vpp");
}

ssize_t pic18_io_get_flash(char *buffer)
{
    memcpy(buffer, flash, 4096);

    return 4096;
}

void pic18_io_set_flash(const char *buffer, size_t size)
{
    memcpy(flash, buffer, size);
}

void pic18_io_set_pgd_value(void)
{
    gpio_set_value(pgd_gpio, 1);
}

void pic18_io_clear_pgd_value(void)
{
    gpio_set_value(pgd_gpio, 0);
}

void pic18_io_set_pgc_value(void)
{
    gpio_set_value(pgc_gpio, 1);
}

void pic18_io_clear_pgc_value(void)
{
    gpio_set_value(pgc_gpio, 0);
}

void pic18_io_set_vpp_value(void)
{
    gpio_set_value(vpp_gpio, 1);
}

void pic18_io_clear_vpp_value(void)
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
