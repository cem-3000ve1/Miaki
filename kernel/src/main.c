#include <vitasdkkern.h>
#include <stdio.h>
#include <string.h>
#include <taihen.h>
#include "power.h"
#include "sysroot.h"
#include "spkg.h"

#define printf 

char infile[128];
char outfile[128];
int sz = -1;
int offst;
int progress = -1;


int getFileSize(const char *file) {
	SceUID fd = ksceIoOpen(file, SCE_O_RDONLY, 0);
	if (fd < 0)
		return fd;
	int fileSize = ksceIoLseek(fd, 0, SCE_SEEK_END);
	ksceIoClose(fd);
	return fileSize;
}

int WriteFile(char *file, void *buf, int size) {
	SceUID fd = ksceIoOpen(file, SCE_O_RDWR | SCE_O_CREAT, 0777);
	if (fd < 0)
		return fd;

	int written = ksceIoWrite(fd, buf, size);

	ksceIoClose(fd);
	return written;
}

int ReadFile(char *file, void *buf, int size) {
	SceUID fd = ksceIoOpen(file, SCE_O_RDONLY, 0777);
	if (fd < 0)
		return fd;

	int readed = ksceIoRead(fd, buf, size);

	ksceIoClose(fd);
	return readed;
}

int run_on_thread(void *func) {
	
	int ret = 0;
	int res = 0;
	int uid = 0;

	ret = uid = ksceKernelCreateThread("run_on_thread", func, 64, 0x10000, 0, 0, 0);
	
	if (ret < 0) {
		ret = -1;
		goto cleanup;
	}
	if ((ret = ksceKernelStartThread(uid, 0, NULL)) < 0) {	
		ret = -1;
		goto cleanup;
	}

	ret = res;

cleanup:
	if (uid > 0)
		ksceKernelDeleteThread(uid);

	return ret;
}



int run_dd(void)
{
	int ret = 0;
	
	SceUID fd = ksceIoOpen(infile, SCE_O_RDONLY, 0777);
	SceUID wfd = ksceIoOpen(outfile, SCE_O_WRONLY, 6);
	static char buffer[0x100000];
	
	while(!(sz <= 0))
	{
		memset(buffer,0x00,0x100000);
		if(sz < 0x100000)
		{
			ksceIoRead(fd, buffer, sz);
			ret = ksceIoWrite(wfd, buffer, sz);
			sz -= sz;
		}
		else
		{
			ksceIoRead(fd, buffer, 0x100000);
			ret = ksceIoWrite(wfd, buffer, 0x100000);
			sz -= 0x100000;
		}
	}

	if (fd > 0)
		ksceIoClose(fd);
	if (wfd > 0)
		ksceIoClose(wfd);
	sz = 0x50000001;
	return ret;
}


int kgetTotalLeft()
{
	return sz;
}

int kdd(char *inf, char *of, int size)
{

	int state =  0;
	ENTER_SYSCALL(state);
	
	ksceKernelStrncpyUserToKernel(&infile, (uintptr_t)inf, sizeof(infile));
	ksceKernelStrncpyUserToKernel(&outfile, (uintptr_t)of, sizeof(outfile));

	sz = size;
	
	int ret = run_on_thread(run_dd);	
	EXIT_SYSCALL(state);
	return ret;
}

/*
* Magical FAPS TEAM technology V V V 
*/
int kscePowerSetCallbackStateForUser(int enable)
{
	return kscePowerSetCallbackState(enable);
}

int kDecryptSpkgFile(char *in, char *out)
{
    char infile[128];
    char outfile[128];
    void *spkg = 0;
    
    ksceKernelStrncpyUserToKernel(&infile, (uintptr_t)in, sizeof(infile));
    ksceKernelStrncpyUserToKernel(&outfile, (uintptr_t)out, sizeof(outfile));
    
    int size = getFileSize(infile);
    
    int memblk = ksceKernelAllocMemBlock("spkg_block", 0x10C0D006, (size + 0xfff) & ~0xfff, NULL);
	if(memblk < 0)
	{
		return memblk;
	}
	
    int base = ksceKernelGetMemBlockBase(memblk, &spkg);
	if(base < 0)
	{
		return base;
	}
	
	if(spkg < 0)
	{
		return (int)spkg;
	}
	
	ReadFile(infile,spkg,size);
    int ret = decrypt_spkg(spkg, size);
	WriteFile(outfile, spkg, size);
    ksceKernelFreeMemBlock(memblk);
	return ret;
}

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize args, void *argp) {
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize args, void *argp) {
  return SCE_KERNEL_STOP_SUCCESS;
}
		