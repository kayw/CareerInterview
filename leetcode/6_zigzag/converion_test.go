package career_interview

import "testing"

func TestConvertRow2(t *testing.T) {
	str := "abc"
	converted := Convert(str, 2)
	if converted != "acb" {
		t.Errorf("wrong zigzag %s", converted)
	}
}

func TestConvertRow3(t *testing.T) {
	str := "PAYPALISHIRING"
	converted := Convert(str, 3)
	if converted != "PAHNAPLSIIGYIR" {
		t.Errorf("wrong zigzag %s", converted)
	}
}

func TestConvertRow4(t *testing.T) {
	str := "abcde"
	converted := Convert(str, 4)
	if converted != "abced" {
		t.Errorf("wrong zigzag %s", converted)
	}
}

func TestConvertCol1(t *testing.T) {
	str := "abcde"
	converted := Convert(str, 6)
	if converted != "abcde" {
		t.Errorf("wrong zigzag %s", converted)
	}
}

func TestConvertStr1(t *testing.T) {
	str := "a"
	converted := Convert(str, 1)
	if converted != "a" {
		t.Errorf("wrong zigzag %s", converted)
	}
}
