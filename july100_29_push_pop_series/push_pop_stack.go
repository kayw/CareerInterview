//http://zhedahht.blog.163.com/blog/static/25411174200732102055385
package career_interview

import "github.com/kayw/gobase"

func isPopOrder(pushed []int, poped []int) bool {
	var isOrder = false
	var serieLen = len(pushed)
	if serieLen != 0 && len(pushed) == len(poped) {
		stack := gobase.NewStack()
		var pushIdx = 0
		var popIdx = 0
		for popIdx < serieLen {
			for stack.Empty() || stack.Peek().(int) != poped[popIdx] {
				if pushIdx < serieLen {
					stack.Push(pushed[pushIdx])
					pushIdx += 1
				} else {
					break
				}
			}
			if stack.Peek().(int) != poped[popIdx] {
				break
			}
			stack.Pop()
			popIdx++
		}
		if stack.Empty() && popIdx == serieLen {
			isOrder = true
		}
	}
	return isOrder
}

// vim:ts=4:sw=4:et
