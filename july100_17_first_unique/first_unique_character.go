package career_interview

//see ../string_cycle_shift.cpp
import (
	"fmt"
	"unicode/utf8"
)

func findFirstUniqueRune(str string) rune {
	charCount := make(map[rune]int, 4)
	var rv rune
	//for _, char := range str {
	for i, w := len(str)-1, 0; i >= 0; i -= w {
		charRune, width := utf8.DecodeRuneInString(str[i:])
		fmt.Printf("%#U(width:%d) starts at byte position %d\n", charRune, width, i)
		charCount[charRune]++
		if charCount[charRune] == 1 {
			rv = charRune
		}
		w = width
	}
	if charCount[rv] != 1 {
		rv = 0
	}
	return rv
}
