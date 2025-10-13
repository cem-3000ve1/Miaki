#include <vitasdkkern.h>
#include <stdio.h>
#include <string.h>
#include <taihen.h>

static int hook = -1;
static tai_hook_ref_t ref_hook;

int ksceSblPostSsMgrGetExpireDate_patched(int *arg1, int arg2)
{
    *arg1 = 0x680b52e4;
    return 0;
}

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize args, void *argp) {
    hook = taiHookFunctionExportForKernel(KERNEL_PID,
                                        &ref_hook, 
                                        "SceSblPostSsMgr",
                                        0x2254E1B2,
                                        0x4FF2682F, 
                                        ksceSblPostSsMgrGetExpireDate_patched);
    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize args, void *argp) {
  return SCE_KERNEL_STOP_SUCCESS;
}
        
