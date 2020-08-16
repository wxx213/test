package main

import (
    "net/http"
    _"net/http/pprof"
	"time"
	"runtime/pprof"
	"fmt"
	"os"
)

func consumeMemory() {
	a := []int {1,2,3,4,5}
    for {
        a = append(a, 10)
        time.Sleep(time.Duration(1)*time.Microsecond)
    }
}

func consumeCPU() {
	i := 0

	for {
		i++
	}
}

func consumeCPUShortly() {
	i := uint64(0)
	for {
		i++
		if i == 100000000000 {
			break
		}
	}
}
// access pprof web page by http://${hostip}:6060/debug/pprof/
//
// flame graph:
//   go tool pprof -http 192.168.2.101:9090 http://127.0.0.1:8089/debug/pprof/profile
// then view the flame graph by: http://192.168.2.101:9090
// http://127.0.0.1:8089/debug/pprof/profile is the pprof address
//
// heap:
//   go tool pprof -alloc_space http://192.168.2.101:6060/debug/pprof/heap
func testHttpPprof() {
	go func() {
		http.ListenAndServe(":6060", nil)
	}()

	// go consumeMemory()
	// go consumeCPU()

	for {
		time.Sleep(time.Duration(100)*time.Second)
	}
}

func testRuntimePprof() {
	f, err := os.OpenFile("./cpu.pprof", os.O_RDWR|os.O_CREATE, 0644)
    if err != nil {
        fmt.Println(err)
    }
    defer f.Close()

    pprof.StartCPUProfile(f)
    defer pprof.StopCPUProfile()

	consumeCPUShortly()
}
