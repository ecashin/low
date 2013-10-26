CFLAGS = -g -Wall
LIBS = -lpthread

.PHONY: count_demo clean realclean

count_demo: demo
	time sh -c './demo 20 200000; echo $$?'

demo: main.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

realclean: clean
	rm -f *~

clean:
	rm -f demo
