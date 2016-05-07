CC = g++
# SRC = $(wildcard ../src/*.cpp)
# SRC = ../src/libserial.cpp ../src/xbee.cpp
SRC = ../src/xbee.cpp
OBJ = $(notdir $(SRC:.cpp=.o))
CFLAGS =-std=c++14 -Wall -c
LIB = /usr/lib/libxbeep.so
LDFLAGS =-L$(LIB) -lxbeep -lxbee -lpthread -lrt -lserial -lpthread
EXE = io
all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $^ -o $(EXE) $(LDFLAGS)

# $(OBJ): $(SRC) $(LIB)
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $^

clean:
	rm -f *.o $(EXE)
