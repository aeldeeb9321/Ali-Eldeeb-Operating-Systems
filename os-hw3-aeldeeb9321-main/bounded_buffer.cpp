#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include <iostream>

#include <pthread.h>
#include <semaphore.h>
#include <atomic>

using namespace std;

int run_time;
int *buffer;
int buffer_size;

int num_producers;
int num_consumers;

sem_t empty; //when buffer is empty, call the producer and sleep consumer.
sem_t full;  //when buffer is full, call the consumer and sleep the producer 

pthread_mutex_t mutex; //to lock the buffer which prevents race conditions.

int prod_idx = 0;
int cons_idx = 0;

atomic_int producer_num(0);
atomic_int consumer_num(0);

void * producer(void * arg)
{
    int myNum = producer_num.fetch_add(1) + 1;
    printf("I am producer, myNum = %d\n", myNum);
    
    while(true) 
    {
        int sec = rand() % 5;
        if (sec == 0)
            sec++;
        sleep(sec);

        int item = rand() % 100;
        while (item == 0)
        {
            item = rand() % 100;
        }

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[prod_idx] = item;
        prod_idx = (prod_idx + 1) % buffer_size;
        cout << myNum << ": slept " << sec << ", produced " << item << " in slot " << prod_idx << endl;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void * consumer(void * arg)
{
    int myNum = consumer_num.fetch_add(1) + 1;
    printf("I am consumer, myNum = %d\n", myNum);

    while(true) 
    {
        int sec = rand()%5;
        if (sec == 0)
            sec++;
        sleep(sec);

        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[cons_idx];
        cons_idx = (cons_idx + 1) % buffer_size;
        cout << myNum << ": slept " << sec << ", consumed " << item << " from slot " << cons_idx << endl;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}


int main(int argc, char ** argv)
{

    if (argc != 5)
    {
        cout << "Wrong number of arguments." << endl;
        cout << "Usage: bounded_buffer <run_time> <buffer_size> <num_producers> <num_consumers> " << endl;
        exit(1);
    }

    if (stoi(argv[1]) <= 0)   
    {
        cout << argv[0] << " " << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4] << endl;
        cout << "run_time must be greater than 0" << endl;
        exit(1);
    }

    if (stoi(argv[2]) <= 0)   
    {
        cout << argv[0] << " " << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4] << endl;
        cout << "buffer_size must be greater than 0" << endl;
        exit(1);
    }
    if (stoi(argv[3]) <= 0)   
    {
        cout << argv[0] << " " << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4] << endl;
        cout << "num_producers must be greater than 0" << endl;
        exit(1);
    }
    if (stoi(argv[4]) <= 0)   
    {
        cout << argv[0] << " " << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4] << endl;
        cout << "num_consumers must be greater than 0" << endl;
        exit(1);
    }


    run_time = stoi(argv[1]);  // The length of time the program should run
    buffer_size = stoi(argv[2]);
    num_producers = stoi(argv[3]); // The number of producers and consumers we will have
    num_consumers = stoi(argv[4]);

    buffer = (int *)malloc(sizeof(int) * buffer_size); // The buffer that will be produced into and consumed from. 

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, buffer_size);
    sem_init(&full, 0, 0);

    srand(time(NULL));

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for (int i = 0; i < num_producers; ++i) 
    {
        pthread_t thread_id;
        pthread_create(&thread_id, &attr, producer, NULL);
    }

    for (int i = 0; i < num_consumers; ++i) 
    {
        pthread_t thread_id;
        pthread_create(&thread_id, &attr, consumer, NULL);
    }

    sleep(run_time);

    // When the main program is done sleeping, we exit. This will cause all the threads to exit.
    // In other applications, the main program might want to wait for the child threads to complete. 
    // This is accomplished with the pthread_join() function (https://man7.org/linux/man-pages/man3/pthread_join.3.html)

    free(buffer);
    exit(0);
}
// TODO: Declare any other global variables you will need to 
//       use to implement your algorithm

    // Now the main program sleeps for as long as the program is supposd to run (based on the command line
    // argument). While the main thread is sleeping, all of the child threads will be busily producing and consuming.


    // Start the producer and consumer threads.

// These atomic variables will be used simply to generate unique numbers
// to identify each thread.

    // TODO: Initialize the semaphore(s) you are using in your algorithm.
    //       Use the function sem_init() - see https://man7.org/linux/man-pages/man3/sem_init.3.html
    //   

    // Set my unique thread number, to be used in the output statements below.
    // Set my unique thread number, to be used in the output statements below.

        // TODO: Sleep for a random amount of time between 1 and 5 seconds
        //       Make sure to save the amount of time that was slept, so it can 
        //       be printed out below.


        // TODO: "Produce" an item by generating a random number between 1 and 100 and 
        //       assigning it to "item"

        

        // TODO: Implement the meat of the producer algorithm, using any semaphores and
        //       mutex locks that are needed to ensure safe concurrent access.
        //
        //       After producing your item and storing it in the buffer, print a line
        //       in the following format:
        //

        //       <myNum>: slept <seconds>, produced <item> in slot <buffer slot>
        //
        //       For example: 
        //       7: slept 5, produced 27 in slot 2


        // TODO: Sleep for a random amount of time between 1 and 5 seconds
        //       Make sure to save the amount of time that was slept, so it can 
        //       be printed out below.

            // The item that will be consumed
        
        // TODO: "Consume" an item by retrieving the next item from the buffer.

        
        // TODO: Implement the meat of the consumer algorithm, using any semaphores and
        //       mutex locks that are needed to ensure safe concurrent access.
        //
        //       After consuming your item and storing it in "item", print a line
        //       in the following format:
        //
        //       <myNum>: slept <seconds>, produced <item> in slot <buffer slot>
        //       For example: 
        //       2: slept 3, consumed 22 from slot 2
    