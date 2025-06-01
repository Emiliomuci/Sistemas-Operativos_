//Crear dos hilos hilo_fibonacci, hilo_primo
//main lee un número n
//Hilo fibonacci escribe los n primeros términos fibonacci
//Hilo_primo calcula si n es primo

//Obviamente main tiene que esperar a que acaben los dos hilos

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h> 
#include <semaphore.h>
#include <pthread.h>

int opFibonacci;
static int *num;
pthread_mutex_t mutex;

void* hiloFibonacci(void* arg) {
    pthread_mutex_lock(&mutex);

    int a = 0;
    int b = 1;

    printf("Serie Fibonacci: %d, ", b);
    for (int i = 1; i < *num; i++) { // comienza desde 1
        opFibonacci = a + b;
        a = b; 
        b = opFibonacci;
        printf("%d, ", opFibonacci);
    }
    printf("\n");

    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* hiloPrimo(void* arg) {
    pthread_mutex_lock(&mutex);

    int primo = 1; // asumimos que sí es primo

    if (*num <= 1) {
        primo = 0;
    } else {
        for (int i = 2; i <= *num / 2; i++) {
            if (*num % i == 0) {
                primo = 0;
                break; // ya no es primo, salimos
            }
        }
    }

    if (primo) {
        printf("Sí es primo: %d\n", *num);
    } else {
        printf("No es primo: %d\n", *num);
    }

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char **argv) {
    pthread_t hilo1, hilo2;

    num = mmap(NULL, sizeof *num, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (num == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    printf("Escribe un número: ");
    scanf("%d", num);

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&hilo1, NULL, hiloFibonacci, NULL);
    pthread_create(&hilo2, NULL, hiloPrimo, NULL);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
