package com.demo.spi.service;

import org.apache.dubbo.common.extension.SPI;
import org.apache.dubbo.common.URL;
import org.apache.dubbo.common.extension.Adaptive;

@SPI("jack")
public interface PeopleWater {
    PeopleWater water();

    @Adaptive("selected_water")
    String printWater(URL url);
}
