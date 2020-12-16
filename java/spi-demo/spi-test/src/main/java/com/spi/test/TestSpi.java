package com.spi.test;

import java.util.ServiceLoader;

import com.demo.spi.service.OrderService;

public class TestSpi {
    public static void main(String[] args) {
        ServiceLoader<OrderService> orderServices = ServiceLoader.load(OrderService.class);
        for (OrderService orderService : orderServices) {
            orderService.getOrderCountById(1);
        }
    }

}
