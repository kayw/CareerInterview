// Package  provides testFirstUniqueChar
package career_interview

import (
	"testing"
)

func TestFirstUniqueChar(t *testing.T) {
	const str = "abcdfdcbag"
	char := findFirstUniqueRune(str)
	if char != 'f' {
		t.Errorf("findFirstUniqueRune want %c return %c", 'f', char)
	}
}

func TestFindNonUniqueChar(t *testing.T) {
	const str = "abcdabcd"
	char := findFirstUniqueRune(str)
	if char != 0 {
		t.Errorf("findFirstUniqueRune should find no unique rune, but find %c", char)
	}
}
