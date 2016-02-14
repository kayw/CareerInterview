package career_interview

import (
	"testing"
)

func TestIsPopOrder(t *testing.T) {
	pushOrder := []int{1, 2, 3, 4, 5}
	popOrder := []int{4, 5, 3, 2, 1}
	isorder := isPopOrder(pushOrder, popOrder)
	if !isorder {
		t.Error("4,5,3,2,1 should be poped order")
	}
}
