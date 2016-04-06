package career_interview

type NumArray struct {
	sums []int
}

// another way len(nums) + 1 sums array sums[0] = 0  sums[j+1] = sum{0, j}
// http://www.cnblogs.com/jcliBlogger/p/4952704.html
// http://bookshadow.com/weblog/2015/11/10/leetcode-range-sum-query-immutable/
func NewNumArray(nums []int) *NumArray {
	sum := 0
	//preprocess nums sum from 0 to index i
	sums := make([]int, len(nums))
	for i, num := range nums {
		sum += num
		sums[i] = sum
	}
	return &NumArray{
		sums: sums,
	}
}

func (na *NumArray) sumRange(i, j int) int {
	if i < 0 || i > j || j > len(na.sums) {
		return 0
	}
	subtract := 0
	if i != 0 {
		subtract = na.sums[i-1]
	}
	return na.sums[j] - subtract
}
