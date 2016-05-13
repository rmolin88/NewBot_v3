CXX = g++
SRC = Uart.cpp
OBJ = $(SRC:.cpp=.o)
CFLAGS =-std=c++14 -Wall -O3 -c
LDFLAGS =-lserial -lpthread
ARCHIVE =ar -cvq
EXE = libuart.a
all: $(EXE)

$(EXE): $(OBJ)
	$(ARCHIVE) $(EXE) $(OBJ)
	cp $(EXE) ../odroid/build

$(OBJ): $(SRC)
	$(CXX) $(CFLAGS) $^ $(LDFLAGS) 

clean:
	rm -f *.o $(EXE)
