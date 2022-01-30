package server

import (
	"bytes"
	"context"
	"google.golang.org/grpc"
	"com.example.grpc/generated/helloword"
	"log"
	"net"
	"runtime"
	"strconv"
)

const (
	port = ":50051"
)

// server is used to implement helloworld.GreeterServer.
type server struct {
	helloword.UnimplementedGreeterServer
}

// SayHello implements helloworld.GreeterServer
func (s *server) SayHello(ctx context.Context, in *helloword.HelloRequest) (*helloword.HelloReply, error) {
	log.Printf("grpc server interface goroutine ID is: %d\n", getGID())
	log.Printf("Received: %v", in.GetName())
	return &helloword.HelloReply{Message: "Hello " + in.GetName()}, nil
}

func getGID() uint64 {
	b := make([]byte, 64)
	b = b[:runtime.Stack(b, false)]
	b = bytes.TrimPrefix(b, []byte("goroutine "))
	b = b[:bytes.IndexByte(b, ' ')]
	n, _ := strconv.ParseUint(string(b), 10, 64)
	return n
}

func testBasic() {
	log.Printf("grpc server goroutine ID is: %d\n", getGID())

	lis, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}
	s := grpc.NewServer()
	helloword.RegisterGreeterServer(s, &server{})
	if err := s.Serve(lis); err != nil {
		log.Fatalf("failed to serve: %v", err)
	}
}
func StartServer() {
	testBasic()
}