#include <stdio.h>
#include <stdarg.h>
#include <vitasdk.h>
#include <psp2kern/kernel/sysmem.h>
#include <psp2kern/kernel/dipsw.h>
#include <psp2kern/kernel/debug.h>
#include <psp2kern/kernel/sysclib.h>
#include "config.h"

#define CONFIG_PATH "ur0:tai/lazyconf.cfg"
#define LOG(fmt, ...) ksceDebugPrintf("[LazyLoader      ]:" fmt "\n", ##__VA_ARGS__)

static void enable_devmode(void) {
    ksceKernelSetDipsw(159);
    LOG("development_mode enabled");
}

static void memoryswitch(void) {
    ksceKernelSetDipsw(128);
    LOG("Switch memory configuration");
}

static void enable_dolce(void) {
    ksceKernelSetDipsw(152);
    LOG("dolce_emulation enabled");
}

static void enable_shellbootime(void) {
    ksceKernelSetDipsw(185);
    LOG("BootTimeNotification enabled");
}

int module_start(SceSize argc, const void *args) {
    LOG("loading config\n");
    lazyconf_load(CONFIG_PATH);

    if (lazyconf.development_mode == 1) {
        LOG("enabling devmode...");
        enable_devmode();
    }

    if (lazyconf.platform_emulation_dolce == 1) {
        LOG("enabling dolce mode");
        enable_dolce();
    }

    if (lazyconf.shellbootime == 1) {
        LOG("enabling ShellBootTimeNotification");
        enable_shellbootime();
    }

    if (lazyconf.memory_switch == 1) {
        LOG("Switching memory configuration...");
        memoryswitch();
    }

    if (lazyconf.activation_date != 0) {
        LOG("Starting act_sm");
        act_sm_start();
    }

    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) {
    return SCE_KERNEL_STOP_SUCCESS;
}