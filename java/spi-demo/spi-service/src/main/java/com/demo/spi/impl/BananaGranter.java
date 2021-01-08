package com.demo.spi.impl;

import com.demo.spi.service.FruitGranter;
import org.apache.dubbo.common.URL;

// 香蕉种植者
public class BananaGranter implements FruitGranter {

    @Override
    public FruitGranter grant() {
        return new BananaGranter();
    }

    @Override
    public String watering(URL url) {
        System.out.println("watering banana");
        return "watering success";
    }
}
