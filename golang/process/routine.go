package main

import (
	"fmt"
	"sync"
)

var wg sync.WaitGroup
var myCh chan int
var myCh2 chan int

func routine1() {
	fmt.Println("runing routine1")
	myCh <- 0
	myCh <- 1
	myCh <- 2
	// close channel for traverse
	close(myCh)
	myCh2 <- 3
	wg.Done()
}

func routine2() {
	fmt.Println("runing routine2")
	select {
		case data := <-myCh:
			fmt.Println("received channel data:", data)
			for {
				if v,ok := <-myCh; ok {
					fmt.Println(v)
					fmt.Println(ok)
				} else {
					break
				}
			}
		case data2 := <-myCh2:
			fmt.Println("received channel2 data:", data2)
	}

	select {
		case data := <-myCh:
			fmt.Println("received channel data:", data)
		case data2 := <-myCh2:
			fmt.Println("received channel2 data:", data2)
	}

	wg.Done()
}

func testRoutine() {
	myCh = make(chan int, 3)
	myCh2 = make(chan int, 3)
	go routine1()
	go routine2()
	wg.Add(2)
	wg.Wait()
}

