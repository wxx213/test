package main

import (
    "fmt"
    "net/http"
)

func main()  {
    //监听协议
    http.HandleFunc("/",HelloWorldHandler)
    http.HandleFunc("/user/login",UserLoginHandler)
    //监听服务
    err := http.ListenAndServe("localhost:8880",nil)

    if err != nil {
        fmt.Println("服务器错误")
    }

}

func HelloWorldHandler(w http.ResponseWriter,r *http.Request)  {
    fmt.Println("r.Method = ", r.Method)
    fmt.Println("r.URL = ", r.URL)
    fmt.Println("r.Header = ", r.Header)
    fmt.Println("r.Body = ", r.Body)
    fmt.Fprintf(w,"Hello World!\n")
}

func UserLoginHandler(response http.ResponseWriter,request *http.Request)  {
    fmt.Println("Handler Hello")
	response.Header().Set("Message", "None")
	response.WriteHeader(http.StatusOK)
	response.Write([]byte("Login Success\n"))
}
