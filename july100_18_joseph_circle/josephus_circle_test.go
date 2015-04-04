package career_interview

import (
	"fmt"
	"testing"
)

func Test5in2JosephCircle(t *testing.T) {
	remain := JosephProblem(5, 2)
	if remain != 3 {
		t.Errorf("Remain one in josphe circle should be 3, return value is %d", remain)
	}
	remain = JosephProblem(7, 4)
	if remain != 2 {
		t.Errorf("Remain one in josphe circle should be 2, return value is %d", remain)
	}
	remain = JosephCircleIncorrectThought(5, 2)
	fmt.Println("JosephCircleIncorrectThought remain value is ", remain)
}
