/*
 * mmu_dump.c - Bare metal ARMv7 translation table dumper
 * Copyright 2014 Yifan Lu
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <string.h>
#include <psp2kern/kernel/modulemgr.h>
#include <psp2kern/kernel/threadmgr.h>
#include <psp2kern/kernel/sysmem.h>
#include <psp2kern/io/fcntl.h>

static int afe;

#define DUMP_PATH "ux0:dump/"

void _start() __attribute__ ((weak, alias ("module_start")));

static unsigned int pa2va(unsigned int pa)
{
    unsigned int va;
    unsigned int vaddr;
    unsigned int paddr;
    unsigned int i;

    va = 0;
    for (i = 0; i < 0x100000; i++)
    {
        vaddr = i << 12;
        __asm__("mcr p15,0,%1,c7,c8,0\n\t"
                "mrc p15,0,%0,c7,c4,0\n\t" : "=r" (paddr) : "r" (vaddr));
        if ((pa & 0xFFFFF000) == (paddr & 0xFFFFF000))
        {
            va = vaddr + (pa & 0xFFF);
            break;
        }
    }
    return va;
}

static void mmu_get_perms(int ap2, int ap1, int *ur, int *uw, int *pr, int *pw)
{
    /* AFE enabled, use simple permissions */
    if (afe)
    {
        *ur = ap1 > 1;
        *uw = !ap2 && ap1 > 1;
        *pr = 1;
        *pw = !ap2 && ap1 < 2;
    }
    else
    {
        *pw = (!ap2 && ap1);
        *pr = *pw || ap1;
        *ur = ap1 > 1;
        *uw = !ap2 && ap1 == 3;
    }
}

//magic
unsigned char magic[0x8] = {
	0xA5, 0x9D, 0xCE, 0xAB, 0x00, 0x01, 0x01
};

//spoof
unsigned char testkit_pscode[0x8] = {
	0x00, 0x01, //CompanyCode
    0x01, 0x02, //ProductCode
    0x00, 0x10,	//ProductSubCode 
    0x00, 0x03	//FactoryCode
};

static int mmu_dump_pages(unsigned int vaddr, unsigned int entry)
{
    int xn;
    int ng;
    int s;
    int ap2;
    int ap1;
    int pr;
    int pw;
    int ur;
    int uw;
    unsigned int paddr;
    SceUID fd;

    if ((entry & 0x3) == 0x1) /* large page */
    {
        xn = entry & 0x8000;
        ng = entry & 0x800;
        s = entry & 0x400;
        ap2 = entry & 0x200;
        ap1 = (entry >> 4) & 3;
        mmu_get_perms(ap2, ap1, &ur, &uw, &pr, &pw);
        paddr = entry & 0xFFFF0000;
	if( paddr >= 0x40201000 && paddr < 0x5FD00000 && paddr != 0x44C20000 && paddr != 0x44C30000 && paddr != 0x443C0000){
		if( (paddr-0x44300000) <= (0x44400000-0x44300000) ){
			
			}else if ( (paddr-0x45020000) <= (0x45030000-0x45020000) ){
			}else{
		
				
				
				
				//spoofing happens here
				int counter = 0;
				for (counter = 0; counter < 0x1000; counter ++){
					if(memcmp((void*)vaddr + counter, magic, 7) == 0 && counter == 0x5B0){
						counter = counter + 4;
						memcpy((void*) vaddr + counter, testkit_pscode, 8);
						return 0;
					}
				}
            }
		}
        else{
            
			}
    }
    else if ((entry & 0x2)) /* small page */
    {
        xn = entry & 1;
        ng = entry & 0x800;
        s = entry & 0x400;
        ap2 = entry & 0x200;
        ap1 = (entry >> 4) & 3;
        mmu_get_perms(ap2, ap1, &ur, &uw, &pr, &pw);
        paddr = entry & 0xFFFFF000;
		//0x4434C000
        if( paddr >= 0x40201000 && paddr < 0x5FD00000){
			if( (paddr-0x47D80000) <= (0x47D90000-0x47D80000) ){
							}else if ( (paddr-0x44C09000) <= (0x44C1A000-0x44C09000) ){
							}else if ( (paddr-0x44300000) <= (0x44400000-0x44300000) ){
							}else if ( (paddr-0x45009000) <= (0x45019000-0x45009000) ){
							}else if ( (paddr-0x44700000) <= (0x44710000-0x44700000) ){
							}else{

				
				//spoofing also happens here
				int counter = 0;
				for (counter = 0; counter < 0x1000; counter ++){
					if(memcmp((void*)vaddr + counter, magic, 7) == 0 && counter  == 0x5B0){
						counter = counter + 4;
						memcpy((void*) vaddr + counter, testkit_pscode, 8);
						return 0;
					}
				}
			}
            
        }
        else{
                    }
    }
    else
    {
            }
	return 1;
}

