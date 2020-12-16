package com.demo.spi.impl;

import com.demo.spi.service.OrderService;

public class CustomerOrderServiceImpl implements OrderService {

    public int getOrderCountById(int id) {
        System.out.println("cutomer order count is 10");
        return 10;
    }

}