package main

import "fmt"

func main1() {
	/*
		var a int = 65
		b := string(a)
		fmt.Println(b)
	*/

label:
	for i := 0; i < 10; i++ {
		for {
			fmt.Println(i)
			continue label
		}
	}
}
