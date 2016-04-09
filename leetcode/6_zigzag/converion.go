package career_interview

func Convert(s string, numRows int) string {
	if numRows >= len(s) || numRows == 1 {
		return s
	}
	buffer := make([]byte, len(s))
	bufLen := 0
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

//https://leetcode.com/discuss/55208/if-you-are-confused-with-zigzag-pattern-come-and-see
/*
/*n=numRows
Δ=2n-2    1                           2n-1                         4n-3
Δ=        2                     2n-2  2n                    4n-4   4n-2
Δ=        3               2n-3        2n+1              4n-5       .
Δ=        .           .               .               .            .
Δ=        .       n+2                 .           3n               .
Δ=        n-1 n+1                     3n-3    3n-1                 5n-5
Δ=2n-2    n                           3n-2                         5n-4

that's the zigzag pattern the question asked! Be careful with nR=1 && nR=2
*/
