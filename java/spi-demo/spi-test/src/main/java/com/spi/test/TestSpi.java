package com.spi.test;

import java.util.ServiceLoader;

import com.demo.spi.service.OrderService;
import org.apache.dubbo.common.extension.ExtensionLoader;
import org.apache.dubbo.common.URL;
import com.demo.spi.service.FruitGranter;

public class TestSpi {
    public static void testJavaSPI() {
        System.out.println("Java Spi Test");
        ServiceLoader<OrderService> orderServices = ServiceLoader.load(OrderService.class);
        for (OrderService orderService : orderServices) {
            orderService.getOrderCountById(1);
        }
    }
    public static void testDubboSPI() {
        System.out.println("Dubbo Spi Test");
        ExtensionLoader<OrderService> extensionLoader = ExtensionLoader.getExtensionLoader(OrderService.class);
        OrderService agencyService = extensionLoader.getExtension("agencyOrder");
        agencyService.getOrderCountById(1);
        OrderService customerService = extensionLoader.getExtension("customerOrder");
        customerService.getOrderCountById(1);
    }

    public static void testDubboAdaptiveSPI() {
        System.out.println("Dubbo Adaptive Spi Test");
        // 首先创建一个模拟用的URL对象
        // URL url = URL.valueOf("dubbo://192.168.0.101:20880?fruit.granter=apple");
        URL url = URL.valueOf("dubbo://192.168.0.101:20880?selected_granter=banana");
        // 通过ExtensionLoader获取一个FruitGranter对象
        FruitGranter granter = ExtensionLoader.getExtensionLoader(FruitGranter.class).getAdaptiveExtension();
        // 使用该FruitGranter调用其"自适应标注的"方法，获取调用结果
        String result = granter.watering(url);
        System.out.println(result);
    }

    public static void main(String[] args) {
        testJavaSPI();
        testDubboSPI();
        testDubboAdaptiveSPI();
    }

}
