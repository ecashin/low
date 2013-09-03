OBJ = subs.o main.o
CFLAGS = -Wall -g
ifeq ($(shell uname),Linux)
TARGET = elf64
else
TARGET = macho64
NASM_FLAGS += -Dcpuidfn=_cpuidfn
endif

testt: t
	./t

clean:
	rm -f t *.o

t: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $* $(OBJ) $(LIBS)

subs.o: subs.asm

main.o: main.c

%.o: %.asm
	nasm $(NASM_FLAGS) -f$(TARGET) $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<
