package career_interview

import (
	//"fmt"
	"testing"
)

func TestSimpleTreeMirror(t *testing.T) {
	ll1 := TreeNode{data_: "ll1"}
	//ll2 := TreeNode{data_: "ll2"}
	lb := TreeNode{data_: "lb", leftNode_: &ll1}
	rl1 := TreeNode{data_: "rl1"}
	rl2 := TreeNode{data_: "rl2"}
	rb := TreeNode{data_: "rb", leftNode_: &rl1, rightNode_: &rl2}
	r := TreeNode{data_: "r", leftNode_: &lb, rightNode_: &rb}
	r.print_tree_by_level()
	r.mirror()
	r.print_tree_by_level()
	if r.leftNode_.data_ != "rb" && r.leftNode_.leftNode_ != nil {
		t.Errorf("r mirror rotation failed")
	}
}
