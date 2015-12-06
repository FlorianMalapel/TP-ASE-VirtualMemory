#ifndef mmu_manager_h
#define mmu_manager_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw_config.h"
#include "hardware.h"
#include "mi_syscall.h"

#define N 20

static int current_process;

struct tlb_entry_s {
	int rfu : 8;
	int vpage : 12;
	int ppage : 8;
	int access_x : 1;
	int access_w : 1;
	int access_r : 1;
	int used : 1;
};

union tlb_entry_u {
	struct tlb_entry_s entry;
	int asInt;
};

void mmu_handler();
static int vpage_of_vaddr(unsigned vaddr);
static int ppage_of_vaddr(int process, unsigned vaddr);


#endif /* mmu_manager_h */