package career_interview

import "testing"

func TestLongestPalindrome(t *testing.T) {
	palindrome := FindLongestPalindrome("dabcacba")
	if palindrome != "abcacba" {
		t.Errorf("not longest")
	}
	palindrome = FindLongestPalindrome("abaaba")
	if palindrome != "abaaba" {
		t.Errorf("not longest")
	}
	palindrome = FindLongestPalindrome("fdababam")
	if palindrome != "ababa" {
		t.Errorf("not longest")
	}
	palindrome = FindLongestPalindrome("babcbabcbaccba")
	if palindrome != "abcbabcba" {
		t.Errorf("not longest")
	}

}
