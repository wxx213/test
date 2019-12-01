package process;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class TestCallable {
    public static void testcallable() {
        //创建一个线程池
        ExecutorService threadPool = Executors.newFixedThreadPool(3);

        //创建三个有返回值的任务
        MyCallable c1 = new MyCallable("线程1");
        MyCallable c2 = new MyCallable("线程2");
        MyCallable c3 = new MyCallable("线程3");

        Future f1 = threadPool.submit(c1);
        Future f2 = threadPool.submit(c2);
        Future f3 = threadPool.submit(c3);

        try {
            System.out.println(f1.get().toString());
            System.out.println(f2.get().toString());
            System.out.println(f3.get().toString());
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }finally {
            threadPool.shutdown();
        }
    }
}

class MyCallable implements Callable{
    private String name;

    public MyCallable(String name) {
        this.name = name;
    }

    @Override
    public Object call() throws Exception {
        return name + "返回了东西...";
    }
}
