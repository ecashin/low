PROG = diffidx
OBJ = subs.o main.o
CFLAGS = -Wall -g
# EXTRA_CFLAGS += -save-temps
ifeq ($(shell uname),Linux)
TARGET = elf64
else
TARGET = macho64
NASM_FLAGS += -D$(PROG)=_$(PROG) -Dcpuidfn=_cpuidfn
endif

$(PROG): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $* $(OBJ) $(LIBS)

.PHONY: testt

testt: $(PROG)
	./$(PROG)

.PHONY: clean realclean

realclean: clean
	rm -f *~ main.s main.i *.rej *.orig

clean:
	rm -f $(PROG) $(OBJ)

subs.o: subs.s

main.o: main.c

%.o: %.s
	nasm $(NASM_FLAGS) -f$(TARGET) $<

%.o: %.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $<
