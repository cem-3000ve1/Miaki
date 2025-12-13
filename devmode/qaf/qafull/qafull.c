/* qafull.c -- QATEAM FULL E
 *
 * Copyright (C) 2025 LazyPreview
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <stdarg.h>

#include <vitasdk.h>
#include <taihen.h>
#include <psp2kern/kernel/debug.h> 
#include <psp2/kernel/threadmgr.h>
#include <psp2kern/kernel/acmgr.h> 
#include <psp2kern/kernel/dipsw.h> 

#define LOG(fmt, ...) ksceKernelPrintf("[LazyLoader/QAF         ]:" fmt "\n", ##__VA_ARGS__)

static int hooks[19];
static tai_hook_ref_t refs[19];

static int returntrue(void) {
    return 1;
}

#define HOOKNID(idx, module, libnid, funcnid) do { \
    int r = taiHookFunctionExportForKernel(KERNEL_PID, &refs[idx], module, libnid, funcnid, (void*)returntrue); \
	if (r >= 0) { \
        hooks[idx] = r; \
        LOG("hooked %s ok (idx=%d)", #funcnid, idx); \
    } else { \
        hooks[idx] = -1; \
        LOG("hook %s failed (err=0x%08X)", #funcnid, r); \
    } \
} while (0)

void _start() __attribute__((weak, alias("module_start")));
int module_start(SceSize argc, const void *args) {
    ksceKernelDelayThread(100000);
	LOG("Starting LazyLoader...");
    HOOKNID(0, "SceVshBridge", 0x35C5ACD4, 0xCEC8B917);
    HOOKNID(1, "SceRegistryMgr", TAI_ANY_LIBRARY, 0x0E588747);
    HOOKNID(2, "SceSblQafMgr", 0x756B7E89, 0xD22A8731);
    HOOKNID(3, "SceSblACMgrForDriver", 0x9AD8E213, 0x991FDC15);
    HOOKNID(4, "SceVshBridge", 0x35C5ACD4, 0x31AACDD2);
    HOOKNID(5, "SceVshBridge", 0x35C5ACD4, 0xD0D4EB67);
    HOOKNID(6, "SceVshBridge", 0x35C5ACD4, 0xB19EAB45);
    HOOKNID(7, "SceVshBridge", 0x35C5ACD4, 0x12831F05);
    HOOKNID(8, "SceVshBridge", 0x35C5ACD4, 0x06AD7CBB);
    HOOKNID(9, "SceVshBridge", 0x35C5ACD4, 0x1484AF06);
    HOOKNID(10, "SceVshBridge", 0x35C5ACD4, 0xD0C8D4EC);
    HOOKNID(11, "SceVshBridge", 0x35C5ACD4, 0xAD95CBE8);
    HOOKNID(12, "SceVshBridge", 0x35C5ACD4, 0x58E1DE33);
    HOOKNID(13, "SceVshBridge", 0x35C5ACD4, 0x314BFD78);
    HOOKNID(14, "SceVshBridge", 0x35C5ACD4, 0x51CE4C9A);
    HOOKNID(15, "SceVshBridge", 0x35C5ACD4, 0x565E0504);
    HOOKNID(16, "SceSblQafMgr", 0x756B7E89, 0x72168C6E);
    HOOKNID(17, "SceSblQafMgr", 0x756B7E89, 0x11D30766);
    HOOKNID(18, "SceSblAIMgrForDriver", 0xFD00C69A, 0x883E9465);
    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) {
    for (int i = 0; i < 19; i++) {
        if (hooks[i] >= 0) {
            int r = taiHookReleaseForKernel(hooks[i], refs[i]);
            if (r >= 0)
                LOG("unhook %d ok", i);
            else
                LOG("unhook %d failed (0x%08X)", i, r);
        }
    }
    return SCE_KERNEL_STOP_SUCCESS;
}
