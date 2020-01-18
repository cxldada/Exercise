package main

import (
	"fmt"
	"github.com/aliyun/alibaba-cloud-sdk-go/services/alidns"
	"io/ioutil"
	"net/http"
)

func main() {
	client, err := alidns.NewClientWithAccessKey("cn-hangzhou",
		"LTAI4FxhuGfCTegzxwUTiVuN",
		"lLetneSTgffl5OE5Q1rtdo7wf7EBon")

	if err != nil {
		fmt.Println(err.Error())
	}

	records := getDomainRecords(client)
	fmt.Println(records)

	updateDomainRecord(client, records)

	records = getDomainRecords(client)
	fmt.Println(records)
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
	var publicIP = getExternalIP()

	for i := 0; i < len(records); i++ {
		record := records[i]

		request := alidns.CreateUpdateDomainRecordRequest()
		request.Scheme = "https"

		request.RecordId = record.RecordId
		request.RR = record.RR
		request.Value = publicIP
		request.Type = record.Type

		response, err := client.UpdateDomainRecord(request)
		if err != nil {
			fmt.Printf("response is %#v\n", response)
			continue
		}
	}
}
