package career_interview

import "testing"

func TestFindRotateMin(t *testing.T) {
	min := FindMin([]int{4, 5, 6, 7, 0, 1, 2})
	if min != 0 {
		t.Errorf("rotate min should be 0, got %d", min)
	}
	min = FindMin([]int{2, 1})
	if min != 1 {
		t.Errorf("rotate min should be 0, got %d", min)
	}
	min = FindMin([]int{0, 1, 2})
	if min != 0 {
		t.Errorf("rotate min should be 0, got %d", min)
	}
}
