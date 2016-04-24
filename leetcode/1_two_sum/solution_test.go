package career_interview

import "testing"

func TestTwoSum(t *testing.T) {
	//http://stackoverflow.com/questions/11928091/linear-time-algorithm-for-2-sum
	nums := []int{0, 1, 10,
		10,
		-10,
		10000,
		-10000,
		10001,
		9999,
		-10001,
		-9999,
		10000,
		5000,
		5000,
		-5000,
		-1,
		1000,
		2000,
		-1000,
		-2000,
	}
	targetIndice := twoSum(nums, 0)
	if targetIndice[0] != 9 || targetIndice[1] != 7 { /*-10001, 10001*/
		t.Errorf(
			"first values should be [-10001, 10001]",
		)
	}
}

func TestTwoSumSameValues(t *testing.T) {
	nums := []int{2, 1, 1, 2}
	targetIndice := twoSum(nums, 2)
	if targetIndice[0] != 1 || targetIndice[1] != 2 {
		t.Errorf("values should be [1,1]")
	}
}
