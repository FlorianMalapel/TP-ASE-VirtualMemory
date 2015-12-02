/* ------------------------------
   $Id: hw_config.h 105 2009-11-24 15:22:50Z simon_duquennoy $
   ------------------------------------------------------------

   Fichier de configuration des acces au materiel

   Philippe Marquet, march 2007

   Code au niveau applicatif la description du materiel qui est fournie
   par hardware.ini
   
*/

#ifndef _HW_CONFIG_H_
#define _HW_CONFIG_H_


#include "hardware.h"
   
#define HARDWARE_INI	"./libs/hardware.ini"

#define MMU_ENABLE 		1
#define MMU_IRQ			13
#define MMU_CMD			0x66
#define MMU_FAULT_ADDR 	0xCD
#define TLB_ADD_ENTRY	0xCE
#define TLB_DEL_ENTRY	0xDE
#define TLB_SIZE		32
#define TLB_ENTRIES		0x800

#define PM_PAGES 		(1 << 8)
#define VM_PAGES 		(1 << 12)
#define PAGE_SIZE 		4096
#define PM_SIZE 		(4096 * PM_PAGES)
#define VM_SIZE 		(4096 * VM_PAGES)
#define N_PAGE_PHYS 	2048


#define BEGIN_PMEM 		*(int*)&physical_memory
#define END_PMEM  		*(int*)&physical_memory + PM_SIZE - 1

#define BEGIN_VMEM		*(int*)&virtual_memory
#define END_VMEM  		*(int*)&virtual_memory + VM_SIZE - 1

#endif