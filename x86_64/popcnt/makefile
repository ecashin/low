OBJ = subs.o main.o
CFLAGS = -Wall -g
ifeq ($(shell uname),Linux)
TARGET = elf64
else
TARGET = macho64
NASM_FLAGS += -Dcanpopcnt=_canpopcnt -Dcountbits=_countbits
endif

t: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $* $(OBJ) $(LIBS)

testt: t
	./t

clean:
	rm -f t *.o

subs.o: subs.asm

main.o: main.c

%.o: %.asm
	nasm $(NASM_FLAGS) -f$(TARGET) $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<
