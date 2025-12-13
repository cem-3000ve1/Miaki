/* devmode.c -- DevMode Enabler 
 *
 * Copyright (C) 2025 LazyPreview
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <stdarg.h>

#include <vitasdk.h>

#include <psp2kern/kernel/debug.h> 
#include <psp2/kernel/threadmgr.h>
#include <psp2kern/kernel/acmgr.h> 
#include <psp2kern/kernel/dipsw.h> 

#define LOG(fmt, ...) ksceDebugPrintf("[LazyLoader/DevMode      ]:" fmt "\n", ##__VA_ARGS__)

static int returntrue(void) {
    return 1;
}

void _start() __attribute__((weak, alias("module_start")));
int module_start(SceSize argc, const void *args) {
    int dipsw_id[] = {159, 128};
    int count = sizeof(dipsw_id)/sizeof(dipsw_id[0]);
    ksceKernelDelayThread(100000);
	LOG("Starting LazyLoader...");
	for (int i = 0; i < count; i++) {
        int id = dipsw_id[i];
        ksceKernelSetDipsw(id);
        int status = ksceKernelCheckDipsw(id);
        if (status == 1)
            LOG("dipsw %d enabled", id);
        else
            LOG("failed dipsw %d", id);
    }
    
    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) {
    return SCE_KERNEL_STOP_SUCCESS;
}
