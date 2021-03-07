package main;

import base.KafkaConsumerTest;
import base.KafkaProducerTest;

public class Application {
    public static void main(String[] args) {
        if (args.length > 0) {
            if ("provider".equals(args[0])) {
                KafkaProducerTest.startProvider(args);
            } else if ("consumer".equals(args[0])) {
                KafkaConsumerTest.startConsumer(args);
            }
        }
    }
}
