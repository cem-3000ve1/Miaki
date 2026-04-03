#include <vitasdk.h>
#include <stdio.h>
#include <string.h>
#include "config.h"
#include <taihen.h>

static int hook = -1;
static tai_hook_ref_t ref_hook;

int ksceSblPostSsMgrGetExpireDate_patched(int *expire_date, SceBool read_from_nvs)
{
    *expire_date = act_date;
    return 0;
}

void act_sm_start(void) {
    hook = taiHookFunctionExportForKernel(KERNEL_PID,
                                         &ref_hook,
                                         "SceSblPostSsMgr",
                                         0x2254E1B2,
                                         0x4FF2682F,
                                         ksceSblPostSsMgrGetExpireDate_patched);
}

void act_sm_stop(void) {
    if (hook >= 0) {
        taiHookReleaseForKernel(hook, ref_hook);
        hook = -1;
    }
}

        
