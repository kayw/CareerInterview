#include <stdio.h>
template<class T>
struct LinkList {
  T data_;
  LinkList* pNext_;
};
//http://leetcode.com/2010/04/reversing-linked-list-iteratively-and.html
template<typename T>
void reverseSingleLinkedList(LinkList<T>*& pRoot) {
  if (!pRoot)
    return;
  LinkList<T>* pPrev = NULL;
  LinkList<T>* pCurr = pRoot;
  while(pCurr) {
    LinkList<T>* pNext = pCurr->pNext_;
    pCurr->pNext_ = pPrev;
    pPrev = pCurr;
    pCurr = pNext;
  }
  pRoot = pPrev;
}

template<typename T>
void reverseRecursive(LinkList<T>*& pRoot) {
  if (!pRoot) {
    return;
  }
  LinkList<T>* pRest = pRoot->pNext_;
  if (!pRest) {
    return;
  }
  reverseRecursive(pRest);
  pRoot->pNext_->pNext_ = pRoot;
  pRoot->pNext_ = NULL;
  pRoot = pRest;
}

int main(int /*argc*/, char */*argv*/[]) {
  printf("Link List before reverse:\n");
  LinkList<int> L;
  L.data_ = 20;
  printf("%d ", 20);
  LinkList<int>* pRoot = &L;
  for (int i = 0; i < 5; ++i) {
    LinkList<int>* l = new LinkList<int>;
    l->data_ = i + 1;
    l->pNext_ = NULL;
    pRoot->pNext_ = l;
    pRoot = l;
    printf("%d ", i+1);
  }
  printf("\n");
  pRoot = &L;
  reverseSingleLinkedList(pRoot);
  printf("after reverse:\n");
  LinkList<int>* pCur = pRoot;
  while(pCur) {
    printf("%d ", pCur->data_);
    pCur = pCur->pNext_;
  }
  printf("\n");
  reverseRecursive(pRoot);
  printf("after another reverse:\n");
  pCur = pRoot;
  while(pCur) {
    printf("%d ", pCur->data_);
    pCur = pCur->pNext_;
  }
  return 0;
}
