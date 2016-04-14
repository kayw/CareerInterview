package career_interview

func max(a, b int) int {
	if a > b {
		return a
	} else {
		return b
	}
}

//https://leetcode.com/discuss/96727/java-concise-hashmap-solution
func LengthOfLongestSubstring(s string) int {
	charMap := make(map[rune]int)
	var substrBuffer []byte = make([]byte, len(s))
	curBegin := 0
	bufLen := 0
	maxLenSoFar := 0
	maxBegin := 0
	for i, ch := range s {
		if index, ok := charMap[ch]; ok {
			curBegin = max(index+1, curBegin) // "abba"
		}
		charMap[ch] = i
		bufLen = i - curBegin + 1
		println(bufLen)
		if bufLen > maxLenSoFar {
			maxLenSoFar = bufLen
			maxBegin = curBegin
			copy(substrBuffer[0:bufLen], s[maxBegin:maxBegin+bufLen])
			println(string(substrBuffer))
		}
	}
	//this is incorret can not print every string
	println(string(substrBuffer))
	return maxLenSoFar
}