static int mmu_dump_sections(unsigned int vaddr, unsigned int entry)
{
    int ns;
    int ss;
    int ng;
    int s;
    int ap1;
    int ap2;
    int domain;
    int xn;
    int pr;
    int pw;
    int ur;
    int uw;
    unsigned int paddr;
    unsigned int i;
    unsigned int *tbl;
    

    if ((entry & 0x3) == 2) /* section or supersection */
    {
        ns = entry & 0x80000;
        ss = entry & 0x40000;
        ng = entry & 0x20000;
        s = entry & 0x10000;
        ap2 = entry & 0x8000;
        ap1 = (entry >> 10) & 3;
        domain = (entry >> 5) & 15;
        xn = entry & 0x10;
        mmu_get_perms(ap2, ap1, &ur, &uw, &pr, &pw);
        paddr = ss ? entry & 0xFF000000 : entry & 0xFFF00000;

            }
    else if ((entry & 0x3) == 1) /* page table */
    {
        domain = (entry >> 5) & 15;
        ns = entry & 8;
        paddr = entry & 0xFFFFFC00;
        tbl = (unsigned int *)pa2va(paddr);
                for (i = 0; i < 0x100; i++)
        {
            int ret = mmu_dump_pages(vaddr+(i<<12), tbl[i]);
			if (ret == 0) {
				return 0;
			}
        }
    }
    else if ((entry & 0x3) == 0) /* not mapped */
    {
            }
    else
    {
            }
	return 1;
}

int mmu_dump(void)
{
    unsigned int ttbr[2];
    int ttbcr;
    int n;
    unsigned int i = 0;
    
    unsigned int *ttb_vaddr[2];
    unsigned int entry;

	
    __asm__("mrc p15,0,%0,c2,c0,0" : "=r" (ttbr[0]));
    __asm__("mrc p15,0,%0,c2,c0,1" : "=r" (ttbr[1]));
    __asm__("mrc p15,0,%0,c2,c0,2" : "=r" (ttbcr));
    
    n = ttbcr & 0x7;
    ttbr[0] &= (unsigned int)((int)0x80000000 >> (31 - 14 + 1 - n));
    ttbr[1] &= 0xFFFFC000;

    ttb_vaddr[0] = (unsigned int *)pa2va(ttbr[0]);
    ttb_vaddr[1] = (unsigned int *)pa2va(ttbr[1]);
        
    for (i = 0; i < (1 << (12 - n)); i++)
    {
        entry = ttb_vaddr[0][i];
        int ret = mmu_dump_sections(i<<20, entry);
		if(ret == 0){
			return 0;
		}
    }

    if (n)
    {
        for (i = ((~0xEFFF & 0xFFFF) >> n); i < 0x1000; i++)
        {
            entry = ttb_vaddr[1][i];
            int ret = mmu_dump_sections(i<<20, entry);
			if(ret == 0){
				return 0;
			}
        }
    }
    return 1;
}

int module_start(SceSize argc, const void *args)
{
    unsigned int sctlr;

    __asm__("mrc p15,0,%0,c1,c0,0" : "=r" (sctlr));
    afe = sctlr & 0x20000000;
    mmu_dump();

    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args)
{
	return SCE_KERNEL_STOP_SUCCESS;
}


