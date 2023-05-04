all:clean myqueue coder task stdinExample

coder:myqueue
	gcc coder.c queue.o ./libCodec.so -o coder -Wall -lpthread -g

myqueue:
	gcc -c myqueue.c -o queue.o -Wall -Werror -fpic -g

task:
	gcc basic_main.c ./libCodec.so -o encoder -g

stdinExample:
		gcc stdin_main.c ./libCodec.so -o tester -g

clean:
	-rm -f encoder tester 2>/dev/null a.out main *.o coder
