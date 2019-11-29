package main

import (
	"fmt"
	"sync"
)

var wg sync.WaitGroup
var myCh chan int

func routine1() {
        fmt.Println("runing routine1")
		myCh <- 2
        wg.Done()
}

func routine2() {
        fmt.Println("runing routine2")
		fmt.Println("received channel data:", <-myCh)
        wg.Done()
}

func testRoutine() {
		myCh = make(chan int, 3)
        go routine1()
        go routine2()
        wg.Add(2)
        wg.Wait()
}

