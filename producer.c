#include <stdio.h>
#include "producer_consumer.h"
#include "shared_memory.h"

int main (int argc, char *argv []){
    int in = 0, item = 0;
    size_t buffer_size = BUFFER_SIZE * sizeof(int);
    int *buffer = (int *) sm_create("buffer", buffer_size, O_CREAT | O_RDWR, 0666, PROT_READ | PROT_WRITE);
    int *count = (int *) sm_create("count", sizeof(int), O_CREAT | O_RDWR, 0666, PROT_READ | PROT_WRITE);
    
    while (*count < BUFFER_SIZE){
        buffer[in] = item++;
        in = (in + 1) % BUFFER_SIZE;
        *count = *count + 1;
        printf ("Produzido! Count = %d\n", *count);
    }
}