all:clean queue coder gpt second

coder:queue
	gcc coder.c queue.o ./libCodec.so -o coder -Wall -lpthread -g 
	# ./coder 12 -e

queue:
	gcc myqueue.c -c -o queue.o -Wall -lpthread -g 


gpt:
	gcc gpt.c -o test -Wall -lpthread -g

second:queue
	gcc second.c queue.o ./libCodec.so  -o second -Wall -lpthread -g

clean:
	-rm -f encoder tester a.out *.o coder test
