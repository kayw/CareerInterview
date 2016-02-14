package gobase

import (
	"testing"
)

func TestStack(t *testing.T) {
	s := NewStack()
	s.Push(75)
	s.Push(124)
	s.Push("Hello")

	if s.size != 3 {
		t.Fatalf("Unexpected stack size: expected 3, got %d", s.size)
	}
	if elem, _ := s.Pop(); elem.(string) != "Hello" {
		t.Fatalf("Unexpected popped value.")
	}
	if s.size != 2 {
		t.Fatalf("Unexpected stack size: expected 2, got %d", s.size)
	}
	if elem, _ := s.Pop(); elem.(int) != 124 {
		t.Fatalf("Unexpected popped value.")
	}
	if s.size != 1 {
		t.Fatalf("Unexpected stack size: expected 3, got %d", s.size)
	}
	if elem, _ := s.Pop(); elem.(int) != 75 {
		t.Fatalf("Unexpected popped value.")
	}
	if s.size != 0 {
		t.Fatalf("Unexpected stack size: expected 3, got %d", s.size)
	}
}

func TestCapacityStack(t *testing.T) {
	s := NewStackWithCapacity(4)
	if c := s.blockSize; c != 4 {
		t.Fatalf("unexpected stack block size: got %d,expect 4", c)
	}
	for i := 0; i < 15; i++ {
		s.Push(i)
	}
	if v := s.Peek().(int); v != 14 {
		t.Fatalf("Unexpected stack block size: got %d, expected 14", v)
	}
	if v := len(s.blocks); v != 4 {
		t.Fatalf("Unexpected number of allocated pages: got %d, expected 4", v)
	}
	if v := s.offset; v != 3 {
		t.Fatalf("Unexpected stack page offset: got %d, expected 3", v)
	}

	if s.size != 15 {
		t.Fatalf("Unexpected stack size after 14 insertions: %d", s.size)
	}

	for i := 14; i >= 0; i-- {
		if v, _ := s.Pop(); v != i {
			t.Fatalf("Unexpected popped value: got %d, expected %d", v, i)
		}
	}
}

func BenchmarkPush(b *testing.B) {
	stack := NewStack()
	b.N = 102400
	for i := 0; i < b.N; i++ {
		stack.Push(i)
	}
}

func BenchmarkPop(b *testing.B) {
	stack := NewStack()
	b.N = 102400
	for i := 0; i < b.N; i++ {
		stack.Push(i)
	}
	b.ResetTimer()
	for !stack.empty() {
		stack.Pop()
	}
}
