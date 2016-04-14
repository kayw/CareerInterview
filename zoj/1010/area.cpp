//http://blog.csdn.net/glorywu/article/details/3635900
#include <iostream>
#include <vector>

struct Point {
  double x;
  double y;
};

bool multiply(const Point& a, const Point& b, const Point& c) {
   return (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x);
}

bool intersect(const Point a, const Point& b, const Point& c, const Point& d) {
      return std::max(a.x, b.x) >= std::min(c.x, d.x) &
        std::max(a.y, b.y) >= std::min(c.y, d.y) &
        std::max(c.x, d.x) >= std::min(a.x, b.x) &
        std::max(c.y, d.y) >= std::min(a.y, b.y) &
        multiply(a, d, c) * multiply(d, b, c) >= 0 &
        multiply(c, b, a) * multiply(b, d, a) >= 0;
}
int main(int /*argc*/, char */*argv*/[]) {
  int N = 0;
  int num = 0;
  while(std::cin >> N && N) {
    std::vector<Point> pts(N+1, Point() );
    for(int i = 0; i < N; ++i) {
      std::cin >> pts[i].x >> pts[i].y;
    }
    ++num;
    // there points parallel
    if (N == 1 || N == 2 || (N == 3 && (pts[2].y - pts[1].y)/(pts[2].x - pts[1].x)
          == (pts[2].y - pts[0].y) / (pts[2].x - pts[0].x) ) ) {
      std::cout << "Figure "<< num << ": Impossible" << std::endl << std::endl;
      continue;
    }
    std::cout << "Figure " << num << ": ";
    pts[N].x = pts[0].x;
    pts[N].y = pts[0].y;
    bool possible = true;
    for (int i = 0; i < N - 1; ++i)
    {
      for (int j = i+1; j < N; ++j)
      {
        if (i+1 != j && (i != 0 || j != N-1) && intersect(pts[i], pts[i+1], pts[j], pts[j+1]) ) {
          std::cout << "Impossible" << std::endl << std::endl;
          possible = false;
          break;
        }
      }
      if (!possible)
        break;
    }
    if (!possible)
      continue;
    double area = 0.0;
    for (int i = 1; i < N - 1; ++i)
    {
      area += 0.5*((pts[0].x - pts[i+1].x)*(pts[i].y - pts[i+1].y) - (pts[i].x - pts[i+1].x)*(pts[0].y - pts[i+1].y) );
    } 
    std::cout.setf(std::ios::fixed);
    std::cout.setf(std::ios_base::showpoint);
    std::cout.precision(2);
    std::cout<<(area>0?area:-area)<<std::endl << std::endl;
  }
  return 0;
}





//http://my384581169.blog.163.com/blog/static/139014454201031393626106/
