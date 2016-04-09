package career_interview

import "bytes"

func preprocess(str string) string {
	var buffer bytes.Buffer
	buffer.WriteString("^")
	for _, s := range str {
		buffer.WriteString("#")
		buffer.WriteRune(s)
	}
	buffer.WriteString("#")
	buffer.WriteString("$")
	return buffer.String()
}

func min(a, b int) int {
	if a < b {
		return a
	} else {
		return b
	}
}
func FindLongestPalindrome(str string) string {
	if len(str) < 2 {
		return str
	}
	tstr := preprocess(str)
	println(tstr)
	palLens := make([]int, len(tstr))
	center := 0
	maxpl := 1
	for i := 1; i < len(tstr)-1; i++ {
		if maxpl > i {
			iMirror := 2*center - i
			palLens[i] = min(maxpl-i, palLens[iMirror])
		} else {
			palLens[i] = 1
		}
		for tstr[i+palLens[i]] == tstr[i-palLens[i]] {
			palLens[i]++
		}
		if palLens[i]+i > maxpl {
			center = i
			maxpl = palLens[i] + i
		}
	}
	println(center, maxpl)
	maxLen := 0
	centerIndex := 0
	for i := 1; i < len(palLens)-1; i++ {
		pal := palLens[i]
		if pal > maxLen {
			centerIndex = i
			maxLen = pal
		}
	}
	start := (centerIndex - maxLen) / 2
	println(centerIndex, start, maxLen)
	return str[start : start+maxLen-1]
}

// https://www.quora.com/What-is-the-most-efficient-algorithm-to-find-the-longest-palindrome-in-a-string suffix tree longest common prefix
// https://www.akalin.com/longest-palindrome-linear-time  explaination /awkward code
