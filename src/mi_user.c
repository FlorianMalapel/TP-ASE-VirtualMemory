//
//  mi_user.c
//  TP9-Mémoire virtuelle
//
//  Created by jerome on 24/11/2015.
//  Copyright © 2015 Malapel&Dhersin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/hw_config.h"
#include "../header/hardware.h"
#include "../header/mi_syscall.h"
#include "../header/mmu_manager.h"



static int sum(void *ptr) {
	int i;   
	int sum = 0;
	for(i = 0; i < PAGE_SIZE * N/2 ; i++) 
		sum += ((char*)ptr)[i];
	return sum; 
}


void init() {
	printf("init \n");
	void *ptr;
	int res;
	
	ptr = virtual_memory;
	_int(SYSCALL_SWITCH_0);
	printf("après SYSCALL_SWTCH_0  %p \n",ptr);
	memset(ptr, 1, PAGE_SIZE * N/2); 
	_int(SYSCALL_SWITCH_1);
	memset(ptr, 3, PAGE_SIZE * N/2);
	_int(SYSCALL_SWITCH_0);
	res = sum(ptr);
	printf("Resultat du processus 0 : %d\n",res); 
	_int(SYSCALL_SWITCH_1);
	res = sum(ptr);
	printf("Resultat processus 1 : %d\n",res);
}