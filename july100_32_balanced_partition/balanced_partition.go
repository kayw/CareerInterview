package career_interview

import (
	"math"
	"sort"
)

func IntAbs(num int) int {
	if num < 0 {
		return -num
	} else {
		return num
	}
}
func Sum(list []int) int {
	sum := 0
	for _, l := range list {
		sum += l
	}
	return sum
}

// http://outofmemory.cn/code-snippet/1658/python-get-two-sequence-sum-least-chazhi-sequence
func flawed1_mean(sorted_list []int) ([]int, []int) {
	if len(sorted_list) == 0 {
		return []int{}, []int{}
	}

	var big = sorted_list[len(sorted_list)-1]
	var small = sorted_list[len(sorted_list)-2]
	var big_list, small_list = flawed1_mean(sorted_list[:len(sorted_list)-2])

	big_list = append(big_list, small)
	small_list = append(small_list, big)

	var big_list_sum = Sum(big_list)
	var small_list_sum = Sum(small_list)

	if big_list_sum > small_list_sum {
		return big_list, small_list
	} else {
		return small_list, big_list
	}
}

func PartitionEqualSubsetGreedyFlawed1(list1 []int, list2 []int) ([]int, []int) {
	sorted := append(list1, list2...)
	// https://gobyexample.com/sorting
	sort.Ints(sorted)
	big, small := flawed1_mean(sorted)
	return big, small
}

//http://blog.csdn.net/ljsspace/article/details/6434621

//http://blog.csdn.net/xshbx/article/details/6845766
/*
假设序列a，b中元素的和为sum_a和sum_b。假设aa和bb分别为序列a，b中的元素，
则交换aa，bb后序列的和变为sum_a-aa+bb，sum_b+aa-bb；两序列的差为（sum_a-aa+bb）-（sum_b+aa-bb）=sum_a-sum_b-2*（aa-bb）；

所以可以扫描序列a，b中的元素，找到使abs（sum_a-sum_b-2*（aa-bb））最小的两个元素进行交换，重复此过程，直至两序列的差无法减小
*/
//http://blog.csdn.net/tianshuai1111/article/details/7479767
/*
当前数组a和数组b的和之差为
A = sum(a) - sum(b)

a的第i个元素和b的第j个元素交换后，a和b的和之差为
A' = sum(a) - a[i] + b[j] - （sum(b)- b[j] + a[i])
   = sum(a) - sum(b) - 2 (a[i] - b[j])
   = A - 2 (a[i] - b[j])

设x= a[i] - b[j]
|A| - |A'| = |A| - |A-2x|

假设A> 0,
当x在(0,A)之间时，做这样的交换才能使得交换后的a和b的和之差变小，
x越接近A/2效果越好,
如果找不到在(0,A)之间的x，则当前的a和b就是答案。

所以算法大概如下：
在a和b中寻找使得x在(0,A)之间并且最接近A/2的i和j，交换相应的i和j元素，
重新计算A后，重复前面的步骤直至找不到(0,A)之间的x为止。
*/
/*
因为一次只允许交换一对元素，这对于一次需要交换两个元素的数组而言将出错，考虑如下情况：
A ＝ { 5,5,9,10 };
B ＝ { 4,7,7,13 };
A的和为29，B为31。当把A中的5，5与B中的4，7交换后，A与B的和都为30，差为0.但算法一将检测不到这种交换
为交换过后反而加大了A与B的差距，这算法并没有办法“知道”这种“以退为进”的策略
*/
func PartitionEqualSubsetSwapGreedyFlawed2(list1 []int, list2 []int) {
	length := len(list1)
	sum1 := Sum(list1)
	sum2 := Sum(list2)
	diff := sum1 - sum2
	for diff != 0 {
		besti := 0
		var bestj = 0
		bestchange := 0
		for i := 0; i < length; i++ {
			for j := 0; j < length; j++ {
				change := list1[i] - list2[j]
				if IntAbs(diff-2*change) < IntAbs(diff-2*bestchange) {
					bestchange = change
					besti = i
					bestj = j
				}
			}
		}
		if bestchange == 0 {
			return
		}
		temp := list1[besti]
		list1[besti] = list2[bestj]
		list2[bestj] = temp
		sum1 -= bestchange
		sum2 += bestchange
		diff = sum1 - sum2
	}
}

//http://stackoverflow.com/questions/4899300/partition-a-set-of-numbers-into-two-parts-with-the-smallest-difference
//https://en.wikipedia.org/wiki/Partition_problem
//https://www.careercup.com/question?id=10244832
//http://webcache.googleusercontent.com/search?q=cache:fa0PBgRbo-YJ:www.faraway.me/2013/02/two-equal-sized-subsets-partition.html+&cd=10&hl=en&ct=clnk
func PartitionSubsetMinimal(list1 []int, list2 []int) int {
	list := append(list1, list2...)
	total := Sum(list)
	equal_sum := total / 2
	n := len(list) / 2
	//dp[i][v] = true means that there is i elements added up to value v
	dp := make([][]bool, n+1)
	for i := range dp {
		dp[i] = make([]bool, equal_sum+1)
	}
	dp[0][0] = true
	for k := 1; k <= 2*n; k++ {
		val := list[k-1]
		for i := 1; i <= k && i <= n; i++ {
			for v := 1; v <= equal_sum; v++ {
				//try to take k as ith element
				if v >= val && dp[i-1][v-val] {
					dp[i][v] = true
				}
			}
		}
	}
	//find the answer check dp[n][*]
	for i := equal_sum; i > 0; i-- {
		if dp[n][i] {
			//difference total - i - i = total - 2*i
			return total - 2*i
		}
	}
	return -1
}

