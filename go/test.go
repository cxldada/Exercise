package main

import (
	"fmt"
	"time"
)

func main1() {
	d := time.Duration(time.Second * 3)
	t := time.NewTicker(d)

	defer t.Stop()

	for {
		<-t.C
		fmt.Println("...")
	}
}
