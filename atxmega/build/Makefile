CC = avr-gcc

EXE = atxmega
SRC = $(wildcard ../src/*.c)
SRC_MAIN = $(EXE).c
OBJ = $(notdir $(SRC:.c=.o))
HEX = $(SRC_MAIN:.c=.hex)
ELF = $(SRC_MAIN:.c=.elf)
DEVICE=atxmega128a4u
AVR_SRC_FLAGS =-g -mmcu=$(DEVICE) -Os -c
AVR_OBJ_FLAGS =-g -mmcu=$(DEVICE)
AVR_HEX_FLAGS =avr-objcopy -j .text -j .data -O ihex
PROGRAMMER=dfu-programmer


all: $(HEX)

$(HEX): $(ELF)
	$(AVR_HEX_FLAGS) $^ $(HEX)

$(ELF): $(OBJ)
	$(CC) $(AVR_OBJ_FLAGS) $^ -o $(ELF)

$(OBJ): $(SRC)
	$(CC) $(AVR_SRC_FLAGS) $^

clean:
	rm -f *.o $(EXE).hex $(EXE).elf

flash:
	$(PROGRAMER) $(DEVICE) flash $(EXE).hex

erase:
	$(PROGRAMER) $(DEVICE) erase

start:
	$(PROGRAMER) $(DEVICE) start
