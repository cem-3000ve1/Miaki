#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vitasdk.h>
#include <taihen.h>

#include "../../miaki_user.h"

#include "../../ctrl.h"
#include "../../pup.h"
#include "../flasher.h"
#include "../utils.h"
#include "../modules.h"
#define printf psvDebugScreenPrintf

void fixboot(void)
{
	DebugLog("Fixing the boot configuration...");
	CopyFile("app0:/testkit_vita.skprx", "ur0:tai/testkit.skprx");
	CopyFile("app0:/vitaConfig.txt", "ur0:tai/boot_config.txt");
	scePowerRequestColdReset();
}
