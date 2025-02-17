i#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Función que ejecutará cada hilo
void *tarea_hilo(void *argumento) {
    int id_hilo = *(int *)argumento;
    printf("Hilo %d: ¡Hola desde el hilo!\n", id_hilo);
    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[5]; // Arreglo para almacenar los identificadores de los hilos
    int ids[5]; // Arreglo para los IDs de los hilos

    // Crear 5 hilos
    for (int i = 0; i < 5; i++) {
        ids[i] = i;
        int resultado = pthread_create(&hilos[i], NULL, tarea_hilo, &ids[i]);
        if (resultado) {
            printf("Error al crear el hilo %d\n", i);
            exit(-1);
        }
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < 5; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("Hilo principal: Todos los hilos han terminado.\n");
    pthread_exit(NULL);
}

