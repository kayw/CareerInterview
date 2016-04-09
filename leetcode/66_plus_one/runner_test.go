package career_interview

import "testing"

func TestPlusOne(t *testing.T) {
	newDigits := PlusOne([]int{3, 9, 9})
	if newDigits[0] != 4 || newDigits[1] != 0 || newDigits[2] != 0 {
		t.Errorf("wrong")
	}
	newDigits = PlusOne([]int{9, 9})
	if newDigits[0] != 1 || newDigits[1] != 0 {
		t.Errorf("wrong")
	}
	newDigits = PlusOne([]int{1, 0})
	if newDigits[0] != 1 || newDigits[1] != 1 {
		t.Errorf("wrong")
	}
	newDigits = PlusOne([]int{0})
	if newDigits[0] != 1 {
		t.Errorf("wrong")
	}
}
