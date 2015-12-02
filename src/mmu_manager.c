#include <stdio.h>
#include <stdlib.h>
#include "../header/mmu_manager.h"
#include "../header/mi_syscall.h"
#include "../header/hardware.h"

static int current_process;

/* Retourne le numéro de la page de cette adresse virtuelle, retourne -1 en cas d'erreur */
static int vpage_of_vaddr(unsigned vaddr){
	// On met un mask sur vaddr pour vérifier que la constante des premiers 8bits
	// correspondent avec la mémoire virtuelle
	if( (vaddr &0xFF000000) != (unsigned int)virtual_memory){
		return -1;
	}

	// On ne renvoie que la numéro de page virtuelle correspondante
	return ((vaddr >> 12) &0xFFF);
}

/* Retourne le numéro de la page physique associée à l'@ virtuelle vaddr du process
 * process (0 pour le premier processus, 1 pour le second). La fonction retourne -1
 * si l'@ virtuelle est en dehors de l'espace alloué au processus */
 static int ppage_of_vaddr(int process, unsigned vaddr){
	int vpage = vpage_of_vaddr(vaddr);
	if(vpage < 0) return -1;
	return (vpage < N/2) ? process*N/2 + vpage +1 : -1;
}

void mmu_handler(){
	union tlb_entry_u union_entry;
	unsigned int vaddr = _in(MMU_FAULT_ADDR);
	
	int ppage = ppage_of_vaddr(current_process, vaddr);
	
	if(ppage < 0)
		exit(-1);

	union_entry.entry.ppage = ppage;
	union_entry.entry.vpage = vpage_of_vaddr(vaddr);
	union_entry.entry.access_x = 1;
	union_entry.entry.access_r = 1;
	union_entry.entry.access_w = 1;
	union_entry.entry.used = 1;


	_out(TLB_ADD_ENTRY, union_entry.asInt);
}


static int sum(void *ptr) {
	int i;
	int sum = 0;
	for(i = 0; i < PAGE_SIZE * N/2; i++) {
		sum += ((char*)ptr)[i];
	}
	return sum;
}


static void switch_to_process0(void) {
	current_process = 0;
	_out(MMU_CMD, MMU_RESET);
}


static void switch_to_process1(void) {
	current_process = 1;
	_out(MMU_CMD, MMU_RESET);
}


int main(int argc, char* argv[]) {

	void *ptr;
	int res;
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
	
	/* Passe la main au code Utilisateur */
	_mask(0x1001);
	printf("User mode...\n");
	ptr = virtual_memory;
	_int(SYSCALL_SWITCH_0);
	printf("après SYSCALL_SWTICH_0  %p \n",ptr);
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




// int main(int argc, char **argv) {
// 	_out(MMU_PROCESS,1);
// 	if(init_swap("swap")) {
// 		fprintf(stderr, "Error in swap initialization\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	if(init_hardware(HARDWARE_INI) == 0) {
// 		fprintf(stderr, "Error in hardware initialization\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	IRQVECTOR[MMU_IRQ] = mmu_handler;

// 	_mask(0x1001);
// 	user_process();
// 	return 0;
// }