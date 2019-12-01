package main

import (
    "errors"
    "fmt"
    "log"
    "net"
    "net/http"
    "net/rpc"
    "os"
)

// 算数运算结构体
type Arith struct {
}

// 乘法运算方法
func (this *Arith) Multiply(req ArithRequest, res *ArithResponse) error {
    res.Pro = req.A * req.B
    return nil
}

// 除法运算方法
func (this *Arith) Divide(req ArithRequest, res *ArithResponse) error {
    if req.B == 0 {
        return errors.New("divide by zero")
    }
    res.Quo = req.A / req.B
    res.Rem = req.A % req.B
    return nil
}

func startRPCServer() {
    rpc.Register(new(Arith)) // 注册rpc服务
    rpc.HandleHTTP()         // 采用http协议作为rpc载体

    lis, err := net.Listen("tcp", "127.0.0.1:8095")
    if err != nil {
        log.Fatalln("fatal error: ", err)
    }

    fmt.Fprintf(os.Stdout, "%s", "start connection")

    http.Serve(lis, nil)
}

func startUnixRPCServer() {
	fmt.Println("starting run startUnixRPCServer")
	os.Mkdir(unix_rpc_dir, 0777)
	rpcs := rpc.NewServer()
	rpcs.Register(new(Arith))
	os.Remove(unix_rpc_addr)
	lis, err := net.Listen("unix", unix_rpc_addr)
	if err != nil {
		fmt.Println("startUnixRPCServer net.Listen error:", err)
	}
	conn, err := lis.Accept()
	if err == nil {
		rpcs.ServeConn(conn)
		conn.Close()
	} else {
		fmt.Println("startUnixRPCServer lis.Accept error:", err)
	}
}
