CC = g++
SRC = $(wildcard ../src/*.cpp)
OBJ = $(notdir $(SRC:.cpp=.o))
CFLAGS =-std=c++14 -Wall -c
LDFLAGS =-lserial -lpthread
EXE = io
all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $^ -o $(EXE) $(LDFLAGS)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $^

clean:
	rm -f *.o $(EXE)
