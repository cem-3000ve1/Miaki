/* qafull.c -- QATEAM FULL E
 *
 * Copyright (C) 2025 LazyPreview
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include <vitasdk.h>
#include <taihen.h>
#include <psp2kern/kernel/debug.h>

#define LOG(fmt, ...) ksceKernelPrintf("[LazyLoader/QAF]: " fmt "\n", ##__VA_ARGS__)

static SceUID hooks[40];
static tai_hook_ref_t refs[40];

static int returntrue(void) {
    return 1;
}

#define HOOKNID(idx, module, libnid, funcnid) do { \
    SceUID r = taiHookFunctionExportForKernel(KERNEL_PID, &refs[idx], module, libnid, funcnid, (void*)returntrue); \
    if (r >= 0) { \
        hooks[idx] = r; \
        LOG("hooked 0x%08X ok (idx=%d)", funcnid, idx); \
    } else { \
        hooks[idx] = -1; \
        LOG("hook 0x%08X failed (err=0x%08X)", funcnid, r); \
    } \
} while (0)

void _start() __attribute__((weak, alias("module_start")));

int module_start(SceSize argc, const void *args) {
    ksceKernelDelayThread(100000);
    LOG("Starting...");

    HOOKNID(0, "SceSblQafMgr", 0x756B7E89, 0x382C71E8);

    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) {
    for (int i = 0; i < 40; i++) {
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