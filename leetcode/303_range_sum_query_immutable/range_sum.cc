#include <vector>
class NumArray {
  public:
    NumArray(std::vector<int> &nums) {
      int sum = 0;
      //for(int num : nums) {
      for(std::vector<int>::iterator num = nums.begin(); num != nums.end(); num++) {
        sum += *num;
        sums_.push_back(sum);
      }
    }

    int sumRange(int i, int j) {
      if (i < 0 || i > j || j > sums_.size()) {
        return 0;
      }
      int subtractor = 0;
      if (i > 0) {
        subtractor = sums_[i-1];
      }
      return sums_[j] - subtractor;
    }

  private:
    std::vector<int> sums_;
};
