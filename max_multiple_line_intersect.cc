//http://blog.sina.com.cn/s/blog_6be26cc701012cc8.html
#include <stdio.h>
#include <algorithm>
#include <vector>

struct Line {
  int x1;//beginPos
  int x2;//endPos
};

struct LinePosPred {
  bool operator()(const Line& lhs, const Line& rhs) const {
    if (lhs.x1 != rhs.x1) {
      return lhs.x1 < rhs.x1;
    }
    else {
      return lhs.x2 < rhs.x2;
    }
  }
};

int getMaxRange(const std::vector<Line>& lines) {
  auto pivot = lines.begin();
  //std::vector<Line>::const_iterator pivot = lines.begin();
  auto lineIter = lines.begin();
  //std::vector<Line>::const_iterator lineIter = lines.begin();
  int maxRange = 0;
  for (++lineIter; lineIter != lines.end(); ++lineIter) {
    if (lineIter->x1 > pivot->x2) { //intersect 0
      //maxRange = std::max(maxRange, lineIter->x1 - pivot->x2);
      pivot = lineIter; 
    }
    else if (lineIter->x2 > pivot->x2) {
      maxRange = std::max(maxRange, -lineIter->x1 + pivot->x2);
      pivot = lineIter; 
    }
    else {
      maxRange = std::max(maxRange, lineIter->x2 - lineIter->x1);
    }
  }
  return maxRange;
}

int main(int /*argc*/, char */*argv*/[]) {
  std::vector<Line> lines;
  Line l;
  l.x1 = 2;
  l.x2 = 8;
  lines.push_back(l);
  l.x1 = -9;
  l.x2 = -6;
  lines.push_back(l);
  l.x1 = 9;
  l.x2 = 10;
  lines.push_back(l);
  l.x1 = 4;
  l.x2 = 10;
  lines.push_back(l);
  std::sort(lines.begin(), lines.end(), LinePosPred() );
  printf("the maxium range between lines is %d\n", getMaxRange(lines) );
  return 0;
}
