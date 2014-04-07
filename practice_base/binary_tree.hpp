#ifndef BINARY_TREE_HPP_8906E665_F096_45BF_A214_DD59CAB96982
#define BINARY_TREE_HPP_8906E665_F096_45BF_A214_DD59CAB96982

#include <iostream>
#include <iomanip> // std::setw
#include <algorithm>
#include <queue>
#include <deque>
#include <random>
#include <assert.h>
template<typename T> struct ValuePrinter {};
template<> struct ValuePrinter<int> {
  std::string operator()(const int val) {
    std::string output;
    int dividend = val;
    int remain = 0;
    do {
      remain = dividend%10;
      dividend = dividend/10;
      output += char('0'+remain);
    }while(dividend != 0);
    output += '\0';
    std::reverse(output.begin(), output.end());
    return output;
  }
};
template<typename T>
struct BSTreeNode {
  T value_;
  BSTreeNode* pLeftNode_;
  BSTreeNode* pRightNode_;
};

template<typename T>
class BSTree {
  public:
    BSTree()
      :pRoot_(nullptr) {}

    ~BSTree() {
      destructorHelper(pRoot_);
    }

    BSTreeNode<T>** getRootPtr() {
      return &pRoot_;
    }
    BSTreeNode<T>* getRootNode() const {
      return pRoot_;
    }

    void createTree(const std::vector<T>& vals, const int start, const int end) {
      createTreeHelper(pRoot_, vals, start, end);
    }

    int maxHeight() const {
      //http://www.cnblogs.com/tanghulu321/archive/2013/04/30/3051746.html
      //http://stackoverflow.com/questions/19886297/finding-max-depth-of-binary-tree-without-recursion
      //http://leetcode.com/2010/04/maximum-height-of-binary-tree.html
      if (pRoot_ == nullptr) {
        return 0;
      }
      std::queue<BSTreeNode<T>*> q;
      q.push(pRoot_);
      int count = q.size();
      int  maxDepth = 0;
      while (!q.empty() ) {
        --count;
        if (count == 0) {
          ++maxDepth;
        }
        BSTreeNode<T>* top = q.front();
        q.pop();
        if (top->pLeftNode_) {
          q.push(top->pLeftNode_);
        }
        if (top->pRightNode_) {
          q.push(top->pRightNode_);
        }
        if (count == 0) {
          count = q.size();
        }
      }
      return maxDepth;
    }

    // Pretty formatting of a binary tree to the output stream
    void printLevelNodePretty() const {
      //http://leetcode.com/2010/09/how-to-pretty-print-binary-tree.html
      //http://leetcode.com/2010/09/printing-binary-tree-in-level-order.html
      int h = maxHeight();
      int nodesInThisLevel = 1;
      int indentSpace = 2;//indentSpace of 0 means the lowest level of the left node will stick to the left margin
      int branchLen = (int)pow(2.0, h) - 2;//the length of branch for each node of each level
      int nodeSpaceLen = 2 + (int)pow(2.0, h+1);//distance between left neighbor node's right arm and right neighbor node's left arm
      int startLen = branchLen + indentSpace + 2;// starting space to the first node to print of each level (for the left most node of each level only)
      std::deque<BSTreeNode<T>*> nodeQ;
      nodeQ.push_back(pRoot_);
      for (int i = 1; i < h; ++i) {
        printBranches(nodesInThisLevel, branchLen, nodeSpaceLen, startLen, nodeQ);
        branchLen = branchLen/2 - 1;
        nodeSpaceLen = nodeSpaceLen/2 + 1;
        startLen = branchLen + indentSpace + 2;
        printNodes(nodesInThisLevel, branchLen, nodeSpaceLen, startLen, nodeQ);
        for (int j = 0; j < nodesInThisLevel; ++j) {
          BSTreeNode<T>* p = nodeQ.front();
          nodeQ.pop_front();
          if (p) {
            nodeQ.push_back(p->pLeftNode_);
            nodeQ.push_back(p->pRightNode_);
          }
          else {
            nodeQ.push_back(nullptr);
            nodeQ.push_back(nullptr);
          }
        }
        nodesInThisLevel *= 2;
      }
      printBranches(nodesInThisLevel, branchLen, nodeSpaceLen, startLen, nodeQ);
      printLeaves(nodesInThisLevel, indentSpace, nodeQ);
    }

