package main

import (
	"fmt"
	"time"
)

func testMapConcurrence() {
	c := make(map[string]int)
	// 开一个goroutine写map
    go func() {
        for j := 0; j < 1000000; j++ {
            c[fmt.Sprintf("%d", j)] = j
        }
    }()

	go func() {
		for { fmt.Println("Hello")}
	}()

	// 开一个goroutine读map
    go func() {
        for j := 0; j < 1000000; j++ {
            fmt.Println(c[fmt.Sprintf("%d",j)])
        }
    }()

    time.Sleep(time.Second*20)
}

