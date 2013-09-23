PROG = hilo
OBJ = subs.o main.o
CFLAGS = -Wall -g
ifeq ($(shell uname),Linux)
TARGET = elf64
else
TARGET = macho64
NASM_FLAGS += -Dhilo=_hilo
endif

testt: $(PROG)
	./$(PROG)

.PHONY: clean realclean

realclean: clean
	rm -f *~

clean:
	rm -f $(PROG) $(OBJ)

$(PROG): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $* $(OBJ) $(LIBS)

subs.o: subs.asm

main.o: main.c

%.o: %.asm
	nasm $(NASM_FLAGS) -f$(TARGET) $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<
