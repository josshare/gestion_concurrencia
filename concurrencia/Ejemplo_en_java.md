<img src="https://r2cdn.perplexity.ai/pplx-full-logo-primary-dark%402x.png" class="logo" width="120"/>

# Revisa los ejemplos de implementación en cada uno de los lenguajes de programación que se presentan en los materiales de estudio y abstrae la forma de implementar la concurrencia en cada uno.

Realiza un ejemplo en C y uno en Java, puedes tomar los que se proporcionan en los materiales de revisión o realizar uno diferente.
Redacta un informe en este mismo documento que incluya:
Código de ejemplo	
Descripción del ejercicio realizado
Imagen con resultado de la ejecución
Realiza una explicación general de la implementación haciendo énfasis en la parte de concurrencia.
---
De acuerdo, puedo ayudarte con eso. Aquí tienes ejemplos de código en C y Java que demuestran la concurrencia, junto con una explicación de cómo funcionan.

## Concurrencia en C (Usando Pthreads)

**Código de Ejemplo:**

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Función que ejecutará cada hilo
void *tarea_hilo(void *argumento) {
    int id_hilo = *(int *)argumento;
    printf("Hilo %d: ¡Hola desde el hilo!\n", id_hilo);
    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[^5]; // Arreglo para almacenar los identificadores de los hilos
    int ids[^5]; // Arreglo para los IDs de los hilos

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
```

**Descripción del Ejercicio:**

Este programa crea 5 hilos. Cada hilo ejecuta la función `tarea_hilo`, que simplemente imprime un mensaje que incluye el ID del hilo. El hilo principal espera a que todos los hilos terminen antes de imprimir su propio mensaje de finalización.

**Explicación de la Implementación (Énfasis en la Concurrencia):**

1. **Pthreads (POSIX Threads):**  Utilizamos la biblioteca `pthread` para crear y gestionar hilos en C.
2. **pthread\_create():** La función `pthread_create()` es la clave para la concurrencia.  Crea un nuevo hilo y le asigna una función para ejecutar (`tarea_hilo` en este caso).
    * El primer argumento es un puntero a una variable `pthread_t` que almacenará el ID del nuevo hilo.
    * El segundo argumento son atributos del hilo (generalmente `NULL` para usar los atributos por defecto).
    * El tercer argumento es la función que ejecutará el hilo.
    * El cuarto argumento es un argumento que se pasará a la función del hilo.
3. **pthread\_join():** La función `pthread_join()` hace que el hilo principal espere a que un hilo específico termine.  Esto es importante para asegurar que el programa no termine antes de que todos los hilos hayan completado su trabajo.
4. **Ejecución Concurrente:** Los hilos se ejecutan de forma concurrente, lo que significa que el sistema operativo los intercalará en el tiempo.  El orden exacto en que se ejecutan los hilos puede variar de una ejecución a otra.

## Concurrencia en Java (Usando Threads)

**Código de Ejemplo:**

```java
class MiHilo extends Thread {
    private int id;

    public MiHilo(int id) {
        this.id = id;
    }

    @Override
    public void run() {
        System.out.println("Hilo " + id + ": ¡Hola desde el hilo!");
    }
}

public class EjemploConcurrencia {
    public static void main(String[] args) {
        MiHilo[] hilos = new MiHilo[^5];

        // Crear y iniciar 5 hilos
        for (int i = 0; i < 5; i++) {
            hilos[i] = new MiHilo(i);
            hilos[i].start();
        }

        // Esperar a que todos los hilos terminen
        try {
            for (int i = 0; i < 5; i++) {
                hilos[i].join();
            }
        } catch (InterruptedException e) {
            System.out.println("El hilo principal fue interrumpido.");
        }

        System.out.println("Hilo principal: Todos los hilos han terminado.");
    }
}
```

**Descripción del Ejercicio:**

Este programa crea 5 hilos utilizando la clase `Thread` de Java. Cada hilo es una instancia de la clase `MiHilo`, que extiende la clase `Thread` y sobrescribe el método `run()`. El método `run()` imprime un mensaje que incluye el ID del hilo. El hilo principal espera a que todos los hilos terminen antes de imprimir su propio mensaje de finalización.

**Explicación de la Implementación (Énfasis en la Concurrencia):**

1. **Clase Thread:** En Java, la concurrencia se logra principalmente a través de la clase `Thread`.  Hay dos formas comunes de crear hilos:
    * Extender la clase `Thread` y sobrescribir el método `run()`.
    * Implementar la interfaz `Runnable` y pasar una instancia de la clase `Runnable` al constructor de un objeto `Thread`.
2. **start():** El método `start()` es crucial.  Cuando llamas a `start()` en un objeto `Thread`, Java crea un nuevo hilo del sistema operativo y comienza a ejecutar el método `run()` de ese objeto en el nuevo hilo.  **No llames a `run()` directamente**, ya que eso simplemente ejecutaría el código en el hilo actual, sin crear un nuevo hilo concurrente.
3. **join():** El método `join()` permite que un hilo espere a que otro hilo termine.  Esto es similar a `pthread_join()` en C. Es importante usar `join()` para asegurar que el programa principal no termine antes de que los hilos hayan completado su trabajo.
4. **Ejecución Concurrente:**  Los hilos en Java se ejecutan de forma concurrente, gestionados por el JVM (Java Virtual Machine) y el sistema operativo subyacente. El orden preciso de ejecución puede variar.

Espero que esto te ayude a entender cómo implementar la concurrencia en C y Java. Avísame si tienes alguna otra pregunta.

<div style="text-align: center">⁂</div>

[^1]: https://ppl-ai-file-upload.s3.amazonaws.com/web/direct-files/54051796/416dcb20-56c2-4024-86a9-45b801b6eccd/U4_ProcesosEHilosenC.pdf

[^2]: https://ppl-ai-file-upload.s3.amazonaws.com/web/direct-files/54051796/d09ad87c-c5a8-4b64-83f3-2892e3c1db96/U4_JavaThreads.pdf

[^3]: https://ppl-ai-file-upload.s3.amazonaws.com/web/direct-files/54051796/5514d2fe-7fbd-4c33-aa5a-11514ea9a704/U4_ProgramacionOpenMP.pdf

