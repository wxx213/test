package com.demo.spi.impl;

import com.demo.spi.service.OrderService;

public class AgencyOrderServiceImpl implements OrderService {

    public int getOrderCountById(int id) {
        System.out.println("agency order count is 20");
        return 20;
    }

}