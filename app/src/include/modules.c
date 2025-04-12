#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vitasdk.h>
#include <taihen.h>

#include "../miaki_user.h"

#include "../ctrl.h"
#include "../pup.h"
#include "modules.h"

#define printf psvDebugScreenPrintf
int coordX, coordY;
void load_modules(void)
{
    char titleid[12];
    char kplugin_path[0x200];
    char uplugin_path[0x200];

    sceAppMgrUmount("app0:");
    sceAppMgrAppParamGetString(0, 12, titleid , 256);

    sprintf(kplugin_path, "ux0:app/%s/kernel.skprx", titleid);
    sprintf(uplugin_path, "ux0:app/%s/user.suprx", titleid);
    printf("kplugin_path: %s\n",kplugin_path);
    printf("uplugin_path: %s\n",uplugin_path);
    int kernel_modid, user_modid;

    kernel_modid = taiLoadStartKernelModule(kplugin_path, 0, NULL, 0);
    if(kernel_modid < 0){
        printf("taiLoadStartKernelModule() failed. ret = 0x%x\n", kernel_modid);
    }
    user_modid = sceKernelLoadStartModule(uplugin_path, 0, NULL, 0, NULL, NULL);
    if(user_modid < 0){
        printf("sceKernelLoadStartModule() failed. ret = 0x%x\n", user_modid);
    }
    psvDebugScreenClear(0);
    return;
}
