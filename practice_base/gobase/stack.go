package gobase

import "errors"

//https://github.com/karalabe/cookiejar/blob/master/collections/stack
//https://github.com/alediaferia/stackgo

type Stack struct {
	size      int
	capacity  int
	offset    int
	blockSize int
	blocks    [][]interface{}
	active    []interface{}
}

const s_DefaultCap = 4096

func NewStack() *Stack {
	stack := new(Stack)
	stack.active = make([]interface{}, s_DefaultCap)
	stack.blocks = [][]interface{}{stack.active}
	stack.blockSize = s_DefaultCap
	stack.capacity = s_DefaultCap
	return stack
	// return &Stack { make([]interface{}, s_DefaultCap) }
}

func NewStackWithCapacity(cap int) *Stack {
	stack := new(Stack)
	stack.active = make([]interface{}, cap)
	stack.blocks = [][]interface{}{stack.active}
	stack.blockSize = cap
	stack.capacity = cap
	return stack
}
func (self *Stack) Peek() interface{} {
	if self.offset > 0 {
		return self.active[self.offset-1]
	} else {
		return self.blocks[(self.size-1)/self.blockSize][self.blockSize-1]
	}
}

func (self *Stack) Push(elem interface{}) {
	if self.size == self.capacity {
		self.active = make([]interface{}, self.blockSize)
		self.blocks = append(self.blocks, self.active)
		self.capacity += self.blockSize
		self.offset = 0
	}
	self.active[self.offset] = elem
	self.offset++
	self.size++
}

func (self *Stack) Pop() (interface{}, error) {
	if self.size == 0 {
		return nil, errors.New("empty stack")
	}
	self.size--
	self.offset--
	if self.offset < 0 {
		self.offset = self.blockSize - 1
		self.active, self.blocks = self.blocks[len(self.blocks)-2], self.blocks[:len(self.blocks)-1]
		self.capacity -= self.blockSize
	}
	elem := self.active[self.offset]
	return elem, nil
}

func (self *Stack) Empty() bool {
	return self.size == 0
}
