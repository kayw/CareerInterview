package career_interview

// http://blog.csdn.net/zhanxinhang/article/details/6731134

func GetMatrixMaxSum(matrix [][]int, row, col int) (int, [][]int) {
	max_sum, coordx, coordy, sum, last_sum := 0, 0, 0, 0, matrix[0][0]+matrix[1][0]
	for i := 0; i < row-1; i++ {
		for j := 1; j < col; j++ {
			sum = last_sum
			last_sum = matrix[i][j] + matrix[i+1][j]
			sum += last_sum
			if max_sum < sum {
				max_sum = sum
				coordx = i
				coordy = j - 1
			}
		}
	}
	// http://www.dotnetperls.com/2d-go
	// 2d := [2][2]string {}
	// 2d[0][0] = "xx"

	//http://www.tutorialspoint.com/go/go_multi_dimensional_arrays.htm
	//https://groups.google.com/forum/#!topic/golang-nuts/sPYRl4RHFdU
	max_matrix := [][]int{
		{matrix[coordx][coordy], matrix[coordx][coordy]},
		{matrix[coordx+1][coordy], matrix[coordx+1][coordy+1]},
	}
	return max_sum, max_matrix
}
