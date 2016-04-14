package career_interview

import "testing"

func TestLengthOfLongestSubstring(t *testing.T) {
	len := LengthOfLongestSubstring("abcabcd")
	if len != 4 {
		t.Errorf("%d is not the longest", len)
	}
	len = LengthOfLongestSubstring("bbbbbb")
	if len != 1 {
		t.Errorf("%d is not the longest", len)
	}
	len = LengthOfLongestSubstring("bbcd")
	if len != 3 {
		t.Errorf("%d is not the longest", len)
	}
	len = LengthOfLongestSubstring("abcabcbb")
	if len != 3 {
		t.Errorf("%d is not the longest", len)
	}
	len = LengthOfLongestSubstring("bcbd")
	if len != 3 {
		t.Errorf("%d is not the longest", len)
	}
	len = LengthOfLongestSubstring("abdab") // two possible longest
	if len != 3 {
		t.Errorf("%d is not the longest", len)
	}
	len = LengthOfLongestSubstring("abba") // two possible longest
	if len != 2 {
		t.Errorf("%d is not the longest", len)
	}
}
