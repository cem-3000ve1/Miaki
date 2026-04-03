#include <vitasdkkern.h>
#include <stdio.h>
#include <string.h>
#include <taihen.h>

static int hook = -1;
static tai_hook_ref_t ref_hook;

static int IsAllowKernelDebugForDriver_patched(void) {
    return 1;
}


void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize args, void *argp) {
    hook = taiHookFunctionExportForKernel(KERNEL_PID,
                                        &ref_hook, 
                                        "SceSblQafMgr",
                                        TAI_ANY_LIBRARY,
                                        0x382C71E8, 
                                        IsAllowKernelDebugForDriver_patched);
    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize args, void *argp) {
  return SCE_KERNEL_STOP_SUCCESS;
}
        
