package career_interview

import (
	"fmt"
	"testing"
)

func TestGreedyFlaw1(t *testing.T) {
	list1 := []int{2, 3, 5, 7}
	list2 := []int{1, 4, 6, 10}
	fmt.Println("for the below list set", list1, list2)
	big, small := PartitionEqualSubsetGreedyFlawed1(list1, list2)
	fmt.Println("flawed1 computed result list is", big, small)
	fmt.Println("minimal diff result list we can get", []int{1, 3, 5, 10}, []int{2, 4, 6, 7})
}

func TestGreedyFlaw2(t *testing.T) {
	// http://blog.csdn.net/tianshuai1111/article/details/7479767
	list1 := []int{5, 5, 9, 10}
	list2 := []int{4, 7, 7, 13}
	fmt.Println("for the below list set", list1, list2)
	PartitionEqualSubsetSwapGreedyFlawed2(list1, list2)
	fmt.Println("flawed2 computed result list is", list1, list2)
	fmt.Println("minimal diff result list we can get", []int{4, 7, 9, 10}, []int{5, 5, 7, 13})
	// http://blog.csdn.net/xshbx/article/details/6845766
	list1 = []int{1, 1, 2, 5, 10}
	list2 = []int{3, 4, 4, 8, 8}
	fmt.Println("for the below list set", list1, list2)
	PartitionEqualSubsetSwapGreedyFlawed2(list1, list2)
	fmt.Println("flawed2 computed result list is", list1, list2)
	fmt.Println("minimal diff result list we can get", []int{1, 3, 4, 5, 10}, []int{1, 2, 4, 8, 8})
	// passed

}

func TestSubsetMinimal(t *testing.T) {
	list1 := []int{1, 1, 2, 5, 10}
	list2 := []int{3, 4, 4, 8, 8}
	diff := PartitionSubsetMinimal(list1, list2)
	diff2 := PartitionSubsetMinimalV2(list1, list2)
	println("diff2:", diff2)
	if diff != 0 {
		t.Errorf("computed diff %d is not 0", diff)
	}
	list1 = []int{1, 3, 5, 7}
	list2 = []int{2, 4, 6, 10}
	diff = PartitionSubsetMinimal(list1, list2)
	if diff != 0 {
		t.Errorf("computed diff %d is not 0", diff)
	}
}

func TestPrintSubsets(t *testing.T) {
	list1 := []int{1, 1, 2, 5, 10}
	list2 := []int{3, 4, 4, 8, 8}
	flist1, flist2, diff := PartitionSubsetMinimalAndGet(list1, list2)
	fmt.Println("partitioned lists:", flist1, flist2)
	fmt.Println("diff:", diff)
	list1 = []int{1, 3, 5, 7}
	list2 = []int{2, 4, 6, 10}
	flist1, flist2, diff = PartitionSubsetMinimalAndGet(list1, list2)
	fmt.Println("partitioned lists:", flist1, flist2)
	fmt.Println("diff:", diff)
	list1 = []int{1, 7}
	list2 = []int{4, 11}
	flist1, flist2, diff = PartitionSubsetMinimalAndGet(list1, list2)
	fmt.Println("partitioned lists:", flist1, flist2)
	fmt.Println("diff:", diff)
}
