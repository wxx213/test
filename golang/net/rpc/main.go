package main

import (
	"flag"
	"fmt"
	"os"
	"os/exec"
	"errors"
	"time"
)

var mode string

func init() {
	flag.StringVar(&mode, "m", "c", "rpc mode process to run")
}

// 算数运算请求结构体
type ArithRequest struct {
	A int
	B int
}

// 算数运算响应结构体
type ArithResponse struct {
	Pro int // 乘积
	Quo int // 商
	Rem int // 余数
}

func execRPCServer() (*exec.Cmd, error) {
	cmd := exec.Command(os.Args[0], "-m", "s")
	if cmd == nil {
		return nil, errors.New("exec.Command error")
	}
	err := cmd.Start()
	if err != nil {
		fmt.Println(err)
		 return nil, err
	}
	// fmt.Println("the path is %s", os.Args[0])
	return cmd, nil
}

func main() {
	flag.Parse()
	if mode == "c" {
		execRPCServer()
		time.Sleep(1 * time.Second)
		startRPCClient()
	} else if mode == "s" {
		startRPCServer()
	} else {
		fmt.Println("nothing to do")
	}
}
