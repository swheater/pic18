/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#ifndef _PIC18_IO_H_
#define _PIC18_IO_H_

extern int  pic18_io_init(void);
extern void pic18_io_setvpp(void);
extern void pic18_io_clearvpp(void);
extern void pic18_io_exit(void);

#endif
