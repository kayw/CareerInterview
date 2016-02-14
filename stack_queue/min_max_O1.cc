//http://articles.leetcode.com/2010/11/stack-that-supports-push-pop-and-getmin.html  likewise min max queue 
//http://stackoverflow.com/questions/7134129/stack-with-find-min-find-max-more-efficient-than-on
#include <stdio.h>
#include <iostream>
#include <queue>
template<typename T, int N=4096>
class Stack{
  public:
    Stack()
     : stackTop_(-1) {}

    bool push(const T& t) {
      bool rv = false;
      if (stackTop_ != N) {//if (stackTop_ + 1 < N) {
        stackBuffer_[++stackTop_] = t;
        rv = true;
      }
      else {
        printf("exceed stack limit\n");
      }
      return rv;
    }
    T pop() {
      if (stackTop_ >= 0) {
        return stackBuffer_[--stackTop_];
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
    bool empty() const {
      return stackTop_ == -1;
    }

  private:
    int stackTop_;
    T stackBuffer_[N];
};

template<typename T, int N=4096>
class StackWithMinMax {
  public:
    StackWithMinMax() {}  //todo initializer list {1,3,4,5,2}
    void push(const T& t) {
      if (valueStack_.push(t) ) {
        if (minStack_.empty() || t <= min()) {
          minStack_.push(t);
        }
        if (maxStack_.empty() || t >= max()) {
          maxStack_.push(t);
        }
      }
    }
    T pop() {
      if (valueStack_.empty()) {
        return T();
      }
      T poped = valueStack_.pop();
      if (poped == min()) {
        minStack_.pop();
      }
      if (poped == max()) {
        maxStack_.pop();
      }
      return poped;
    }
    T min() const {
      return minStack_.top();
    }
    T max() const {
      return maxStack_.top();
    }

  private:
    Stack<T, N> valueStack_;
    Stack<T, N> minStack_;
    Stack<T, N> maxStack_;
#if 0
    int stackTop_;
    int minStackTop_;
    T stack_[N];
    T minStack_[N];
#endif
};

//http://stackoverflow.com/questions/4802038/implement-a-queue-in-which-push-rear-pop-front-and-get-min-are-all-consta Cartesian tree todo read
//another way using two stackmin move all element to another in pop
template<typename T>
class QueueWithMin {
  public:
    void pushRear(T elem) {
      values_.push(elem);
      while (!minQueue_.empty() && elem < minQueue_.back()){
        minQueue_.pop_back();
      }
      minQueue_.push_back(elem);
    }
    void popFront() {
      if (values_.front() == minQueue_.front()) {
        minQueue_.pop_front();
      }
      values_.pop();
    }
    T getMin() {
      return minQueue_.front();
    }
  private:
    std::queue<T> values_;
    std::deque<T> minQueue_;
};

int main(void)
{
  StackWithMinMax<int> smm;
  smm.push(3);
  smm.push(1);
  smm.push(4);
  smm.push(1);
  smm.push(2);
  smm.pop();
  std::cout << "stack min wants 1, get " << smm.min() << std::endl;
  std::cout << "stack max wants 4, get " << smm.max() << std::endl;

  QueueWithMin<int> qm;
  qm.pushRear(4);
  qm.pushRear(0);
  qm.pushRear(1);
  qm.pushRear(2);
  qm.pushRear(1);
  qm.popFront();
  qm.popFront();
  std::cout << "queue min wants 1, get " << qm.getMin() << std::endl;
  return 0;
}
