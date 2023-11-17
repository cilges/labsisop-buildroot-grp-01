#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

int THREADS = 4;
int BUFFER_SIZE = 100000;

char *buffer;
int buffer_pointer;
pthread_mutex_t mutex;

void *task(void *arg)
{
    int tid = (int)(long int)arg;

    while (1) {
        pthread_mutex_lock(&mutex);
        if (buffer_pointer >= BUFFER_SIZE) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        // printf("Thread %d: %d\n", tid, buffer_pointer);
        buffer[buffer_pointer] = 'A' + tid;
        buffer_pointer++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void show_buffer()
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        printf("%c", buffer[i]);
    }
}

void count_buffer()
{
    int *countLetter = (int *)malloc(sizeof(int) * THREADS);
    char aux = buffer[0];

    for (int i = 0; i < THREADS; i++)
    {
        countLetter[i] = 0;
    }

    countLetter[aux - 'A']++;

    for (int i = 1; i < BUFFER_SIZE; i++)
    {
        if (buffer[i] != aux)
        {
            countLetter[aux - 'A']++;
            aux = buffer[i];
        }
    }

    for (int i = 0; i < THREADS; i++)
    {
        printf("Thread %c: %d\n", 'A' + i, countLetter[i]);
    }

}

int main(int argc, char *argv[])
{
    long int i;

    THREADS = atoi(argv[1]);
    BUFFER_SIZE = atoi(argv[2]);

    buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    pthread_t threads[THREADS];

    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < THREADS; i++)
    {
        pthread_create(&threads[i], NULL, task, (void *)i);
    }

    for (i = 0; i < THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);

    // show_buffer();
    // free(buffer);
    count_buffer();
    return 0;
}
