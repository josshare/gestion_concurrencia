ipublic class PingPong extends Thread {
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

