package main

import (
	"fmt"
	"os"
)

func main1() {
	fmt.Println("Hello world!")

	beyondHello()
}

func beyondHello() {
	var x int
	x = 3
	y := 4
	sum, prod := learnMultiple(x, y)
	fmt.Println("sum:", sum, "prod:", prod)
	learnTypes()
}

func learnMultiple(x, y int) (sum, prod int) {
	return x + y, x * y
}

func learnTypes() {
	str := "read book"
	s2 := `haha
	xixi`
	g := '🥱'
	f := 3.14159 // float64
	c := 3 + 4i
	var u uint = 7
	var pi float32 = 22. / 7
	n := byte('\n')
	var a4 [4]int // 4个int变量的数组，初始化为0
	a3 := [...]int{3, 1, 5}
	s3 := []int{4, 5, 9} // slice (dynamic array)(like vector in c++)
	s4 := make([]int, 4) // stack slice
	var d2 [][]float64
	bs := []byte("a slice")

	s := []int{1, 2, 3}
	s = append(s, 4, 5, 6)
	fmt.Println(s)
	s = append(s, []int{7, 8, 9}...)
	fmt.Println(s)

	p, q := learnMemory()
	fmt.Println(*p, *q)

	m := map[string]int{"three": 3, "four": 4}
	m["one"] = 1

	_, _, _, _, _, _, _, _, _, _ = str, s2, g, f, u, pi, n, a3, s4, bs

	file, _ := os.Create("output.txt")
	fmt.Fprint(file, "input to file.")
	file.Close()

	fmt.Println(s, c, a4, s3, d2, m)

	learnFlowControl()
}

func learnNamedReturns(x, y int) (z int) {
	z = x * y
	return
}

// go有gc机制，但是有空指针异常
func learnMemory() (p, q *int) {
	p = new(int)
	s := make([]int, 20)
	s[3] = 7
	r := -2
	return &s[3], &r
}

func expensiveComputation() int {
	return 1e6
}

func learnFlowControl() {
	if true {
		fmt.Println("real print this words.")
	}

	if false {

	} else {

	}

	x := 1
	// 隐含break
	switch x {
	case 0:
	case 1:
	case 2:
	}

	for x := 0; x < 3; x++ {
		fmt.Println("foreach", x)
	}
	// 作用域
	fmt.Println("x ==== ", x)

	for {
		break
	}

	for key, value := range map[string]int{"one": 1, "two": 2, "three": 3} {
		fmt.Printf("index: %s, value: %d\n", key, value)
	}

	for _, name := range []string{"bob", "bill", "joe"} {
		fmt.Printf("you are %s\n", name)
	}

	if y := expensiveComputation(); y > x {
		x = y
	}

	xBig := func() bool {
		return x > 100
	}

	fmt.Println("xBig:", xBig())
	x /= 1e5
	fmt.Println("xBig", xBig())

	fmt.Println("+: ", func(a, b int) int {
		return (a + b) * 2
	}(10, 2))

	goto love
love:
	learnFunctionFactory()
	learnDefer()
	learnInterfaces()
}

func learnFunctionFactory() {
	fmt.Println(sentenceFactory("原谅")("当然选择", "她"))

	d := sentenceFactory("原谅")
	fmt.Println(d("当然选择", "她"))
	fmt.Println(d("怎么可以", "她"))
}

func sentenceFactory(mystring string) func(before, after string) string {
	return func(before, after string) string {
		return fmt.Sprintf("%s %s %s", before, mystring, after) // new string
	}
}

func learnDefer() (ok bool) {
	defer fmt.Println("后进先出")
	defer fmt.Println("e")

	return true
}

type Stringer interface {
	String() string
}

type pair struct {
	x, y int
}

func (p pair) String() string {
	return fmt.Sprintf(" (%d,%d) ", p.x, p.y)
}

func learnInterfaces() {
	p := pair{3, 4}
	fmt.Println(p.String())
	var i Stringer
	i = p
	fmt.Println(i.String())

	fmt.Println(p)
	fmt.Println(i)

	// learnVariadicParams("great", "learning", "here!")
}
