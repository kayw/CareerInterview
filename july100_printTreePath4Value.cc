#include "practice_base/binary_tree.hpp"

#include <math.h>

#define MAX_TREE_HEIGHT 20

void printTreePathHelper(BSTreeNode<int>& root, int& sum, int (&path)[MAX_TREE_HEIGHT], int top) {
  path[top++] = root.value_;
  sum -= root.value_;
  if (root.pLeftNode_ == nullptr && root.pRightNode_ == nullptr) {
    if (sum == 0) {
      for(int i = 0; i < top; ++i)
        std::cout << path[i] << " ";
    }
  }
  else {
    if (root.pLeftNode_ != nullptr) {
      printTreePathHelper(*root.pLeftNode_, sum, path, top);
    }
    if (root.pRightNode_ != nullptr) {
      printTreePathHelper(*root.pRightNode_, sum, path, top);
    }
  }
  --top;
  sum += root.value_;
}

void printTreePath(BSTreeNode<int>& root, int sum) {
  int path[MAX_TREE_HEIGHT] = {};
  printTreePathHelper(root, sum, path, 0);
}

int main(int /*argc*/, char */*argv*/[]) {
  BSTree<int> tree;
  createIntegerNodes(tree, 9);
  tree.printLevelNodePretty();
  int sum = tree.getRootNode()->value_;
  BSTreeNode<int>* pNode = tree.getRootNode();
  for (; ;) { 
    if (pNode->pLeftNode_ == nullptr && pNode->pRightNode_ == nullptr) {
      break;
    }
    if (pNode->pLeftNode_ != nullptr) { 
     sum += pNode->pLeftNode_->value_;
     pNode = pNode->pLeftNode_;
    }
    if (pNode->pRightNode_ != nullptr) {
      sum += pNode->pRightNode_->value_;
      pNode = pNode->pRightNode_;
    }
  }
  printTreePath(*tree.getRootNode(), sum);
  return 0;
}
