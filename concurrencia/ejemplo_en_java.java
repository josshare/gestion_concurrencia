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
        MiHilo[] hilos = new MiHilo[5];

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

