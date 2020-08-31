import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class Threadpool {
    public static void main(String[] args) {
        ThreadPoolExecutor executor = new ThreadPoolExecutor(5, 10, 200, TimeUnit.MILLISECONDS,
                new ArrayBlockingQueue<Runnable>(5));

        for (int i = 0; i < 15; i++) {
            mytasks mytasks23 = new mytasks(i);
            executor.execute(mytasks23);
            System.out.println("the number of threads in the threadpool:" + executor.getPoolSize());
            System.out.println("the number of tasks in the queue:" + executor.getQueue());
            System.out.println("the number of tasks completed:" + executor.getCompletedTaskCount());
        }
        executor.shutdown();
    }
}

class mytasks implements Runnable {
    private int tasknum;

    public mytasks(int num) {
        this.tasknum = num;
    }

    public void run() {
        int sum = 0;
        System.out.println("Task" + tasknum + "is running");
        try {
            for (int i = 0; i < 15; i++) {
                sum += i;
            }
            Thread.sleep(4000);
        } catch (InterruptedException e) {
            e.printStackTrace();
            ;
        }
        System.out.println("Task" + tasknum + "has been done by 17030140076 LMY");
    }
}