package com.demo.spi.service;

import org.apache.dubbo.common.extension.SPI;
import org.apache.dubbo.common.URL;
import org.apache.dubbo.common.extension.Adaptive;

@SPI("apple")
public interface FruitGranter {
    FruitGranter grant();

    @Adaptive("selected_granter")
    String watering(URL url);
}
