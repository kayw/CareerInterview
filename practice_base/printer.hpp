#include <iostream>
template<typename T>
void printArray(T a[]) {
  int sizet = sizeof(a)/sizeof(T);
  for (int i = 0; i < sizet; ++i) {
    std::cout << a[i];
  }
  std::cout << std::endl;
}
