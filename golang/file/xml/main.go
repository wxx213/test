package main

import (
	"encoding/xml"
	"fmt"
	"io/ioutil"
)

type Peoples struct {
	XMLName xml.Name `xml:"peoples"`
	Version string `xml:"version,attr"`
	Peos []People `xml:"people"`


}

type People struct {
	XMLName xml.Name `xml:"people"`
	ID    	int 		 `xml:"id,attr"`//这里的attr 代表的是什么意思 没有attr 取不出所需要的ID号
	Name  	string	 	 `xml:"name"`
	Address string		 `xml:"address"`
	sex     string        `xml:"sex"`
}

func readXmlFile() {
	peo := new(Peoples)
	b,err  := ioutil.ReadFile("./A.xml")
	if err == nil {
		fmt.Println(string(b))
	} else {
		fmt.Println(err)
		return
	}

	err = xml.Unmarshal(b,peo)//使用Ummarshal 对b内容进行解析
	if err == nil {
		fmt.Println(peo)
	} else {
		fmt.Println(err)
	}
}

func writeXmlFile() {
	b := Peoples{Version:"0.9"}
	var text = `<Peoples></Peoples>`
	peo := People{ID:125,Name:"LHH",Address:"ccsu",sex:"male"}
	b.Peos = append(b.Peos,peo)
	xml.Unmarshal([]byte(text),b)

	wrb ,_:= xml.MarshalIndent(b,"","	")
	wrb = append([]byte(xml.Header),wrb...)

	ioutil.WriteFile("./B.xml",wrb,0666)
}

func main() {
	readXmlFile()
	writeXmlFile()
}

