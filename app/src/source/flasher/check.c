#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vitasdk.h>
#include <psp2kern/io/fcntl.h>
#include <taihen.h>

#include "../../include/miaki_user.h"

#include "../../include/ctrl.h"
#include "../../include/pup.h"
#include "../../include/flasher.h"
#include "../../include/utils.h"
#include "../../include/modules.h"
#include "../../include/ui.h"
#define printf psvDebugScreenPrintf


void check_install(void) {
    SceUID fd;
    fd = ksceIoOpen("ur0:tai/boot_config.txt", SCE_O_WRONLY | SCE_O_APPEND, 0777);
    char buf[1024];
    const char *target = "- load\tur0:tai/henkaku.skprx\n";
    int found = 0;
    ksceIoClose(fd);
}
