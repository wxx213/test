package main

/*
void cprint();
*/
import "C"

import (
	"fmt"
	"os"
	"strings"
)

func printHello() {
	who := "World!"
	if len(os.Args) > 1 {
		who = strings.Join(os.Args[1:], " ")
	}
	fmt.Println("Hello", who)
}

func testC() {
	C.cprint()
}

func main() {
	// printHello()
	// testC()
	// testInterface()
	// testChannel()
}
