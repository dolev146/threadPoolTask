all: task stdinExample

task:
	gcc basic_main.c ./libCodec.so -o encoder

stdinExample:
		gcc stdin_main.c ./libCodec.so -o tester

clean:
	-rm -f encoder tester 2>/dev/null a.out 
