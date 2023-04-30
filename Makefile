all:queue coder 

coder:queue
	gcc coder.c queue.o ./libCodec.so -o coder -Wall -lpthread -g

queue:
	gcc myqueue.c -c -o queue.o -Wall -lpthread -g


clean:
	-rm -f encoder tester 2>/dev/null a.out  *.o
