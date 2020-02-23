package main

import (
	"fmt"
	"time"
	"sync"
)

var myCh chan int
var myCh2 chan int
var wg sync.WaitGroup

func routine() {
	select {
		case x := <-myCh:
			fmt.Println("myCh received: ", x)
		case myCh2 <- 6:
		case <-time.After(3*time.Second):
			fmt.Println("sub routine received nothing in 3s")
	}
	wg.Done()
}

func testChannel() {
	myCh = make(chan int, 3)
	myCh2 = make(chan int, 3)
	myCh <- 5
	wg.Add(1)
	go routine()
	select {
		case x := <-myCh2:
			fmt.Println("myCh2 received: ", x)
		case <-time.After(3*time.Second):
			fmt.Println("main routine received nothing in 3s")
	}
	wg.Wait()
}
