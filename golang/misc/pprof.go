package main

import (
    "net/http"
    _"net/http/pprof"
	"time"
	"runtime/pprof"
	"fmt"
	"os"
)

// access pprof web page by http://${hostip}:6060/debug/pprof/
func testHttpPprof() {
	go func() {
		http.ListenAndServe(":6060", nil)
	}()

	a := []int {1,2,3,4,5}
	for {
		a = append(a, 10)
		time.Sleep(time.Duration(10)*time.Microsecond)
	}
}

func testRuntimePprof() {
	f, err := os.OpenFile("./cpu.prof", os.O_RDWR|os.O_CREATE, 0644)
    if err != nil {
        fmt.Println(err)
    }
    defer f.Close()
    pprof.StartCPUProfile(f)
    defer pprof.StopCPUProfile()

	// 注意，有时候 defer f.Close()， defer pprof.StopCPUProfile() 会执行不到，
	// 这时候我们就会看到 prof 文件是空的， 我们需要在自己代码退出的地方，增加上下面两行，
	// 确保写文件内容了。
	pprof.StopCPUProfile()
	f.Close()
}
