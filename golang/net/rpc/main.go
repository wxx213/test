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

const unix_rpc_addr = "/tmp/golang/rpc"
const unix_rpc_dir = "/tmp/golang"
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

func startRPCServerProcess(arg string) (*exec.Cmd, error) {
	cmd := exec.Command(os.Args[0], "-m", arg)
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
	var cmd *exec.Cmd
	var err error

	if mode == "a" {
		cmd, err = startRPCServerProcess("s")
		if err != nil {
			fmt.Println("startRPCServerProcess http error: %v", err)
			return
		}
		time.Sleep(1 * time.Second)
		startRPCClient()
		stopRPCServerProcess(cmd)
	} else if mode == "s" {
		startRPCServer()
	} else if mode == "c" {
		startRPCClient()
	} else if mode == "au" {
		cmd, err = startRPCServerProcess("su")
		if err != nil {
			fmt.Println("startRPCServerProcess unix error: %v", err)
			return
		}
		time.Sleep(1 * time.Second)
		startUnixRPCClient()
		stopRPCServerProcess(cmd)
	} else if mode == "su" {
		startUnixRPCServer()
	} else if mode == "cu" {
		startUnixRPCClient()
	} else {
		fmt.Println("nothing to do")
	}
}
