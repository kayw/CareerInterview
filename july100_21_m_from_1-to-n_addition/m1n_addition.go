package career_interview

import (
	"bytes"
	"fmt"
	_ "golang.org/x/blog/blog"
	"strings"
)

func strFltSlice(fs []float64) string {
	var b bytes.Buffer
	for _, f := range fs {
		fmt.Fprintf(&b, "%.6f ", f)
	}
	return b.String()
} //http://play.golang.org/p/-OBvk2VVv0
func findM1NAdditions(combiner, combinee int) [][]int {
	if combiner <= combinee {
		return findM1NAdditions(combiner, combiner-1)
	}
	var visited_combinee = map[int]bool{}
	var combinee_result [][]int
	return findCombinationHelper(combiner, combinee, visited_combinee, combinee_result)
}

func findCombinationHelper(combiner, combinee int, visited_combinee map[int]bool, combinee_result [][]int) [][]int {
	if combiner == 0 {
		var rv []int
		for k, v := range visited_combinee {
			if v {
				//println(k)
				rv = append(rv, k)
			}
		}

		//https: //groups.google.com/forum/#!topic/golang-nuts/oFz4ta4L60M
		//http://play.golang.org/p/sk6JKiN6qQ
		fmt.Println(strings.Trim(fmt.Sprint(rv), "[]"))
		combinee_result = append(combinee_result, rv)
		//http://kitmenke.com/blog/2013/04/14/using-slices-in-golang/
		fmt.Println(combinee_result)
		//println(combinee_result)
		//http://stackoverflow.com/questions/14680255/whats-the-difference-between-fmt-println-and-println-in-go
	}
	if combiner <= 0 || combinee <= 0 {
		return combinee_result
	} /*
		if visited_combinee[combinee] {
			return
		}*/
	visited_combinee[combinee] = true
	combinee_result = findCombinationHelper(combiner-combinee, combinee-1, visited_combinee, combinee_result)
	visited_combinee[combinee] = false
	combinee_result = findCombinationHelper(combiner, combinee-1, visited_combinee, combinee_result)
	return combinee_result
}
