package main

import (
    "fmt"
    "log"
    "net/rpc"
)

func startRPCClient() {
    conn, err := rpc.DialHTTP("tcp", "127.0.0.1:8095")
    if err != nil {
        log.Fatalln("dailing error: ", err)
    }

    req := ArithRequest{9, 2}
    var res ArithResponse

    err = conn.Call("Arith.Multiply", req, &res) // 乘法运算
    if err != nil {
        log.Fatalln("arith error: ", err)
    }
    fmt.Printf("%d * %d = %d\n", req.A, req.B, res.Pro)

    err = conn.Call("Arith.Divide", req, &res)
    if err != nil {
        log.Fatalln("arith error: ", err)
    }
    fmt.Printf("%d / %d, quo is %d, rem is %d\n", req.A, req.B, res.Quo, res.Rem)
}

func startUnixRPCClient() {
	req := ArithRequest{9, 2}
	var res ArithResponse

	conn, err := rpc.Dial("unix", unix_rpc_addr)
	if err != nil {
		fmt.Println("startUnixRPCClient rpc.Dial error:", err)
		return
	}
	err = conn.Call("Arith.Multiply", req, &res)
	if err != nil {
		fmt.Println("startUnixRPCClient conn.Call error:", err)
		return
	}
	fmt.Printf("%d * %d = %d\n", req.A, req.B, res.Pro)

	err = conn.Call("Arith.Divide", req, &res)
	if err != nil {
		fmt.Println("startUnixRPCClient conn.Call error 2:", err)
		return
	}
	fmt.Printf("%d / %d, quo is %d, rem is %d\n", req.A, req.B, res.Quo, res.Rem)
}
