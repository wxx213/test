package main

import (
	"fmt"
	"flag"
)

var test string
func init() {
	flag.StringVar(&test, "t", "r", "test process to run")
}

func main() {
	flag.Parse()
	fmt.Println("starting test process")
	if test == "r" {
		testRoutine()
	} else if test == "p" {
		testProcess()
	} else {
		fmt.Println("nothing to do")
	}
}
