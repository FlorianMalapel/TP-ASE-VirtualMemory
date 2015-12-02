#ifndef swap_h
#define swap_h


#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "hw_config.h"

#define N 2048


extern char init_swap(const char *path);
extern char store_to_swap(int vpage, int ppage);
extern char fetch_from_swap(int vpage, int ppage);

#endif /* swap_h */