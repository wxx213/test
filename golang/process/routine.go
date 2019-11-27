package main

import (
        "fmt"
        "sync"
)

var wg sync.WaitGroup

func routine1() {
        fmt.Println("runing routine1")
        wg.Done()
}

func routine2() {
        fmt.Println("runing routine2")
        wg.Done()
}

func testRoutine() {
        go routine1()
        go routine2()
        wg.Add(2)
        wg.Wait()
}

