//
//  mi_kernel.c
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


extern void init();
static void switch_to_process0(void);
static void switch_to_process1(void);


int main(int argc, char* argv[]) {

	printf("Init hardware...\n");
	/* Initialise le matériel */
	if(init_hardware(HARDWARE_INI) == 0) {
		fprintf(stderr, "Error in hardware initialization\n");
		exit(EXIT_FAILURE);
	}

	 /* Initialise le vecteur d'interruptions */
	IRQVECTOR[MMU_IRQ] = mmu_handler;
	IRQVECTOR[SYSCALL_SWITCH_0] = switch_to_process0; 
	IRQVECTOR[SYSCALL_SWITCH_1] = switch_to_process1; 

	/** Passage au mode User **/
	_mask(0x1001);
	printf("User mode...\n");
	init();
}