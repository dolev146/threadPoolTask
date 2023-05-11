#ifndef READ_CHUNCKS_H_
#define READ_CHUNCKS_H_


extern void (*chosen_function)(char *, int); // decrypt or encrypt
extern int order;
extern int key;

void read_chunks();

#endif // READ_CHUNCKS_H