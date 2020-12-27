package com.demo.spi.service;

import org.apache.dubbo.common.extension.SPI;

// only dubbo need this annotation
@SPI
public interface OrderService {
    int getOrderCountById(int id);
}