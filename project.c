#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>


#define BUFFER_SIZE 10  // Change this to set the buffer size
#define NUM_ITEMS 10    // Change this to set the number of integers to produce/consume
#define MIN_VALUE 1     // Change this to set the minimum random value
#define MAX_VALUE 100  // Change this to set the maximum random value


int buffer[BUFFER_SIZE];
int buffer_index = 0;
int sum = 0;

pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t buffer_empty, buffer_full;

void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;

        sem_wait(&buffer_full);  // Wait if buffer is full
        pthread_mutex_lock(&buffer_mutex);

        buffer[buffer_index++] = item;
        
        printf("%d ) Producer Thread Produced: %d\n", i,item);

        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&buffer_empty);  // Signal that buffer is not empty
    }
    return NULL;
}


void *consumer(void *arg) {

    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&buffer_empty);  // Wait if buffer is empty
        pthread_mutex_lock(&buffer_mutex);

        int item = buffer[--buffer_index];
        sum += item;
        printf("%d ) Consumer Thread Consumed: %d\n",i, item);

        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&buffer_full);  // Signal that buffer is not full
    }

    float average = (float)sum / NUM_ITEMS;
    printf("\n\n");
    printf("Average of all is: %.2f\n", average);

    return NULL;
}

int main() {
    srand(time(NULL));


    pthread_t producer_thread, consumer_thread;

    sem_init(&buffer_empty, 0, 0);
    sem_init(&buffer_full, 0, BUFFER_SIZE);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&buffer_empty);
    sem_destroy(&buffer_full);

    return 0;
}