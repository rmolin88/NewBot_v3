# TODO: try to make a unique make file that launches after done
CC = g++
SRC = ../src/Main.cpp
OBJ = $(notdir $(SRC:.cpp=.o))
CFLAGS =-std=c++14 -Wall -O3 -c
LDFLAGS =-lserial -lpthread
EXE = remote.out
all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $^ -o $(EXE) $(LDFLAGS) 

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $^ 

clean:
	rm -f *.o $(EXE)
