/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#ifndef _PIC18_WORKER_H_
#define _PIC18_WORKER_H_

extern int  pic18_worker_init(void);
extern int  pic18_worker_main(void *data);
extern void pic18_worker_exit(void);

#endif
