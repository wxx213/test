package com.demo.spi.impl;

import com.demo.spi.service.PeopleWater;
import org.apache.dubbo.common.URL;

// 苹果种植者
public class TomWater implements PeopleWater {

    @Override
    public PeopleWater water() {
        return new TomWater();
    }

    @Override
    public String printWater(URL url) {
        System.out.println("tom is in water");
        return "tom finished";
    }
}
