package main;

import basic.JdbcTest;
import mybatis.basic.MybatisTest;
import mybatis.generator.Generator;

public class Application {
    public static void main(String[] args) {
        // JdbcTest.test(args);
        // MybatisTest.startMybatisTest(args);
        try {
            new Generator().testGenerator(args);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
