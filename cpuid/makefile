OBJ = subs.o main.o
CFLAGS = -Wall -g
# use elf64 for Linux
TARGET = macho64

testt: t
	./t

clean:
	rm -f t *.o

t: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $* $(OBJ) $(LIBS)

subs.o: subs.asm

main.o: main.c

%.o: %.asm
	nasm -f$(TARGET) $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<
