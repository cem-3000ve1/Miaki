#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vitasdk.h>

#define printf psvDebugScreenPrintf

int get_key(int type) {


	SceCtrlData pad;

	if(type == 0){

		while (1) {
			//memset(&pad, 0, sizeof(pad));
			sceCtrlPeekBufferPositive(0, &pad, 1);

				if (pad.buttons != 0)
					return pad.buttons;

			sceKernelDelayThread(1000); // 1ms
		}

	}else{

		while (1) {

			//memset(&pad, 0, sizeof(pad));
			sceCtrlPeekBufferPositive(0, &pad, 1);
			if(pad.buttons == 0){

				break;

			}

			sceKernelDelayThread(1000); // 1ms

		}

	}

	return 0;

}


void press_exit(void) {

	get_key(1);

	printf("Press any key to exit this application.\n");

	get_key(0);

	sceKernelExitProcess(0);

}