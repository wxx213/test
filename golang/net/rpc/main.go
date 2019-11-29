package main

import (
	"flag"
	"fmt"
	"os"
	"os/exec"
	"errors"
	"time"
	"syscall"
)

var mode string

func init() {
	flag.StringVar(&mode, "m", "a", "rpc mode process to run")
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

func startRPCServerProcess() (*exec.Cmd, error) {
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

func stopRPCServerProcess( cmd *exec.Cmd) {
	proc, err := os.FindProcess(cmd.Process.Pid)
	if err != nil {
		fmt.Println("os.FindProcess error: %v", err)
		return
	}
	err = proc.Signal(syscall.SIGINT)
	if err != nil {
		fmt.Println("pro.Signal error: %v", err)
		return
	}
}

func main() {
	flag.Parse()
	if mode == "a" {
		cmd, err := startRPCServerProcess()
		if err != nil {
			fmt.Println("startRPCServerProcess error: %v", err)
			return
		}
		time.Sleep(1 * time.Second)
		startRPCClient()
		stopRPCServerProcess(cmd)
	} else if mode == "s" {
		startRPCServer()
	} else if mode == "c" {
		startRPCClient()
	} else {
		fmt.Println("nothing to do")
	}
}
