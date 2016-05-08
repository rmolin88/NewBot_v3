CC = g++
# SRC = $(wildcard ../src/*.cpp)
SRC = ../src/Main.cpp ../src/SerialXmega.cpp
OBJ = $(notdir $(SRC:.cpp=.o))
CFLAGS =-std=c++14 -Wall -O3 -c
LDFLAGS =-lserial -lpthread -pthread
EXE = io
all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $^ -o $(EXE) $(LDFLAGS) 
	# $(CC) $^ -o $(EXE) $(LDFLAGS)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $^ 

clean:
	rm -f *.o $(EXE)
