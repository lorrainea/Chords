MF=     Makefile
 
CC=     g++ 
 
CFLAGS= -g -fopenmp -D_USE_OMP -msse4.2 -O3 -fomit-frame-pointer -funroll-loops  
 
LFLAGS= -std=c++11 -DNDEBUG -I ./ -I ./libsdsl/include/ -L ./libsdsl/lib/ -lsdsl -ldivsufsort -ldivsufsort64 -Wl,-rpath=$(PWD)/libsdsl/lib
 
EXE=    chords
 
SRC=    chords.cc mapping.cc tree.cc split.cc utils.cc
 
HD=     chords.h Makefile
 
# 
# No need to edit below this line 
# 
 
.SUFFIXES: 
.SUFFIXES: .cc .o 
 
OBJ=    $(SRC:.cc=.o) 
 
.cc.o: 
	$(CC) $(CFLAGS)-c $(LFLAGS) $< 
 
all:    $(EXE) 
 
$(EXE): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS) 
 
$(OBJ): $(MF) $(HD) 
 
clean: 
	rm -f $(OBJ) $(EXE) *~

clean-all: 
	rm -f $(OBJ) $(EXE) *~
