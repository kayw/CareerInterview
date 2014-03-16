#include <stdio.h>
template<typename T, int N=4096>
class Stack{
  public:
    Stack()
     : stackTop_(0) {}

    bool push(const T& t) {
      bool rv = false;
      if (stackTop_ != N) {//if (stackTop_ + 1 < N) {
        stackBuffer_[stackTop_++] = t;
        rv = true;
      }
      else {
        printf("exceed stack limit\n");
      }
      return rv;
    }
    T pop() {
      if (stackTop_ >= 0) {
        return stackBuffer_[stackTop_--];
      }
      else {
        return T();
      }
    }
    T top() const {
      if (stackTop_ >= 0) {
        return stackBuffer_[stackTop_];
      }
      else {
        return T();
      }
    }

  private:
    int stackTop_;
    T stackBuffer_[N];
};

template<typename T, int N=4096>
class StackWithMin {
  public:
    StackWithMin() {}
    void push(const T& t) {
      if (valueStack_.push(t) ) {
        if (t < min() ) {
          minStack_.push(t);
        }
      }
    }
    T pop() {
      T poped = valueStack_.pop();
      if (poped == minStack_.top() ) {
        minStack_.pop();
      }
    }
    T min() {
      return minStack_.top();
    }

  private:
    Stack<T, N> valueStack_;
    Stack<T, N> minStack_;
#if 0
    int stackTop_;
    int minStackTop_;
    T stack_[N];
    T minStack_[N];
#endif
};
