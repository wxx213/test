grpc demo for golang, reference: https://www.grpc.io/docs/languages/go/quickstart/

# install protoc3

reference: https://www.grpc.io/docs/protoc-installation/

```shell
PB_REL="https://github.com/protocolbuffers/protobuf/releases"
curl -LO $PB_REL/download/v3.15.8/protoc-3.15.8-linux-x86_64.zip
unzip protoc-3.15.8-linux-x86_64.zip -d $HOME/.local
export PATH="$PATH:$HOME/.local/bin"
# check the version
protoc --version
```

# install go plugins

```shell
go install google.golang.org/protobuf/cmd/protoc-gen-go@v1.26
go install google.golang.org/grpc/cmd/protoc-gen-go-grpc@v1.1
export PATH="$PATH:$(go env GOPATH)/bin"
```

# generate the codes

```shell
protoc -I . --go_out=plugins=grpc:. helloworld.proto
```

