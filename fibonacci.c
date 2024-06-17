#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int* fib_sequence;

void* generate_fibonacci(void* arg) {
    int n = *(int*)arg;

    if (n >= 1) fib_sequence[0] = 0;
    if (n >= 2) fib_sequence[1] = 1;

    for (int i = 2; i < n; i++) {
        fib_sequence[i] = fib_sequence[i - 1] + fib_sequence[i - 2];
    }

    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_fibonacci_numbers>\n", argv[0]);
        return -1;
    }

    int num_fib = atoi(argv[1]);
    fib_sequence = (int*)malloc(num_fib * sizeof(int));

    pthread_t fib_thread;
    pthread_create(&fib_thread, NULL, generate_fibonacci, &num_fib);
    pthread_join(fib_thread, NULL);

    printf("Fibonacci sequence:\n");
    for (int i = 0; i < num_fib; i++) {
        printf("%d ", fib_sequence[i]);
    }
    printf("\n");

    free(fib_sequence);
    return 0;
}