  private:
    void createTreeHelper(BSTreeNode<T>*& ppTreeNode, const std::vector<T>& vals, const int start, const int end) {
      //http://leetcode.com/2010/11/convert-sorted-array-into-balanced.html
      //http://leetcode.com/2010/11/convert-sorted-list-to-balanced-binary.html
      if (start > end) {
        return;
      }
      int mid = start + ((end - start) >> 1);
      ppTreeNode = new BSTreeNode<T>();
      ppTreeNode->value_ = vals[mid];
      createTreeHelper(ppTreeNode->pLeftNode_, vals, start, mid - 1);
      createTreeHelper(ppTreeNode->pRightNode_, vals, mid+1, end);
    }

    // Print the arm branches (eg, /    \ ) on a line
    void printBranches(int nodesInThisLevel, int branchLen, int nodeSpaceLen, int startLen, const std::deque<BSTreeNode<T>*>& nodesQueue) const {
      typename std::deque<BSTreeNode<T>*>::const_iterator iter = nodesQueue.begin();
      for (int i = 0; i < nodesInThisLevel>>1; i++) {
        std::cout << ((i == 0) ? std::setw(startLen-1) : std::setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
        std::cout << std::setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
      }
      std::cout << std::endl;
    }
     
    // Print the branches and node (eg, ___10___ )
    void printNodes(int nodesInThisLevel, int branchLen, int nodeSpaceLen, int startLen, const std::deque<BSTreeNode<T>*>& nodesQueue) const {
      typename std::deque<BSTreeNode<T>*>::const_iterator iter = nodesQueue.begin();
      for (int i = 0; i < nodesInThisLevel; i++, iter++) {
        std::cout << ((i == 0) ? std::setw(startLen) : std::setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->pLeftNode_) ? std::setfill('_') : std::setfill(' '));
        std::cout << std::setw(branchLen+2) << ((*iter) ? ValuePrinter<T>()((*iter)->value_) : "");
        std::cout << ((*iter && (*iter)->pRightNode_) ? std::setfill('_') : std::setfill(' ')) << std::setw(branchLen) << "" << std::setfill(' ');
      }
      std::cout << std::endl;
    }
     
    // Print the leaves only (just for the bottom row)
    void printLeaves(int nodesInThisLevel, int indentSpace, const std::deque<BSTreeNode<T>*>& nodesQueue) const {
      typename std::deque<BSTreeNode<T>*>::const_iterator iter = nodesQueue.begin();
      for (int i = 0; i < nodesInThisLevel; i++, iter++) {
        std::cout << ((i == 0) ? std::setw(indentSpace+2) : std::setw(4)) << ((*iter) ? ValuePrinter<T>()((*iter)->value_) : "");
      }
      std::cout << std::endl;
    }

    void destructorHelper(BSTreeNode<T>* pNode) {
      if (pNode == nullptr) {
        return;
      }
      destructorHelper(pNode->pLeftNode_);
      destructorHelper(pNode->pRightNode_); 
      delete pNode;
      pNode = nullptr;
    }
  private:
    BSTreeNode<T>* pRoot_;
};

void createIntegerNodes(BSTree<int>& tree, const int nodeNum) {
  std::default_random_engine gen((std::random_device())() );
  //std::uniform_int_distribution<int> dis(0, 10000);
  std::uniform_int_distribution<int> dis(10, 99);
  std::vector<int> nodeValues;
  nodeValues.reserve(nodeNum);
//  nodeValues.resize(nodeNum);
  for (int i = 0; i < nodeNum; ++i) {
//    nodeValues[i] = dis(gen);
    nodeValues.push_back(dis(gen));
  }
  std::sort(nodeValues.begin(), nodeValues.end(), std::less<int>() );
  tree.createTree(nodeValues, 0, nodeNum-1);
}
#endif /* BINARY_TREE_HPP_8906E665_F096_45BF_A214_DD59CAB96982 */
