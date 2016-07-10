package career_interview

import "testing"

func Test3x4Arrays(t *testing.T) {
	matrix := [][]int{
		{3, 0, 1, 4},
		{5, 6, 3, 2},
		{1, 2, 0, 1},
	}
	nm := newNumMatrix(matrix)
	sum := nm.sumRegion(1, 1, 2, 2)
	if sum != 11 {
		t.Errorf("(1, 1) -> (2,2) sum %d not 11", sum)
	}
	nm.update(2, 1, 4)
	sum = nm.sumRegion(1, 1, 2, 2)
	if sum != 13 {
		t.Errorf("(1, 1) -> (2,2) sum %d not 13", sum)
	}
}
