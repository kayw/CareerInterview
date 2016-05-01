package career_interview

//http://www.sigmainfy.com/blog/two-sum-problem-analysis-1-sort-hash-unique-solution.html
import (
	"fmt"
	"sort"
)

type numberPair struct {
	num,
	index int
}

type byNumberPair []numberPair

func (np byNumberPair) Len() int           { return len(np) }
func (np byNumberPair) Swap(i, j int)      { np[i], np[j] = np[j], np[i] }
func (np byNumberPair) Less(i, j int) bool { return np[i].num < np[j].num }

func twoSum(nums []int, target int) []int {
	numPairVector := make([]numberPair, len(nums))
	for index, num := range nums {
		numPairVector[index] = numberPair{
			index: index,
			num:   num,
		}
	}
	sort.Sort(byNumberPair(numPairVector))
	i := 0
	j := len(nums) - 1
	var result []int
	for i < j {
		total := numPairVector[i].num + numPairVector[j].num
		if total == target {
			indexI := numPairVector[i].index
			indexJ := numPairVector[j].index
			result = []int{indexI, indexJ}
			fmt.Println("found nums", numPairVector[i].num, numPairVector[j].num)
			break
		} else if total < target {
			i++
		} else {
			j--
		}
	}
	return result
}
