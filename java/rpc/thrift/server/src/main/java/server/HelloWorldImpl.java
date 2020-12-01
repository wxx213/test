package server;

import common.HelloWorldService;

public class HelloWorldImpl implements HelloWorldService.Iface {
    public  HelloWorldImpl(){
    }
    @Override
    public  String sayHello(String username){
        return "hi " + username + " " + "welcome to thrift world";
    }
}
