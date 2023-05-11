#include "codec.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	char data[] = "abc";
	int key = 1;

	encrypt(data,key);
	printf("encripted data: %s\n",data);

	decrypt(data,key);
	printf("decripted data: %s\n",data);

	return 0;
}
