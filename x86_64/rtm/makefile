PROG = rtmdemo
OBJ = subs.o main.o
CFLAGS = -Wall -g
# EXTRA_CFLAGS += -save-temps
ifeq ($(shell uname),Linux)
TARGET = elf64
else
TARGET = macho64
NASM_FLAGS += $(shell for i in `grep '^[a-z][0-9a-z]*:' *.s | sed 's!:!!'`; do echo '-D'$$i'=_'$$i; done)
# -D$(PROG)=_$(PROG) -Drtm=_rtm -Drtminit=_rtminit
endif

.PHONY: testt

testt: $(PROG)
	./$(PROG)

$(PROG): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $* $(OBJ) $(LIBS)

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
