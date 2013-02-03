/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#ifndef _PIC18_IO_H_
#define _PIC18_IO_H_

#include <linux/types.h>

extern int  pic18_io_init(void);
extern int  pic18_io_get_gpio_pgd(void);
extern void pic18_io_set_gpio_pgd(int gpio);
extern int  pic18_io_get_gpio_pgc(void);
extern void pic18_io_set_gpio_pgc(int gpio);
extern int  pic18_io_get_gpio_vpp(void);
extern void pic18_io_set_gpio_vpp(int gpio);
extern ssize_t pic18_io_get_flash(char *flash);
extern void pic18_io_set_flash(const char *flash, size_t size);
extern void pic18_io_program(void);
extern void pic18_io_exit(void);

#endif
