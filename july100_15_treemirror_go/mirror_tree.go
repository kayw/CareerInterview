package career_interview

import "fmt"

type TreeNode struct {
	leftNode_, rightNode_ *TreeNode
	data_                 interface{}
}

//http://stackoverflow.com/questions/23531891/how-do-i-succinctly-remove-the-first-element-from-a-slice-in-go
//https://github.com/eapache/queue/blob/master/queue.go
func (root *TreeNode) mirror() {
	//nodeStack := make([]*TreeNode, 0)
	var nodeStack []*TreeNode
	//fmt.Printf("root is %#v\n", root)
	nodeStack = append(nodeStack, root)
	var r *TreeNode
	for len(nodeStack) != 0 {
		//fmt.Printf("nodestacknode len is %#v, [0] is %#v\n", len(nodeStack), nodeStack[0])
		r, nodeStack = nodeStack[0], nodeStack[1:]
		//fmt.Printf("current process node is %#v\n", r)
		if r.leftNode_ != nil {
			nodeStack = append(nodeStack, r.leftNode_)
		}
		if r.rightNode_ != nil {
			nodeStack = append(nodeStack, r.rightNode_)
		}
		r.leftNode_, r.rightNode_ = r.rightNode_, r.leftNode_
	}
}

func (r *TreeNode) print_tree_by_level() {
	var nodesInCurLevel []*TreeNode
	nodesInCurLevel = append(nodesInCurLevel, r)
	var node *TreeNode
	for len(nodesInCurLevel) != 0 {
		for _, node = range nodesInCurLevel {
			fmt.Print("  ", node.data_)
		}
		fmt.Print("\n")
		var nodeNum = len(nodesInCurLevel)
		for i := 0; i < nodeNum; i++ {
			node, nodesInCurLevel = nodesInCurLevel[0], nodesInCurLevel[1:]
			if node.leftNode_ != nil {
				nodesInCurLevel = append(nodesInCurLevel, node.leftNode_)
			}
			if node.rightNode_ != nil {
				nodesInCurLevel = append(nodesInCurLevel, node.rightNode_)
			}
		}
	}
}
