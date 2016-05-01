package career_interview

//http://www.sigmainfy.com/blog/4sum-problem-analysis-different-time-complexity.html
//https://leetcode.com/discuss/15690/proved-to-be-a-best-o-n-2-worst-o-n-3-solution
import (
	"fmt"
	"sort"
)

func fourSum(nums []int, target int) [][]int {
	var numIndex = make(map[int]int)
	var twoSumIndex = make(map[int]int)
	sort.Ints(nums)
	for i, num := range nums {
		numIndex[num] = i
		for j := i + 1; j < len(nums); j++ {
			sum := num + nums[j]
			twoSumIndex[sum] = i
		}
	}
	result := make([][]int, 0)
	for i := 0; i < len(nums); i++ {
		if i > 0 && nums[i] == nums[i-1] {
			continue
		}
		tmp := make([]int, 0)
		tmp = append(tmp, nums[i])
		fmt.Printf("i:%d ", nums[i])
		for j := i + 1; j < len(nums); j++ {
			if j > i+1 && nums[j] == nums[j-1] {
				continue
			}
			sum2 := nums[i] + nums[j]
			halfSum := target - sum2
			fmt.Printf("j:%d ", nums[j])
			if index, ok := twoSumIndex[halfSum]; ok && index > j {
				tmp = append(tmp, nums[j])
				for k := j + 1; k < len(nums); k++ {
					if k > j+1 && nums[k] == nums[k-1] {
						continue
					}
					fmt.Printf("k:%d ", nums[k])
					remainder := halfSum - nums[k]
					if index, ok = numIndex[remainder]; ok && index > k {
						fmt.Printf("rem:%d ", remainder)
						tmp = append(tmp, nums[k], remainder)
						fmt.Printf("tmp: %p", &tmp)
						for _, t := range tmp {
							fmt.Printf("%d ", t)
						}
						// result = append(result, tmp)
						result = append(result, append([]int(nil), tmp...))
						/*
							for _, res := range result {
								for _, t := range res {
									fmt.Printf("%d ", t)
								}
							}
						*/
						tmp = tmp[:len(tmp)-2]
					}
				}
				tmp = tmp[:1]
			}
		}
		fmt.Printf("\n")
	}
	fmt.Printf("\n")
	return result
}
