package career_interview

import "testing"

func TestMaxBackwardsSum(t *testing.T) {
	/*
		matrix := [][]int{
			{1, 2, 6},
			{9, 8, 4},
			{-5, 5, 2},
		}
		walkSum := SumBackPathDP(matrix)
		if walkSum != 37 {
			t.Errorf("expected 37, calculated sum is %d", walkSum)
		}
	*/
	var matrix = [][]int{
		{1, 2, 3},
		{6, 5, 4},
		{7, 8, 9},
	}
	var walkSum = SumBackPathDP(matrix)
	if walkSum != 42 {
		t.Errorf("expected 42, calculated sum is %d", walkSum)
	}
	/*
		walkSum = SumPathMirror(matrix)
		if walkSum != 42 {
			t.Errorf("expected 42, calculated sum is %d", walkSum)
		}
			var matrix = [][]int{
				{1, -1, 0},
				{0, 1, 1},
				{0, 1, 1},
			}
			var walkSum = SumBackPathDP(matrix)
			if walkSum != 4 {
				t.Errorf("expected 4, calculated sum is %d", walkSum)
			}
	*/
	/*
		matrix = [][]int{
			{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16},
		}
		walkSum = SumBackPathDP(matrix)
		if walkSum != 1+5+9+13+14+15+16+2+6+10+11+12 {
			t.Errorf("expected 4, calculated sum is %d", walkSum)
		}
	*/
}
