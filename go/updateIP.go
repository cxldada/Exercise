package main

import (
	"fmt"
	"github.com/aliyun/alibaba-cloud-sdk-go/services/alidns"
	"io/ioutil"
	"net/http"
	"time"
)

var lastIP string

func main() {
	client, err := alidns.NewClientWithAccessKey("cn-hangzhou",
		"1",
		"1")

	if err != nil {
		fmt.Println(err.Error())
	}

	d := time.Duration(time.Second * 300)
	t := time.NewTicker(d)

	for {
		newIP := getExternalIP()
		if newIP == lastIP {
			fmt.Println("like ip")
			continue
		}

		lastIP = newIP
		records := getDomainRecords(client)

		updateDomainRecord(client, records)

		<-t.C
	}
}

func getDomainRecords(client *alidns.Client) []alidns.Record {
	request := alidns.CreateDescribeDomainRecordsRequest()
	request.Scheme = "https"

	request.DomainName = "cxldada.cn"
	request.Lang = "en"

	response, err := client.DescribeDomainRecords(request)
	if err != nil {
		fmt.Println(err.Error())
	}

	var records []alidns.Record
	for _, value := range response.DomainRecords.Record {
		if value.Type == "A" {
			records = append(records, value)
		}
	}

	return records
}

func getExternalIP() string {
	resp, err := http.Get("https://myexternalip.com/raw")
	if err != nil {
		fmt.Println("get external ip err=", err)
		return ""
	}
	defer resp.Body.Close()
	content, _ := ioutil.ReadAll(resp.Body)
	return string(content)
}

func updateDomainRecord(client *alidns.Client, records []alidns.Record) {
	for i := 0; i < len(records); i++ {
		record := records[i]

		request := alidns.CreateUpdateDomainRecordRequest()
		request.Scheme = "https"

		request.RecordId = record.RecordId
		request.RR = record.RR
		request.Value = lastIP
		request.Type = record.Type

		response, err := client.UpdateDomainRecord(request)
		if err != nil {
			fmt.Printf("response is %#v\n", response)
			continue
		}
	}
}
