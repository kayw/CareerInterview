package career_interview

import (
	"fmt"
	"testing"
)

func Test5x3Matrix(t *testing.T) {
	matrix := [][]int{
		{1, 2, 0, 3, 4},
		{2, 3, 4, 5, 1},
		{1, 1, 5, 3, 0},
	}
	maxSum, maxMatrix := GetMatrixMaxSum(matrix, 3, 5)
	fmt.Println(maxMatrix)
	if maxSum != 17 && maxMatrix[0][0] != 4 {
		println("matrix max sum should be 17")
	}
}
