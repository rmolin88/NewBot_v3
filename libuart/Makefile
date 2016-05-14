CXX = g++
SRC = Uart.cpp
OBJ = $(SRC:.cpp=.o)
CFLAGS =-std=c++14 -Wall -O3 -c
LDFLAGS =-lserial
ARCHIVE =ar -cvq
EXE = libuart.a
all: $(EXE)

$(EXE): $(OBJ)
	$(ARCHIVE) $(EXE) $(OBJ)

$(OBJ): $(SRC)
	$(CXX) $(CFLAGS) $^ $(LDFLAGS) 

clean:
	rm -f *.o $(EXE)
