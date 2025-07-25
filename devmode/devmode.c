/* devmode.c -- DevMode Enabler 
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

static int hook = -1;
static int hook1 = -1;
static int hook2 = -1;
static int hook3 = -1;
static tai_hook_ref_t ref_hook;
static tai_hook_ref_t ref_hook1;
static tai_hook_ref_t ref_hook2;
static tai_hook_ref_t ref_hook3;

static int returntrue() {
    return 1;
}	
void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args)
{
        
       hook = taiHookFunctionExportForKernel(KERNEL_PID,
		&ref_hook, 
		"SceVshBridge",
		0x35C5ACD4, //SceVshBridge
		0x641890D8, //vshSblSsIsDevelopmentMode
		returntrue);

	   hook1 = taiHookFunctionExportForKernel(KERNEL_PID, 
		   &ref_hook1, 
		   "SceVshBridge",
		   0x35C5ACD4, //SceVshBridge
		   0xDDFC4EEE, //vshSblAimgrIsGenuineDolce
		   returntrue);
	
		hook2 = taiHookFunctionExportForKernel(KERNEL_PID, 
			&ref_hook2, 
		   	"SceSblQafMgr",
		   	0x756B7E89, //SceSblQafMgr
		   	0xD22A8731, //sceSblQafMgrIsAllowScreenShotAlways
		   	returntrue);

		hook3 = taiHookFunctionExportForKernel(KERNEL_PID,
			&ref_hook3,
			"SceSblQafMgr",
			0x756B7E89, //SceSblQafMgr
			0x66843305, //sceSblQafMgrIsAllowAllDebugMenuDisplay
			returntrue);
       
       
       
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args)
{
	if (hook >= 0) taiHookReleaseForKernel(hook, ref_hook);   
	if (hook1 >= 0) taiHookReleaseForKernel(hook1, ref_hook1);
	if (hook2 >= 0) taiHookReleaseForKernel(hook2, ref_hook2);
	if (hook3 >= 0) taiHookReleaseForKernel(hook3, ref_hook3);
	return SCE_KERNEL_STOP_SUCCESS;
}