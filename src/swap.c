//
//  swap.c
//  TP9-Mémoire virtuelle
//
//  Created by jerome on 26/11/2015.
//  Copyright © 2015 Malapel&Dhersin. All rights reserved.
//

#include "../header/swap.h"


static FILE *swap_file;


char init_swap(const char *path) {
	swap_file = fopen(".swap_file", "w+");
	return (swap_file != NULL ? -1 : 1);
}	


char store_to_swap(int vpage, int ppage) {
	if (fseek(swap_file, vpage << 12, SEEK_SET) == -1) 
        return -1;
    if (fwrite((void*)(ppage << 12) , 1, PAGE_SIZE, swap_file) == -1) 
        return -1;
  	return 0;
}


char fetch_from_swap(int vpage, int ppage) {
	if (fseek(swap_file, vpage << 12, SEEK_SET) == -1) 
        return -1;
    if (fread((void*)(ppage << 12), 1, PAGE_SIZE, swap_file) == -1)       
        return -1;
    return 0;
}