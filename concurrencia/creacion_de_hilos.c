#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *hola(void *arg) {
    char *msg = "Hola";
    int i;
    for (i = 0; i < strlen(msg); i++) {
        printf(" %c", msg[i]);
        fflush(stdout);
        usleep(1000000); // 1 segundo
    }
    return NULL;
}

void *mundo(void *arg) {
    char *msg = " mundo ";
    int i;
    for (i = 0; i < strlen(msg); i++) {
        printf(" %c", msg[i]);
        fflush(stdout);
        usleep(1000000); // 1 segundo
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t h1;
    pthread_t h2;

    pthread_create(&h1, NULL, hola, NULL);
    pthread_create(&h2, NULL, mundo, NULL);

    pthread_join(h1, NULL); // Esperar a que el hilo h1 termine
    pthread_join(h2, NULL); // Esperar a que el hilo h2 termine

    printf("Fin\n");

    return 0;
}

