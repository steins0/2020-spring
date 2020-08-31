import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.BlockingQueue;

public class Demo {
    public static void main(String[] args) {
        BlockingQueue<String> blockingQueue = new LinkedBlockingQueue(4);
        new Thread(new Producer(blockingQueue), "First Producer").start();
        new Thread(new Consumer(blockingQueue), "First Consumer").start();
        new Thread(new Consumer(blockingQueue), "Second Consumer").start();
    }
}

// Producer
class Producer implements Runnable {
    private BlockingQueue<String> queue;

    public Producer(BlockingQueue<String> queue) {
        this.queue = queue;
    }

    public void run() {
        int i = 0;
        while (true) {
            try {
                String product = String.valueOf(i);
                queue.put(product);
                System.out.println("Thread(" + Thread.currentThread().getName() + ")produced: " + product
                        + "; We now have " + queue.size() + " products.");
                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            i++;
        }
    }
}

// Consumer
class Consumer implements Runnable {
    private BlockingQueue<String> queue;

    public Consumer(BlockingQueue<String> queue) {
        this.queue = queue;
    }

    public void run() {
        String tempStr = null;
        while (true) {
            try {
                tempStr = queue.take();
                System.out.println("Thread( " + Thread.currentThread().getName() + ")consumed:" + tempStr
                        + "; We now have " + queue.size() + " products.");
                try {
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}