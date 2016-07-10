// http://www.mitbbs.com/article_t/JobHunting/33200117.html
// 给一个巨大的二维平面 横纵坐标无限 给定一个坐标点写一个add value函数 和求给定
// 一个四边形范围内的所有value的和 get sum 函数
// 不能用二维数组存因为是无限的平面 要求add value和get sum尽量高效

// 给定坐标点作为maxRow/maxCol, 不用2d array,用hash with row col
/*
计算sum (0,0) -> (x, y) 内所有点的value，而且对方没让我写代码，只是一个open ended discussion:
1. insertion > query
2. query > insertion
3. insertion = query

segmented tree现在看到才有点印象，当时一点也没想起来，我第一步就是直接按X排
序，然后按Y排序，然后可以query出来点，进行sum；后来多想了一个按照每个点预计
算总和，但没想到二分或者四分，对方也没有多问下去。。

每个点有一个value (1,1) = 2, (1,2) = 1, (3,3) =2, 那么sum(0,0 -> 2,2) => 3
*/

// http://blog.csdn.net/u012175043/article/details/50093933
// https://discuss.leetcode.com/topic/30343/java-2d-binary-indexed-tree-solution-clean-and-short-17ms
package career_interview

import "fmt"

type NumMatrix struct {
	rowNum  int
	colNum  int
	bitTree [][]int
	matrix  [][]int
}

func newNumMatrix(matrix [][]int) *NumMatrix {
	nm := new(NumMatrix)
	nm.rowNum = len(matrix)
	nm.colNum = 0
	if nm.rowNum > 0 {
		nm.colNum = len(matrix[0])
	}
	nm.matrix = make([][]int, nm.rowNum)
	for i := 0; i < nm.rowNum; i++ {
		nm.matrix[i] = make([]int, nm.colNum)
	}
	nm.bitTree = make([][]int, nm.rowNum+1)
	for i := 0; i < nm.rowNum+1; i++ {
		nm.bitTree[i] = make([]int, nm.colNum+1)
	}
	fmt.Printf("update sum %v", nm)
	for row := range matrix {
		for col := range matrix[row] {
			nm.update(row, col, matrix[row][col])
		}
	}
	return nm
}

func (nm *NumMatrix) update(row, col, value int) {
	if nm.rowNum == 0 || nm.colNum == 0 {
		return
	}
	diff := value - nm.matrix[row][col]
	nm.matrix[row][col] = value
	for i := row + 1; i <= nm.rowNum; i += i & -i {
		for j := col + 1; j <= nm.colNum; j += j & -j {
			nm.bitTree[i][j] += diff
		}
	}
}

func (nm *NumMatrix) sum(row, col int) int {
	sum := 0
	for i := row; i > 0; i = i & (i - 1) {
		for j := col; j > 0; j = j & (j - 1) {
			sum += nm.bitTree[i][j]
		}
	}
	return sum
}

func (nm *NumMatrix) sumRegion(row1, col1, row2, col2 int) int {
	return nm.sum(row2+1, col2+1) + nm.sum(row1, col1) - nm.sum(row1, col2+1) - nm.sum(row2+1, col1)
}
