package main
import (
    "os"
    "io"
    "fmt"
    "io/ioutil"
    "bufio"
)

func testFileWrite() {
	name := "testwritefile.txt"
	content := "Hello, wxx.github.io!\n"
	WriteWithIoutil(name,content)
	contents := "Hello, wxx\n"
	//清空一次文件并写入两行contents
	WriteWithFileWrite(name,contents)
	WriteWithIo(name,content)
	//使用bufio包需要将数据先读到buffer中，然后在flash到磁盘中
	WriteWithBufio(name,contents)
	err := os.Remove(name)
	if err != nil {
		fmt.Println(err)
	}
}

//使用ioutil.WriteFile方式写入文件,是将[]byte内容写入文件,如果content字符串中没有换行符的话，默认就不会有换行符
func WriteWithIoutil(name,content string) {
    data :=  []byte(content)
    if ioutil.WriteFile(name,data,0644) == nil {
        fmt.Println("写入文件成功:",content)
	}
}

//使用os.OpenFile()相关函数打开文件对象，并使用文件对象的相关方法进行文件写入操作
//清空一次文件
func WriteWithFileWrite(name,content string){
    fileObj,err := os.OpenFile(name,os.O_RDWR|os.O_CREATE|os.O_TRUNC,0644)
    if err != nil {
        fmt.Println("Failed to open the file",err.Error())
        os.Exit(2)
    }
    defer fileObj.Close()
    if _,err := fileObj.WriteString(content);err == nil {
        fmt.Println("Successful writing to the file with os.OpenFile and *File.WriteString method.",content)
    }
    contents := []byte(content)
    if _,err := fileObj.Write(contents);err == nil {
        fmt.Println("Successful writing to thr file with os.OpenFile and *File.Write method.",content)
    }
}


//使用io.WriteString()函数进行数据的写入
func WriteWithIo(name,content string) {
    fileObj,err := os.OpenFile(name,os.O_RDWR|os.O_CREATE|os.O_APPEND,0644)
    if err != nil {
        fmt.Println("Failed to open the file",err.Error())
        os.Exit(2)
    }
    if  _,err := io.WriteString(fileObj,content);err == nil {
        fmt.Println("Successful appending to the file with os.OpenFile and io.WriteString.",content)
    }
}

//使用bufio包中Writer对象的相关方法进行数据的写入
func WriteWithBufio(name,content string) {
    if fileObj,err := os.OpenFile(name,os.O_RDWR|os.O_CREATE|os.O_APPEND,0644);err == nil {
        defer fileObj.Close()
        writeObj := bufio.NewWriterSize(fileObj,4096)
        //
		if _,err := writeObj.WriteString(content);err == nil {
              fmt.Println("Successful appending buffer and flush to file with bufio's Writer obj WriteString method",content)
		}

        //使用Write方法,需要使用Writer对象的Flush方法将buffer中的数据刷到磁盘
        buf := []byte(content)
        if _,err := writeObj.Write(buf);err == nil {
            fmt.Println("Successful appending to the buffer with os.OpenFile and bufio's Writer obj Write method.",content)
            if  err := writeObj.Flush(); err != nil {panic(err)}
            fmt.Println("Successful flush the buffer data to file ",content)
		}
	}
}
