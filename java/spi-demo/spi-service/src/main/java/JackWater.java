package com.demo.spi.impl;

import com.demo.spi.service.PeopleWater;
import org.apache.dubbo.common.URL;

// 苹果种植者
public class JackWater implements PeopleWater {

    @Override
    public PeopleWater water() {
        return new JackWater();
    }

    @Override
    public String printWater(URL url) {
        System.out.println("jack is in water");
        return "jack finished";
    }
}
