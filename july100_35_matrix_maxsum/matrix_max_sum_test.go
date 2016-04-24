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

//http://www.geeksforgeeks.org/dynamic-programming-set-27-max-sum-rectangle-in-a-2d-matrix/
/*
    int M[ROW][COL] = {{1, 2, -1, -4, -20},
                           {-8, -3, 4, 2, 1},
			                          {3, 8, 10, 1, 3},
						                         {-4, -1, 1, 7, -6}
									                       };

*/
