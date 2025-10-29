#include <stdio.h>
#include <stdarg.h>
#include <vitasdkkern.h>
#include <taihen.h>
#include <string.h>

static int hook = -1;
static tai_hook_ref_t ref_hook;

static const unsigned char cid_patched[16] = {
    0x00, 0x00, 0x00, 0x01,
    0x01, 0x01, 0x00, 0x14,
    0x0C, 0x00, 0x05, 0xD3,
    0x26, 0x7F, 0xDF, 0xD6
};

static int ksceSblAimgrGetConsoleId_patched(char CID[16])
{
    int ret = TAI_CONTINUE(int, ref_hook, CID);
    memcpy(CID, cid_patched, sizeof(cid_patched));
    return ret;
}

void _start() __attribute__ ((weak, alias ("module_start")));


int module_start(SceSize argc, const void *args)
{
    hook = taiHookFunctionExportForKernel(KERNEL_PID,
                                         &ref_hook,
                                         "SceSblSsMgr",
                                         TAI_ANY_LIBRARY,
                                         0xFC6CDD68, 
                                         ksceSblAimgrGetConsoleId_patched);
    if (hook < 0) {
        return SCE_KERNEL_START_FAILED;
    }
    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args)
{
    if (hook >= 0) {
        taiHookReleaseForKernel(hook, ref_hook);
        hook = -1;
    }
    return SCE_KERNEL_STOP_SUCCESS;
}