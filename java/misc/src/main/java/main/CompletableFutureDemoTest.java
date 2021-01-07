package main;

import java.util.concurrent.*;
import java.util.stream.IntStream;

public class CompletableFutureDemoTest {

    class Shop {
        /**异步非阻塞式调用*/
        @SuppressWarnings("AlibabaAvoidManuallyCreateThread")
        public Future<Double> getPriceAsync(String product){
            CompletableFuture<Double> futurePrice = new CompletableFuture<>();
            new Thread(()->{
                try{
                    double price = calcPrice(product);
                    //如果价格计算正常结束，完成 Future 操作并设置商品价格
                    futurePrice.complete(price);
                }catch (Exception e){
                    //否则就抛出导致失败的异常，完成这次 Future 操作
                    futurePrice.completeExceptionally(e);
                }
            }).start();
            return futurePrice;
        }

        private double calcPrice(String product) {
            delay();
            // 执行一些其他耗时的任务
            return IntStream.rangeClosed(1,10000000).asDoubleStream().sum();
        }

        /**同步阻塞式调用*/
        public double getPrice(String product) {
            return calcPrice(product);
        }
        /**模拟调用1秒钟*/
        private void delay() {
            try {
                Thread.sleep(1000L);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
    public void executor() {
        /*java8以前异步执行*/
        ExecutorService executor = Executors.newCachedThreadPool();
        Future<Double> future = executor.submit(new Callable<Double>() {
            @Override
            public Double call() throws Exception {
                return doSomeLongComputation();
            }
        });
        doSomethingElse();
        try {
            Double res = future.get(1, TimeUnit.SECONDS);
            System.out.println(res);
        } catch (InterruptedException | ExecutionException | TimeoutException e) {
            e.printStackTrace();
            System.out.println("ExecutionException:计算抛出一个异常 | InterruptedException:当前线程在等待过程中被中断 | TimeoutException:在Future对象完成之前超过已过期");
        }
    }

    private void doSomethingElse() {
        System.out.println("Do Something Else!!!!");
    }

    private Double doSomeLongComputation() {
        return IntStream.rangeClosed(1, 10000).asDoubleStream().sum();
    }

    public void async() {
        /*
         *
         * 这段代码中，客户向商店查询了某种商品的价格。由于商店提供了异步API，该次
         * 调用立刻返回了一个 Future 对象，通过该对象客户可以在将来的某个时刻取得商品的价格。这
         * 种方式下，客户在进行商品价格查询的同时，还能执行一些其他的任务，比如查询其他家商店中
         * 商品的价格，不会呆呆地阻塞在那里等待第一家商店返回请求的结果。最后，如果所有有意义的
         * 工作都已经完成，客户所有要执行的工作都依赖于商品价格时，再调用 Future 的 get 方法。执行
         * 了这个操作后，客户要么获得 Future 中封装的值（如果异步任务已经完成），要么发生阻塞，直
         * 到该异步任务完成，期望的值能够访问.
         * */
        Shop shop = new Shop();
        long start = System.nanoTime();
        Future<Double> futurePrice = shop.getPriceAsync("my produce");
        long invocationTime = ((System.nanoTime() - start) / 1_000_000);
        System.out.println("invocation time:" + invocationTime + "msecs.");
        // 执行更多任务
        doSomethingElse();
        // 在计算商品价格的同时
        try {
            double price = futurePrice.get();
            System.out.printf("Price is %.2f%n", price);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        long retrievalTime = ((System.nanoTime() - start) / 1_000_000);
        System.out.println("Price returned after " + retrievalTime + " msecs");
        /*Result:
         * invocation time:39msecs.
         * Do Something Else!!!!
         * Price is 50000005000000.00
         * Price returned after 1126 msecs
         */
    }
    public void TestCompletableFuture() {
        executor();
        async();
    }
}