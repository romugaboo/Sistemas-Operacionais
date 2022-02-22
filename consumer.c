#include <stdio.h>
#include "producer_consumer.h"
#include "shared_memory.h"

int main (int argc, char *argv []){
    int out = 0, item_consumed = 0;
    size_t buffer_size = BUFFER_SIZE * sizeof(int);
    int *buffer = (int *) sm_create("buffer", buffer_size, O_CREAT | O_RDWR, 0666, PROT_READ | PROT_WRITE);
    int *count = (int *) sm_create("count", sizeof(int), O_CREAT | O_RDWR, 0666, PROT_READ | PROT_WRITE);

    while (*count > 0){
        item_consumed = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        *count = *count - 1;
        printf ("Consumido! Count = %d\n", *count);
    }

}