/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <asm/page.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/gpio.h>

#include "pic18_io.h"

#define INVALID_GPIO     (-1)
#define PROGRAM_MODE_KEY (0x4D434850)

#define WORD08_MASK (0x00000008)
#define WORD16_MASK (0x00000080)
#define WORD32_MASK (0x00008000)

#define INVALID_DIRECT (0)
#define SEND_DIRECT    (1)
#define RECEIVE_DIRECT (2)

static int pgd_gpio_direction;

static volatile int pgd_gpio = INVALID_GPIO;
static volatile int pgc_gpio = INVALID_GPIO;
static volatile int vpp_gpio = INVALID_GPIO;

static volatile char flash[PAGE_SIZE];

static int pic18_gpio_request(int gpio, int flags, const char *label)
{
    if ((gpio != INVALID_GPIO) && gpio_is_valid(gpio))
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

    if (pgd_gpio != INVALID_GPIO)
        pgd_gpio_direction = SEND_DIRECT;
    else
        pgd_gpio_direction = INVALID_DIRECT;

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

    if (pgd_gpio != INVALID_GPIO)
        pgd_gpio_direction = SEND_DIRECT;
    else
        pgd_gpio_direction = INVALID_DIRECT;
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
    memcpy(buffer, flash, PAGE_SIZE);

    return PAGE_SIZE;
}

void pic18_io_set_flash(const char *buffer, size_t size)
{
    memcpy(flash, buffer, size);
}

static void pic18_io_direction(int direction)
{
    if (pgd_gpio_direction != direction)
    {
        pgd_gpio_direction = INVALID_DIRECT;

        if (pgd_gpio != INVALID_GPIO)
        {
            if (direction == SEND_DIRECT)
            {
	      if (! gpio_direction_output(pgd_gpio, 0))
                    pgd_gpio_direction = SEND_DIRECT;
            }
            else if (direction == RECEIVE_DIRECT)
            {
                if (! gpio_direction_input(pgd_gpio))
                    pgd_gpio_direction = RECEIVE_DIRECT;
            }
        }
    }
}

static void pic18_io_send(unsigned int value, unsigned int mask)
{
    while (mask != 0)
    {
        int bitValue = value & mask;
        mask = (mask >> 1) & 0x7FFFFFFF;

        gpio_set_value(pgc_gpio, 0);
        gpio_set_value(pgd_gpio, (bitValue != 0? 1: 0));
        mdelay(1000); // DEBUG DELAY
        mdelay(1);
        
        gpio_set_value(pgc_gpio, 1);
        mdelay(1000); // DEBUG DELAY
        mdelay(1);
    }
    gpio_set_value(pgc_gpio, 0);
}

static unsigned int pic18_io_recieve(unsigned int mask)
{
    unsigned int value = 0;
    while (mask != 0)
    {
        int bitValue = value & mask;
        mask = (mask >> 1) & 0x7FFFFFFF;

    }
    return value;
}

static void pic18_io_program_start(void)
{
    gpio_set_value(vpp_gpio, 0);
    mdelay(1000); // DEBUG DELAY
    mdelay(2);
    pic18_io_send(PROGRAM_MODE_KEY, WORD32_MASK);
    mdelay(1000); // DEBUG DELAY
    mdelay(1);
    gpio_set_value(vpp_gpio, 1);
    mdelay(1000); // DEBUG DELAY
    mdelay(1);
}

static void pic18_io_program_stop(void)
{
    mdelay(1000); // DEBUG DELAY
    mdelay(1);
    gpio_set_value(vpp_gpio, 0);
}

void pic18_io_program(void)
{
    if ((pgd_gpio != INVALID_GPIO) && (pgc_gpio != INVALID_GPIO) && (vpp_gpio != INVALID_GPIO))
    {
        pic18_io_program_start();
        mdelay(1000); // DEBUG DELAY
        mdelay(1);

        

        mdelay(1000); // DEBUG DELAY
        pic18_io_program_stop();
        mdelay(1);
    }
}

void pic18_io_exit(void)
{
    printk(KERN_INFO "pic18_io: pic18_io_exit\n");

    pic18_gpio_free(pgd_gpio, "PGD");
    pic18_gpio_free(pgc_gpio, "PGC");
    pic18_gpio_free(vpp_gpio, "Vpp");
}
