/* ThreadDemo.java — Creating threads by extending Thread */
public class ThreadDemo {

    /* Custom thread class */
    static class CounterThread extends Thread {
        private String name;
        private int count;

        CounterThread(String name, int count) {
            this.name = name;
            this.count = count;
        }

        @Override
        public void run() {
            for (int i = 1; i <= count; i++) {
                System.out.printf("[%s] Count: %d (Thread ID: %d)%n",
                    name, i, Thread.currentThread().getId());
                try {
                    Thread.sleep(500);  /* Simulate work */
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            System.out.printf("[%s] Finished!%n", name);
        }
    }

    public static void main(String[] args) throws InterruptedException {
        System.out.println("Main thread (ID: " + Thread.currentThread().getId() + "): starting...");
        System.out.println("PID: " + ProcessHandle.current().pid() + " — observe threads with ps or htop\n");

        /* Create and start 3 threads */
        CounterThread t1 = new CounterThread("Alpha", 5);
        CounterThread t2 = new CounterThread("Beta", 5);
        CounterThread t3 = new CounterThread("Gamma", 5);

        t1.start();
        t2.start();
        t3.start();

        /* Wait for all threads to finish */
        t1.join();
        t2.join();
        t3.join();

        System.out.println("\nMain thread: all threads finished.");
    }
}
