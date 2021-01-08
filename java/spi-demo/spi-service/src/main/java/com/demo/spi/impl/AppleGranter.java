package com.demo.spi.impl;

import com.demo.spi.service.FruitGranter;
import org.apache.dubbo.common.URL;
import com.demo.spi.service.PeopleWater;

// 苹果种植者
public class AppleGranter implements FruitGranter {

    PeopleWater peopleWater;

    public void setPeopleWater(PeopleWater peopleWater) {
        this.peopleWater = peopleWater;
    }

    @Override
    public FruitGranter grant() {
        return new AppleGranter();
    }

    @Override
    public String watering(URL url) {
        System.out.println("watering apple");
        if (peopleWater != null) {
            peopleWater.printWater(url);
        }
        return "watering finished";
    }
}
