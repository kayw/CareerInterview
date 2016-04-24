package career_interview

//http://www.sigmainfy.com/blog/two-sum-problem-analysis-1-sort-hash-unique-solution.html
import (
	"fmt"
	"sort"
)

func twoSum(nums []int, target int) []int {
	numIndexMap := make(map[int]int)
	for index, num := range nums {
		numIndexMap[num] = index
	}
	sort.Ints(nums)
	i := 0
	j := len(nums) - 1
	var result []int
	for i < j {
		total := nums[i] + nums[j]
		if total == target {
			indexI := numIndexMap[nums[i]]
			indexJ := numIndexMap[nums[j]]
			result = []int{indexI, indexJ}
			fmt.Println("found nums", nums[i], nums[j])
			break
		} else if total < target {
			i++
		} else {
			j--
		}
	}
	return result
}
