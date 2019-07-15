#include <psp2/kernel/modulemgr.h>
#include <vitasdk.h>
#include "cex2rex_user.h"

int dd(char *inf, char *of, int size)
{
	return kdd(inf, of, size);
}


int DecryptSpkgFile(char *in, char *out)
{
	return kDecryptSpkgFile(in, out);
}

int getTotalLeft()
{
	return kgetTotalLeft();
}

int scePowerSetCallbackState(int enable)
{
	return kscePowerSetCallbackStateForUser(enable);
}

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize args, void *argp) {
  return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize args, void *argp) {
  return SCE_KERNEL_STOP_SUCCESS;
}
