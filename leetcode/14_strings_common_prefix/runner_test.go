package career_interview

import "testing"

/*
func TestLSCSort(t *testing.T) {
	strings := []string{
		"ABCD", "ABEF", "ACEF",
	}
	// wrong the shortest two may have longer common string
	prefix := LongestStringsCommonPrefixWithSort(strings)
	println(prefix)
	if prefix != "A" {
		t.Errorf("ABCD, ABEF, ACEF should have longest prefix A but got %s", prefix)
	}
	strings = []string{
		"ABCDEFG", "ABCEFG", "ABCEFA",
	}
	prefix = LongestStringsCommonPrefixWithSort(strings)
	t.Log(len(prefix))
	if prefix != "ABC" {
		t.Errorf("ABCDEFG, ABCEFG ,ABCEFA should have longest prefix ABC but got %s", prefix)
	}
}
*/

func TestLSCNM(t *testing.T) {
	// http://www.cnblogs.com/goblinengineer/p/5321819.html testcase
	strings := []string{
		"ABCD", "ABEF", "ACEF",
	}
	prefix := LongestStringsCommonPrefixNM(strings)
	if prefix != "A" {
		t.Errorf("ABCD, ABEF, ACEF should have longest prefix A but got %s", prefix)
	}
	strings = []string{
		"ABCDEFG", "ABCEFG", "ABCEFA",
	}
	prefix = LongestStringsCommonPrefixNM(strings)
	if prefix != "ABC" {
		t.Errorf("ABCDEFG, ABCEFG ,ABCEFA should have longest prefix ABC but got %s", prefix)
	}
}
