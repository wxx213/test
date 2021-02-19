package main;

import basic.RedisClusterTest;
import basic.RedisTest;

public class Application {
    public static void main(String[] args) {
        RedisTest.startTest(args);
        RedisClusterTest.testCluster();
    }
}
