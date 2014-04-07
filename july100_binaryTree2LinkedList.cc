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
  BSTreeNode<int>* pHead = nullptr;
  BSTreeNode<int>* pTail = nullptr;
#if 0
  binaryTreeToLinkedList(*(bst.getRootPtr()), pHead, pTail);
  while(pHead) {
    std::cout << int(pHead->value_) << "  ";
    pHead = pHead->pRightNode_;
  }
  std::cout << std::endl;
#endif
  return 0;
}
