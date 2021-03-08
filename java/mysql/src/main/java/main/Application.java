package main;

import basic.JdbcTest;
import mybatis.MybatisTest;

public class Application {
    public static void main(String[] args) {
        // JdbcTest.test(args);
        MybatisTest.startMybatisTest(args);
    }
}
