package career_interview

import (
	"sort"
	"testing"
)

func TestM1NAddtion(t *testing.T) {
	combinatrics := findM1NAdditions(10, 20)
	/*
			   1 9
			   2 8
			   3 7
			   4 6
			   1 2 7
			   1 2 3 4
		       1 3 6
			   1 4 5
			   2 3 5
	*/
	if len(combinatrics) != 9 {
		t.Errorf("%d is not equal with combination(9) for 10 in 20", len(combinatrics))
	}
	if !slice_contain(combinatrics, []int{1, 2, 3, 4}) {
		t.Errorf("combiner result should contain 1,2,3,4")
	}
}

//http://stackoverflow.com/questions/10485743/contains-method-for-a-slice
//https://groups.google.com/forum/#!topic/golang-nuts/yQk_g7AjcU8
//todo improve
func slice_contain(c [][]int, e []int) bool {
	var rv = false
	for _, cc := range c {
		sort.Ints(cc)
		if slice_equal(cc, e) {
			rv = true
			break
		}
	}
	return rv
}

func slice_equal(c []int, e []int) bool {
	if len(c) != len(e) {
		return false
	}
	for i := 0; i < len(c); i++ {
		if c[i] != e[i] {
			return false
		}
	}
	return true
}
