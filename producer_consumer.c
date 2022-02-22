#include <pthread.h>
#include <stdio.h>
#define BUFFER_SIZE 10

int count = 0;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void *producer();
void *consumer();

int main (int argc, int *argv[]){
    pthread_t producer_tid;
    pthread_t consumer_tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create (&producer_tid, &attr, producer, NULL);
    pthread_create (&consumer_tid, &attr, producer, NULL);
    pthread_join (producer_tid, NULL);
    pthread_join (consumer_tid, NULL);
}

void *producer (){
    int item = 0;

    while (count < BUFFER_SIZE){
        buffer[in] = item++;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf ("Produzido! Count = %d\n", count);
    }
    pthread_exit (0);
}

void *consumer (){
    int out = 0, item_consumed = 0;

    while (count > 0){
        item_consumed = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        printf ("Consumido! Count = %d\n", count);
        pthread_exit (0);
    }
}