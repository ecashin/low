OBJ = subs.o main.o
CFLAGS = -Wall -g

testt: t
	./t

clean:
	rm -f t *.o

t: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $* $(OBJ) $(LIBS)

subs.o: subs.asm

main.o: main.c

%.o: %.asm
	nasm -fmacho64 $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<
