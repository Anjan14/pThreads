#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define SEED 35791246

int count = 0;
pthread_mutex_t mutex;

double get_time() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + t.tv_usec / 1e6;
}

void* compute_pi(void* arg) {
    int i;
    int iterations = *(int*)arg;
    int local_count = 0;
    double x, y, z;

    for (i = 0; i < iterations; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        z = x * x + y * y;
        if (z <= 1) {
            local_count++;
        }
    }

    pthread_mutex_lock(&mutex);
    count += local_count;
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <number_of_points> <number_of_threads>\n", argv[0]);
        return -1;
    }

    int num_points = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    pthread_t threads[num_threads];
    int points_per_thread = num_points / num_threads;
    int i;

    pthread_mutex_init(&mutex, NULL);
    srand(SEED);

    double start_time = get_time();

    for (i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, compute_pi, &points_per_thread);
    }

    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    double end_time = get_time();
    double pi = (double)count / num_points * 4;
    printf("Computed PI = %g\n", pi);
    printf("Elapsed time: %f seconds\n", end_time - start_time);

    pthread_mutex_destroy(&mutex);
    return 0;
}

/*
    Output: Time vs. Number of Threads
     1. 80000 and 1:
         Computed PI = 3.14105
         Elapsed time: 0.001681 seconds
     2. 80000 and 2:
         Computed PI = 3.12765
         Elapsed time: 0.000897 seconds
     3. 80000 and 4:
         Computed PI = 3.13345
         Elapsed time: 0.000538 seconds
     4. 80000 and 8:
         Computed PI = 3.10695
         Elapsed time: 0.000644 seconds
 */
/*
 Output: Time vs. Number of Sample Points
  1. 20000 and 4:
      Computed PI = 3.124
      Elapsed time: 0.000188 seconds
  2. 40000 and 4:
      Computed PI = 3.1484
      Elapsed time: 0.000509 seconds
  3. 80000 and 4:
      Computed PI = 3.13105
      Elapsed time: 0.000522 seconds
  4. 160000 and 4:
      Computed PI = 3.12323
      Elapsed time: 0.000970 seconds
 */
