CFLAGS = -g -Wall
LIBS = -lpthread

.PHONY: count_demo clean realclean

count_demo: demo
	time sh -c './demo 10 100000; echo $$?'
	time sh -c './demo 10 100000 1; echo $$?'

demo: main.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

realclean: clean
	rm -f *~

clean:
	rm -f demo
