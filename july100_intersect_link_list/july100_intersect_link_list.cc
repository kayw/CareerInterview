
#include "igloo/igloo_alt.h"
using namespace igloo;
#if 0
http://blog.csdn.net/liuxialong/article/details/6556096  (3.2 method isn't right)

TODO: find the intersect node (acyclic or cyclic)
https://www.google.com.hk/search?q=linkedlist+intersect

http://www.cnblogs.com/Griffin/archive/2012/11/16/2772532.html (very messy seems to haven't talked about cyclic intersect)
http://blog.csdn.net/hackbuteer1/article/details/7583102 (acyclic intersect problem)
#endif

template<class T>
struct LinkListNode{
  T value_;
  LinkListNode* nextPtr_;
};

template<class T>
LinkListNode<T>* findCyclicMeetingNode(LinkListNode<T>* headerPtr) {
  LinkListNode<T>* p1 = headerPtr;
  LinkListNode<T>* p2 = headerPtr;
  while (p2 && p2->nextPtr_) {
    p1 = p1->nextPtr_;
    p2 = p2->nextPtr_->nextPtr_;
    if (p1 == p2) {
      return p1;
    }
  }
  return nullptr;
}

template<class T>
LinkListNode<T>* findCyclicStartNode(LinkListNode<T>* headerPtr) {
  LinkListNode<T>* meetingNodePtr = findCyclicMeetingNode(headerPtr);
  // no meeting point, so ther's no loop
  if (!meetingNodePtr || !meetingNodePtr->nextPtr_) {
    return nullptr;
  }
  // headptr and meetingptr are all k steps from the loop start.
  // if they move at the same pace,they'll meet at loop start.
  auto loopStartPtr = headerPtr;
  while(loopStartPtr != meetingNodePtr) {
    loopStartPtr = loopStartPtr->nextPtr_;
    meetingNodePtr = meetingNodePtr->nextPtr_;
  }
  return loopStartPtr;
}

/*
 * A -> B
 *      |
 *      v
 *      C -> D -> E
 *      ^
 *      |
 * F -> G 
 * plot copy from:http://stackoverflow.com/questions/7322379/how-to-find-if-two-linked-list-intersect-each-other
 */
template<class T>
bool isACyclicJoined(LinkListNode<T>* h1, LinkListNode<T>* h2) {
  while(h1 && h1->nextPtr_) {
    h1 = h1->nextPtr_;
  }
  while(h2 && h2->nextPtr_) {
    h2 = h2->nextPtr_;
  }
  return h1 == h2;
}

template<class T>
bool isJoined(LinkListNode<T>* h1, LinkListNode<T>* h2) {
  LinkListNode<T>* p1 = findCyclicMeetingNode(h1);
  LinkListNode<T>* p2 = findCyclicMeetingNode(h2);
  if (!p1 && !p2) {
    return isACyclicJoined(p1, p2);
  }
  if ((p1 && !p2) || (!p1 && p2) ) {
    return false;
  }
  LinkListNode<T>* p = p1;
  while(true) {
    if (p == p2 || p->nextPtr_ == p2) {
      return true;
    }
    p = p->nextPtr_->nextPtr_;
    p1 = p1->nextPtr_;
    if (p == p1) {
      return false;
    }
  }
}

//http://www.geeksforgeeks.org/write-a-function-to-get-the-intersection-point-of-two-linked-lists/
//test data

Describe(IsJoinedLinkList) {
  It(Y_link) {
    LinkListNode<int> node1;
    node1.value_ = 1;
    LinkListNode<int> node2;
    node2.value_ = 2;
    LinkListNode<int> node3;
    node3.value_ = 3;
    LinkListNode<int> node4;
    node4.value_ = 4;
    LinkListNode<int> node5;
    node5.value_ = 5;

    LinkListNode<int> node6;
    node6.value_ = 6;
    LinkListNode<int> node7;
    node7.value_ = 7;
    //root1
    node1.nextPtr_ = &node2;
    node2.nextPtr_ = &node3;
    node3.nextPtr_ = &node4;
    node4.nextPtr_ = &node5;
    node5.nextPtr_ = nullptr;

    //root2
    node6.nextPtr_ = &node7;
    node7.nextPtr_ = &node4;
    bool rv = isJoined(&node1, &node6);
    AssertThat(rv, IsTrue() );
  }
  //todo more testdata
};

int main(int argc, char *argv[]) {
  return TestRunner::RunAllTests(argc, argv);
}
