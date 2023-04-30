all:queue coder task stdinExample

coder:queue
	gcc coder.c queue.o ./libCodec.so -o coder -Wall -lpthread 

queue:
	gcc myqueue.c -c -o queue.o -Wall -lpthread

task:
	gcc basic_main.c ./libCodec.so -o encoder

stdinExample:
		gcc stdin_main.c ./libCodec.so -o tester

clean:
	-rm -f encoder tester 2>/dev/null a.out  *.o