//http://algorithmsandme.in/2014/04/balanced-partition-problem/
//keywords: Balanced Partition Problem
func PartitionSubsetMinimalV2(list1 []int, list2 []int) int {
	list := append(list1, list2...)
	total := Sum(list)
	n := len(list)
	dp := make([][]bool, total+1)
	for i := range dp {
		dp[i] = make([]bool, n+1)
	}
	for i := 0; i <= n; i++ {
		dp[0][i] = true
	}
	for i := 1; i <= total; i++ {
		dp[i][0] = false
	}
	for i := 1; i <= total; i++ {
		for j := 1; j <= n; j++ {
			dp[i][j] = dp[i][j-1]
			if i >= list[j-1] {
				dp[i][j] = dp[i][j] || dp[i-list[j-1]][j-1]
			}
		}
	}
	min := math.MaxInt64
	for i := 1; i <= total; i++ {
		for j := 1; j <= n; j++ {
			if dp[i][j] {
				if IntAbs(total-2*i) < min {
					min = IntAbs(total - 2*i)
				}
			}
		}
	}
	return min
}

func getDiffSubsets(list []int, balanced1 []int, balanced2 []int, finalbalanced1 []int, finalbalanced2 []int,
	index1 int, index2 int, sum1 int, sum2 int, index int, diff *int) {
	if index < 0 && IntAbs(sum1-sum2) < *diff {
		for j := 0; j < index1; j++ {
			finalbalanced1[j] = balanced1[j]
		}
		for j := 0; j < index2; j++ {
			finalbalanced2[j] = balanced2[j]
		}
		finalbalanced1[index1] = -1
		finalbalanced2[index2] = -1
		*diff = IntAbs(sum1 - sum2)
	}
	if index >= 0 {
		balanced1[index1] = list[index]
		getDiffSubsets(list, balanced1, balanced2, finalbalanced1, finalbalanced2,
			index1+1, index2, sum1+list[index], sum2, index-1, diff)
		balanced2[index2] = list[index]
		getDiffSubsets(list, balanced1, balanced2, finalbalanced1, finalbalanced2,
			index1, index2+1, sum1, sum2+list[index], index-1, diff)
	}
}

// http://www.geeksforgeeks.org/dynamic-programming-set-18-partition-problem/
// http://ideone.com/g9HvtO
// brute force expontational complexity to get partitioned subsets not equal
func PartitionSubsetMinimalAndGet(list1 []int, list2 []int) ([]int, []int, int) {
	list := append(list1, list2...)
	balanced1, balanced2, finalbalanced1, finalbalanced2 := make([]int, len(list)+1),
		make([]int, len(list)+1), make([]int, len(list)+1), make([]int, len(list)+1)
	for i := 0; i <= len(list); i++ {
		balanced1[i] = -1
		balanced2[i] = -1
	}
	sum1, sum2, index1, index2, diff := 0, 0, 0, 0, math.MaxInt64
	getDiffSubsets(list, balanced1, balanced2, finalbalanced1, finalbalanced2,
		index1, index2, sum1, sum2, len(list)-1, &diff)
	balanced1, balanced2 = []int{}, []int{}

	for _, v := range finalbalanced1 {
		if v != -1 {
			balanced1 = append(balanced1, v)
		} else {
			break
		}
	}
	for _, v := range finalbalanced2 {
		if v != -1 {
			balanced2 = append(balanced2, v)
		} else {
			break
		}
	}
	return balanced1, balanced2, diff
}

// TODO
// http://shenxingfeng1988.blog.163.com/blog/static/106376005201371171345712/ one swap O(nlogn)
/*
当前数组a和数组b的和之差为
 A = sum(a) - sum(b) ，
 a的第i个元素和b的第j个元素交换后，a和b的和之差为
 A' = sum(a) - a[i] + b[j] - （sum(b) - b[j] + a[i])
 = sum(a) - sum(b) - 2 (a[i] - b[j])
 = A - 2 (a[i] - b[j])

 设x = a[i] - b[j]，
 得 |A| - |A'| = |A| - |A-2x|
 假设A > 0，
 当x 在 (0,A)之间时，做这样的交换才能使得交换后的a和b的和之差变小，x越接近A/2效果越好；
  如果找不到在(0,A)之间的x，则当前的a和b就是答案。
  所以算法大概如下：
  在a和b中寻找使得x在(0,A)之间并且最接近A/2的i和j，交换相应的i和j元素，重新计算A后，重复前面的步骤直至找不到(0,A)之间的x为止。
   a[i]-b[j]要接近A/2，则可以这样想， 我们可以对于a数组的任意一个a[k],在数组b中找出与a[k]-C最接近的数（C就是常数，也就是0.5*A） 这个数要么就是a[k]-C，要么就是比他稍大，要么比他稍小，所以可以要二分查找。 查找最后一个小于等于a[k]-C的数和第一个大于等于a[k]-C的数， 然后看哪一个与a[k]-C更加接近，所以T(n) = nlogn
*/
