package career_interview

func Convert(s string, numRows int) string {
	buffer := make([]byte, len(s))
	bufLen := 0
	if numRows == 1 {
		bufLen += copy(buffer[bufLen:], s)
		return string(buffer)
	}
	//var index int
	for r := 0; r < numRows; r++ {
		j := 0
		for {
			left := 2*(numRows-1)*j - r
			if left >= len(s) {
				break
			}
			if r != 0 && r != numRows-1 && left > 0 {
				bufLen += copy(buffer[bufLen:], s[left:left+1])
			}
			right := 2*(numRows-1)*j + r
			if right >= len(s) {
				break
			}
			bufLen += copy(buffer[bufLen:], s[right:right+1])
			/*
				if r != 0 && r != numRows-1 {
					index = 2*(numRows-1)*j - r
					println("on index", index)
					if index > 0 && index < len(s) {
						bufLen += copy(buffer[bufLen:], s[index:index+1])
					} else if index > len(s) {
						break
					}
				}
				index = 2*(numRows-1)*j + r
				println("off index", index)
				if index < len(s) {
					bufLen += copy(buffer[bufLen:], s[index:index+1])
				} else {
					break
				}
			*/
			j++
		}
	}
	return string(buffer)
}
