#include <stdio.h>
#include <stdlib.h>
#include "../header/mmu_manager.h"
#include "../header/mi_syscall.h"
#include "../header/hardware.h"

extern void init();

static int current_process;

/* Retourne le numéro de la page de cette adresse virtuelle, retourne -1 en cas d'erreur */
static int vpage_of_vaddr(unsigned vaddr){
	// On met un mask sur vaddr pour vérifier que la constante des premiers 8bits
	// correspondent avec la mémoire virtuelle
	if( (vaddr &0xFF000000) != (unsigned int)virtual_memory) {
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

void mmu_handler() {
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
	
	 //  Passe la main au code Utilisateur 
	_mask(0x1001);
	printf("User mode...\n");
	init();
}