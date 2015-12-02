##  Makefile
##  TP9-Virtual_Memory-Malapel&Dhersin
##
##  Last update - by jerome on 26/11/2015.
## 		add : exe mmu_manager oracle
##  Copyright © 2015 Malapel&Dhersin. All rights reserved.


LIBS = -L./libs -lhardware

CFLAGS = -m32 
SRC = ./src/
INC = ./header/
BIN = ./bin/


all: mmu_manager oracle

# generate exe
mmu_manager: $(BIN)mmu_manager.o $(BIN)user_process.o $(BIN)matrix.o $(BIN)swap.o
	gcc -m32 -o mmu_manager $(BIN)mmu_manager.o $(BIN)user_process.o $(BIN)matrix.o $(BIN)swap.o $(LIBS)

oracle: $(BIN)oracle.o $(BIN)matrix.o
	gcc -m32 -o oracle $(BIN)oracle.o $(BIN)matrix.o $(LIBS)


$(BIN)mmu_manager.o: $(SRC)mmu_manager.c $(SRC)user_process.c $(SRC)swap.c $(INC)swap.h $(INC)mi_syscall.h $(INC)hw_config.h $(INC)mmu_manager.h $(INC)hardware.h
	gcc -m32 -o $(BIN)mmu_manager.o -c $(SRC)mmu_manager.c

$(BIN)user_process.o: $(SRC)user_process.c $(SRC)matrix.c $(INC)matrix.h $(INC)mi_syscall.h $(INC)hw_config.h $(INC)hardware.h
	gcc -m32 -o $(BIN)user_process.o -c $(SRC)user_process.c

$(BIN)mi_user.o: $(SRC)mi_user.c $(INC)mi_syscall.h $(INC)hw_config.h $(INC)hardware.h
	gcc -m32 -o $(BIN)mi_user.o -c $(SRC)mi_user.c
 
$(BIN)oracle.o: $(SRC)oracle.c $(SRC)matrix.c $(INC)matrix.h $(INC)hw_config.h $(INC)hardware.h
	gcc -m32 -o $(BIN)oracle.o -c $(SRC)oracle.c

$(BIN)matrix.o: $(SRC)matrix.c $(INC)matrix.h $(INC)hw_config.h $(INC)hardware.h
	gcc -m32 -o $(BIN)matrix.o -c $(SRC)matrix.c

$(BIN)swap.o: $(SRC)swap.c $(INC)swap.h $(INC)hw_config.h $(INC)hardware.h
	gcc -m32 -o $(BIN)swap.o -c $(SRC)swap.c
 


clean:
	rm -rf $(BIN)*.o
	rm -rf mmu_manager
	rm -rf oracle

#cleanall
cleanall: clean
	rm -rf all
	clear
