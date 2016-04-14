#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

//http://blog.sina.com.cn/s/blog_5ced353d0100b84s.html
struct TreeSignals {
  int left;
  int right;
  TreeSignals() 
    :left(-1), right(-1) {}
};

bool traverseTree(const std::vector<int>& acceptSignals, const std::string& tree, std::vector<TreeSignals> transTable[15][10], int transmitterPos, int signalPos) {
  //http://fantasyorg.blog.163.com/blog/static/1092761092009219111854551/
  //isAccept(x) => signals - acceptSignalNum <= x
  if (2*transmitterPos + 1 >= tree.length() || (tree[2*transmitterPos + 1] == '*' && tree[2*transmitterPos+2] == '*' ) ) {
    for(auto ts : transTable[signalPos][tree[transmitterPos] - 'a']) {
      //http://stackoverflow.com/questions/571394/how-to-find-an-item-in-a-stdvector
      if (std::find(acceptSignals.begin(), acceptSignals.end(), ts.left) != acceptSignals.end() &&
         std::find(acceptSignals.begin(), acceptSignals.end(), ts.right) != acceptSignals.end() )
        return true;
    }
    return false;
  }
  for(auto ts :  transTable[signalPos][tree[transmitterPos] - 'a']) {
    bool acceptleft = traverseTree(acceptSignals, tree, transTable, 2*transmitterPos + 1, ts.left);
    bool acceptright = traverseTree(acceptSignals, tree, transTable, 2*transmitterPos + 2, ts.right);
    if (acceptleft && acceptright) {
      return true;
    }
  }
  return false;
}  

int main() {
  int signals = 0;
  int acceptSignalNum = 0;
  int signalTransNum = 0;
  int casenum = 0;
  while((std::cin >> signals >> acceptSignalNum >> signalTransNum) && (signals || acceptSignalNum || signalTransNum) ) {
    std::vector<TreeSignals> transTable[15][10];
    //int tableLen = signals * signalTransNum;
    //http://www.cplusplus.com/forum/beginner/76273/
    //http://www.cplusplus.com/forum/beginner/92979/
    std::cin.ignore();
    //http://stackoverflow.com/questions/9673708/tell-cin-to-stop-reading-at-newline
    //for (int i = 0; i < tableLen; ++i)
    for (int i = 0; i < signals; ++i)
    {
      for (int j = 0; j < signalTransNum; ++j)
      {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        TreeSignals ts;
       // int row = i/signals;
       // int column = i%signalTransNum;
        while(iss >> ts.left >> ts.right) {
          transTable[i][j].push_back(ts);
        }
      }
    }
    int treeDepth = 0;
    std::vector<std::string> trees;
    while(std::cin >> treeDepth && treeDepth != -1) {
      int treeNodeNum = (1 << (treeDepth + 1)) - 1;
      std::string tree;
      for (int i = 0; i < treeNodeNum; ++i)
      {
        char ch;
        std::cin >> ch;
        tree += ch;
      }
      trees.push_back(tree);
    }
    std::vector<int> acceptSignals;
    for (int i = 0; i < acceptSignalNum; ++i)
    {
      acceptSignals.push_back(signals - i - 1);
    }
    if(casenum++) std::cout << std::endl;
    std::cout << "NTA" << casenum <<":" << std::endl;
    for(auto tree : trees) {
      if (traverseTree(acceptSignals, tree, transTable, 0, 0) )
        std::cout << "Valid" << std::endl;
      else 
        std::cout << "Invalid" << std::endl;
    }

  }
}
