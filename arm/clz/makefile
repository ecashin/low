PROG = clz
OBJ = clz.o main.o
CFLAGS = -Wall #-g
# EXTRA_CFLAGS += -save-temps

$(PROG): $(OBJ)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJ) $(LIBS)

.PHONY: clean realclean template
clean:
	rm -f $(OBJ) $(PROG)

realclean: clean
	rm -f *~ $(OBJ:.o=.s) $(OBJ:.o=.i) add1.[ois]

template: add1.o

clz.o: clz.s
	as -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $<
