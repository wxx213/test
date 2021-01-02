package com.demo.spi.impl;

import com.demo.spi.service.FruitGranter;
import org.apache.dubbo.common.URL;

// 苹果种植者
public class AppleGranter implements FruitGranter {

    @Override
    public FruitGranter grant() {
        return new AppleGranter();
    }

    @Override
    public String watering(URL url) {
        System.out.println("watering apple");
        return "watering finished";
    }
}
