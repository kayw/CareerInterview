package career_interview

func FindMin(nums []int) int {
	len := len(nums)
	if len == 0 {
		return -1
	}
	lo, hi := 0, len-1
	mid := 0
	for lo < hi {
		if nums[lo] < nums[hi] {
			mid = lo
			break
		}
		if lo+1 == hi {
			if nums[lo] < nums[hi] {
				mid = lo
			} else {
				mid = hi
			}
			break
		}
		println("lo hi", lo, hi)
		mid = lo + (hi-lo)/2
		println("mid", mid)
		println("nums[lo]:", nums[lo], "nums[mid]:", nums[mid], "nums[hi]:", nums[hi])
		/*
			if nums[lo] > nums[mid] {
				lo = mid
			} else if nums[mid] > nums[lo] {
				hi = mid
			}
		*/
		if nums[lo] < nums[mid] && nums[mid] > nums[hi] {
			lo = mid
		} else if nums[lo] > nums[mid] && nums[mid] < nums[hi] {
			lo = mid
		} else if nums[lo] < nums[mid] && nums[mid] < nums[hi] {
			hi = mid
		} else if nums[lo] == nums[mid] && nums[lo] < nums[hi] {
			hi = mid
		} else if nums[lo] < nums[hi] && nums[mid] == nums[hi] {
			lo = mid
		}
	}
	return nums[mid]
}
