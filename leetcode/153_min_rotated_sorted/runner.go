package career_interview

//https://siddontang.gitbooks.io/leetcode-solution/content/array/find_minimum_in_rotated_sorted_array.html
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
		if nums[lo] > nums[mid] {
			hi = mid
		} else if nums[mid] > nums[lo] {
			lo = mid
		}
	}
	return nums[mid]
}

// http://www.cnblogs.com/yuzhangcmu/p/4049030.html
