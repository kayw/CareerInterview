package career_interview

import "testing"

func TestPowerOf32(t *testing.T) {
	power := IsPowerOfThree(27)
	if power != true {
		t.Errorf("27 should be power of 3")
	}
	power = IsPowerOfThree(26)
	if power != false {
		t.Errorf("26 should be power of 3")
	}
	power = IsPowerOfTwo(26)
	if power != false {
		t.Errorf("26 should be power of 2")
	}
	power = IsPowerOfTwo(4)
	if power != true {
		t.Errorf("4 should be power of 2")
	}
}
