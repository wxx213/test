package com.atguigu.spring.helloworld;

import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Main {

    public static void main(String[] args) {

//		HelloWorld helloWorld = new HelloWorld();
//		helloWorld.setUser("Tom");
//		helloWorld.hello();

        //1. 创建 Spring 的 IOC 容器
        ClassPathXmlApplicationContext ctx = new ClassPathXmlApplicationContext("beans.xml");

        //2. 从 IOC 容器中获取 bean 的实例
        HelloWorld  helloWorld = (HelloWorld) ctx.getBean("helloWorld");
        //是通过bean.xml里面定义的id来定位获取哪个bean实例的。@lcb
        System.out.println("bean实例的样子是"+ ctx);

        //3. 使用 bean
        //有了实例，就可以通过实例来调用实例的方法，那么实例有哪些方法，文档中是要写清楚的。方法可以直接用。
        helloWorld.setUser("chao");
        helloWorld.hello();//hello这个方法，要做什么事情，也是要在方法里面写清楚的。比如这里我输入了setUser的"chao"参数，那么返回的是hello chaobin

    }

}

