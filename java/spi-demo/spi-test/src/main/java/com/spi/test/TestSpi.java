package com.spi.test;

import java.util.ServiceLoader;

import com.demo.spi.service.OrderService;
import org.apache.dubbo.common.extension.ExtensionLoader;

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
    public static void main(String[] args) {
        testJavaSPI();
        testDubboSPI();
    }

}
