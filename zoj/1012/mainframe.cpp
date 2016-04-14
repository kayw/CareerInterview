//http://blog.csdn.net/glorywu/article/details/3666983
#include <iostream>
#include <algorithm>
#include <vector>

struct Job {
  int cpus;
  int memoryUsage;
  int arriveTime;
  int timeline;
  int value;
  int bonus;
  int punishment;
  int executeTime;
  int executedFlag;// -1 finished 0 running 1 waiting
};

struct TimeValuePred {
  bool operator()(const Job& lhs, const Job& rhs) const {
    if (lhs.arriveTime != rhs.arriveTime) {
      //take precedence prior to
      //earlier job sort before or prevail
      return lhs.arriveTime < rhs.arriveTime;
    }
    else {
      //larger value prevail
      return lhs.value > rhs.value;
    }
  }
};

int main(int /*argc*/, char */*argv*/[]) {
  int F = 0;
  int N = 0;
  int M = 0;
  int J = 0;
  int casenum = 0;
  while(std::cin >> F && F) {
    std::cin >> M;// total cpus;
    std::cin >> N;// total memory;
    std::cin >> J;// total jobs;
    std::vector<Job> startTimeJobs;
    for (int i = 0; i < J; ++i) {
      Job j;
      std::cin >> j.cpus;
      std::cin >> j.memoryUsage;
      std::cin >> j.arriveTime;
      std::cin >> j.timeline;
      std::cin >> j.value;
      std::cin >> j.bonus;
      std::cin >> j.punishment;
      j.executedFlag = 1;
      startTimeJobs.push_back(j);
    }
    std::sort(startTimeJobs.begin(), startTimeJobs.end(), TimeValuePred() );
    for (int tl = 0; tl <= F; ++tl) {
      // current running jobs found & free cpu and memory
      for (int j = 0; j < J; ++j) {
        if (startTimeJobs[j].executedFlag == 0 && startTimeJobs[j].executeTime + 1 == tl) {
          M += startTimeJobs[j].cpus;
          N += startTimeJobs[j].memoryUsage;
          startTimeJobs[j].executedFlag = -1;
        }
      }
      // non-executed jobs to be filled
      for (int j = 0; j < J; ++j) {
        if (startTimeJobs[j].arriveTime > tl)
          break;
        if (startTimeJobs[j].executedFlag == 1 && startTimeJobs[j].cpus <= M && startTimeJobs[j].memoryUsage <= N) {
          M -= startTimeJobs[j].cpus;
          N -= startTimeJobs[j].memoryUsage;
          startTimeJobs[j].executedFlag = 0;
          startTimeJobs[j].executeTime = tl;
        }
      }
    } 
    // calculate jobs' income
    int income = 0;
    for (int i = 0; i < J; ++i) {
      //executed
      if (startTimeJobs[i].executedFlag == -1) {
        int extraFreeTime = -(startTimeJobs[i].executeTime + 1) + startTimeJobs[i].timeline;
        income += startTimeJobs[i].value + extraFreeTime*((extraFreeTime > 0) ? startTimeJobs[i].bonus : startTimeJobs[i].punishment);
      }
      //current running or waiting
      else {
        if (startTimeJobs[i].timeline < F) {
          income -= (F - startTimeJobs[i].timeline) * startTimeJobs[i].punishment;
        }
      }
    }
#if 0
    //http://stackoverflow.com/questions/5122804/sorting-with-lambda
    for(auto& kv : startTimeJobs) {
    //http://stackoverflow.com/questions/6963894/c11-how-to-use-range-based-for-loop-with-stdmap
      std::sort(kv.second.begin(),  kv.second.end(), 
        [](const Job& lhs, const Job& rhs) {
          return lhs.value > rhs.value;
          });
    }
#endif
    std::cout << "Case " << ++casenum << ": " << income << std::endl << std::endl;
  }
  return 0;
}


//http://blog.sina.com.cn/s/blog_5ced353d0100b8k9.html
//http://hi.baidu.com/hfnhzpe/item/5a041751de8619908d12ed31
