package career_interview

import "testing"

func TestImutableSumRangeQuery(t *testing.T) {
	numarr := NewNumArray([]int{-2, 0, 3, -5, 2, -1})
	sum := numarr.sumRange(2, 5)
	if sum != -1 {
		t.Errorf("sum error %d", sum)
	}
}
