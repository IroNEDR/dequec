CC=clang
CFLAGS=-Wall -g
OUT=/build

all: dequetest

deque.o: deque.c deque.h
	$(CC) $(CFLAGS) -c deque.c -o $(OUT)/$@

deque.so: deque.c deque.h
	$(CC) $(CFLAGS) -fPIC -shared -o $(OUT)/$@ deque.c -lc

dequetest: deque_test.c deque.o
	$(CC) $(CFLAGS) -o $(OUT)/$@ $^

clean:
	rm $(OUT)/*