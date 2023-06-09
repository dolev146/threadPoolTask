all:clean myqueue coder task stdinExample

coder:myqueue read_chunks startThreads
	gcc coder.c queue.o read_chunks.o startThreads.o ./libCodec.so -o coder -Wall -lpthread -g

startThreads:
	gcc -c startThread.c -o startThreads.o -Wall -Werror -fpic -g

read_chunks:
	gcc -c read_chunks.c -o read_chunks.o -Wall -Werror -fpic -g


myqueue:
	gcc -c myqueue.c -o queue.o -Wall -Werror -fpic -g

task:
	gcc basic_main.c ./libCodec.so -o basic_main -g

stdinExample:
		gcc stdin_main.c ./libCodec.so -o tester -g

clean:
	-rm -f encoder tester 2>/dev/null a.out main *.o coder
