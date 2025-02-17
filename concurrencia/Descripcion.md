De acuerdo, comprendo. Basaré las explicaciones y ejemplos en los documentos proporcionados, enfocándome en la creación de hilos y procesos en C y en los hilos en Java.

## Concurrencia en C (`U4_ProcesosEHilosenC.pdf`)

**Código de Ejemplo (Creación de Procesos):**

```c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    pid = fork();

    if (pid == -1) {
        printf("Fallo en fork\n");
        return -1;
    } else if (!pid) {
        // Proceso hijo
        printf("Proceso hijo: PID %d\n", getpid());
    } else {
        // Proceso padre
        printf("Proceso padre: PID %d\n", getpid());
    }

    return 0;
}
```

**Código de Ejemplo (Creación de Hilos):**

```c
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
```

**Descripción del Ejercicio:**

* **Creación de Procesos:** El primer ejemplo utiliza la función `fork()` para crear un nuevo proceso.  El proceso hijo ejecuta el mismo código que el padre, pero con un PID diferente. `fork()` retorna 0 en el hijo y el PID del hijo en el padre.
* **Creación de Hilos:** El segundo ejemplo utiliza la biblioteca `pthread` para crear dos hilos que imprimen "Hola" y "mundo" respectivamente, letra por letra con una pausa entre cada letra. Se utiliza `pthread_join()` para asegurar que el programa principal espere a que los hilos terminen antes de imprimir "Fin".

**Explicación de la Implementación (Énfasis en la Concurrencia):**

1. **Procesos vs. Hilos:**
    * **Procesos:**  Cada proceso tiene su propio espacio de memoria aislado. La comunicación entre procesos (si es necesaria) es más compleja y generalmente implica mecanismos como pipes o memoria compartida. La creación de procesos es más costosa en términos de recursos del sistema.
    * **Hilos:** Los hilos comparten el mismo espacio de memoria del proceso. Esto hace que la comunicación entre hilos sea más fácil (ya que pueden acceder a las mismas variables), pero también requiere cuidado para evitar condiciones de carrera y otros problemas de concurrencia. La creación de hilos es generalmente más rápida y consume menos recursos que la creación de procesos.
2. **`fork()`:** La función `fork()` crea un duplicado del proceso actual. Tanto el proceso padre como el hijo continúan la ejecución desde el punto donde se llamó a `fork()`. Es crucial verificar el valor de retorno de `fork()` para determinar si el código se está ejecutando en el proceso padre o en el proceso hijo.
3. **`pthread_create()`:** La función `pthread_create()` crea un nuevo hilo dentro del proceso actual. Requiere una función de inicio (que recibe un puntero `void*` como argumento y retorna un puntero `void*`) que será ejecutada por el nuevo hilo.
4. **`pthread_join()`:** Esta función hace que el hilo que la llama espere a que otro hilo termine. Es fundamental para la sincronización y para asegurar que el programa no termine prematuramente.
5. **Compilación con `pthread`:** Al compilar un programa que utiliza `pthread`, es necesario enlazar la biblioteca `pthread` usando la opción `-lpthread` al compilar con `gcc`.  Por ejemplo: `gcc -o mi_programa mi_programa.c -lpthread`

## Concurrencia en Java (`U4_JavaThreads.pdf`)

**Código de Ejemplo:**

```java
public class PingPong extends Thread {
    private String word;

    public PingPong(String s) {
        word = s;
    }

    public void run() {
        for (int i = 0; i < 3000; i++) {
            System.out.print(word);
            System.out.flush(); // Asegura que la salida se muestre inmediatamente
        }
    }

    public static void main(String[] args) {
        Thread tP = new PingPong("P");
        Thread tp = new PingPong("p");

        tp.start();
        tP.start();
    }
}
```

**Descripción del Ejercicio:**

Este programa crea dos hilos, uno que imprime la letra "P" 3000 veces y otro que imprime la letra "p" 3000 veces.  La salida resultante mostrará una mezcla de "P" y "p" debido a la ejecución concurrente de los hilos.

**Explicación de la Implementación (Énfasis en la Concurrencia):**

1. **Extender `Thread`:** La clase `PingPong` extiende la clase `Thread`. Esto permite que las instancias de `PingPong` se ejecuten como hilos separados.
2. **`run()` method:** El método `run()` contiene el código que se ejecutará cuando el hilo se inicie. En este caso, imprime la palabra asignada al hilo repetidamente.
3. **`start()` method:** El método `start()` es crucial. Llama a `start()`  se crea un nuevo hilo y se inicia la ejecución del método `run()` en ese nuevo hilo. **Nunca llames a `run()` directamente**, ya que eso simplemente ejecutará el código en el hilo actual, sin crear un nuevo hilo concurrente.
4. **Ejecución Concurrente:**  Los hilos `tP` y `tp` se ejecutan concurrentemente. El orden exacto en que se ejecutan y la cantidad de "P" o "p" que se imprimen consecutivamente pueden variar debido a la forma en que el sistema operativo programa los hilos.
5. **`System.out.flush()`:** Es importante utilizar `System.out.flush()` dentro del bucle para asegurarse de que la salida se escriba inmediatamente en la consola. De lo contrario, la salida podría almacenarse en búfer y no mostrarse en el orden esperado.

