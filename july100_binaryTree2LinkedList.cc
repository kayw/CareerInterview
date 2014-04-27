#include "practice_base/binary_tree.hpp"
template<typename T>
void binaryTreeToLinkedList(BSTreeNode<T>*& pRoot, BSTreeNode<T>*& pHeadNode, BSTreeNode<T>*& pTailNode) {
  BSTreeNode<T>* leftSubTreeTail = nullptr;
  BSTreeNode<T>* rightSubTreeHead = nullptr;
  if (pRoot == nullptr) {
    pHeadNode = nullptr;
    pTailNode = nullptr;
    return;
  }
  binaryTreeToLinkedList(pRoot->pLeftNode_, pHeadNode, leftSubTreeTail);
  binaryTreeToLinkedList(pRoot->pRightNode_, rightSubTreeHead, pTailNode);
  if (leftSubTreeTail != nullptr) {
    leftSubTreeTail->pRightNode_ = pRoot;
    pRoot->pLeftNode_ = leftSubTreeTail;
  }
  else {
    pHeadNode = pRoot;
  }
  if (rightSubTreeHead != nullptr) {
    rightSubTreeHead->pLeftNode_ = pRoot;
    pRoot->pRightNode_ = rightSubTreeHead;
  }
  else {
    pTailNode = pRoot;
  }
}

int main(int /*argc*/, char */*argv*/[]) {
  BSTree<int> bst;
  createIntegerNodes(bst, 7);
  bst.printLevelNodePretty();

  std::unique_ptr<BSTreeNode<int>> newRoot(new BSTreeNode<int>);
  newRoot = bst.clone(std::move(newRoot) );
  BSTreeNode<int>* newRootPtr = newRoot.get();

  BSTreeNode<int>* pHead = nullptr;
  BSTreeNode<int>* pTail = nullptr;
  //binaryTreeToLinkedList(*(bst.getRootPtr()), pHead, pTail);
  binaryTreeToLinkedList(newRootPtr, pHead, pTail);
  while(pHead) {
    std::cout << int(pHead->value_) << "  ";
    pHead = pHead->pRightNode_;
  }
#if 0
  while(pTail != newRootPtr) {
    BSTreeNode<int>* tmpPtr = pTail->pLeftNode_;
    delete pTail;
    pTail = tmpPtr;
  }
#endif
  //http://stackoverflow.com/questions/2265967/writing-a-linkedlist-destructor
  pHead = newRootPtr ? newRootPtr->pRightNode_ : nullptr;
  while(pHead) {
    auto nextPtr = pHead->pRightNode_;
    delete pHead;
    pHead = nextPtr;
  }

  std::cout << std::endl;
  return 0;
}
