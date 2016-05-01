package career_interview

import (
	"fmt"
	"testing"
)

func TestFourSumBasic(t *testing.T) {
	results := fourSum([]int{1, 4, 2, 7, 3}, 10)
	for _, res := range results {
		for _, num := range res {
			fmt.Printf("%d ", num)
		}
		fmt.Print("\n")
	}
	if len(results) != 1 {
		t.Errorf("%d is not the right length of 3", len(results))
	}
	results = fourSum([]int{1, 1, 2, 0, 3}, 4)
	for _, res := range results {
		for _, num := range res {
			fmt.Printf("%d ", num)
		}
		fmt.Print("\n")
	}
	if len(results) != 1 {
		t.Errorf("%d is not the right length of 3", len(results))
	}
	results = fourSum([]int{1, 0, -1, 0, -2, 2}, 0)
	for _, res := range results {
		for _, num := range res {
			fmt.Printf("%d ", num)
		}
		fmt.Print("\n")
	}
	if len(results) != 3 {
		t.Errorf("%d is not the right length of 3", len(results))
	}
	results = fourSum([]int{}, 0)
	if len(results) != 0 {
		t.Errorf("%d is not the right length of 0", len(results))
	}
}
