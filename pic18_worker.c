/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#include "pic18_io.h"
#include "pic18_worker.h"

static struct task_struct *worker_thread = NULL;

int pic18_worker_init(void)
{
    printk(KERN_INFO "pic18_worker: pic18_worker_init\n");

    worker_thread = kthread_run(pic18_worker_main, NULL, "pic18 worker");

    return 0;
}

int pic18_worker_main(void *data)
{
    printk(KERN_INFO "pic18_worker: main started\n");

    while (! kthread_should_stop())
    {
        pic18_io_set_vpp_value();
	mdelay(500);

        pic18_io_clear_vpp_value();
	mdelay(500);
    }

    printk(KERN_INFO "pic18_worker: main stopped\n");

    return 0;
}

void pic18_worker_exit(void)
{
    printk(KERN_INFO "pic18_worker: pic18_worker_exit\n");

    if (worker_thread != NULL)
        kthread_stop(worker_thread);
}
