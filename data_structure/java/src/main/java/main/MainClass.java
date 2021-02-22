package main;

import base.TwoSum;

import java.io.IOException;

public class MainClass {


    public static void main(String[] args) {
        try {
            TwoSum.testTwoSum(args);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}