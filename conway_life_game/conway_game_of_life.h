#ifndef CONWAY_GAME_OF_LIFE_H_65634F7D_43D5_4EBB_9CC3_79B75B997B58
#define CONWAY_GAME_OF_LIFE_H_65634F7D_43D5_4EBB_9CC3_79B75B997B58

#include "multiarray.h"
#include <iostream>
class Field {
  public:
    Field(const int h, const int w) 
      : states_(static_cast<unsigned int>(h), static_cast<unsigned int>(w))
    , width_(w),height_(h)
    {}
      
    void set(int x, int y, bool state) {
      states_(y, x) = state;
    }

    bool isAlive(int x, int y) {
      x = (x+width_)%width_; 
      y = (y+height_)%height_;
      return states_(y, x);
    }

    bool nextStep(int x, int y);
  private:
    //std::vector<std::vector<bool>> s;
    MultiArray<bool,2> states_;
    int width_;
    int height_;
};

#include <random>
class RandInt {
  public:
    RandInt(int lo, int hi)
    : r(std::bind(std::uniform_int_distribution<>{lo, hi-1}, std::default_random_engine{})) {}
    int operator()() const { return r(); }

  private:
    std::function<int()> r;
};
class Life {
  public:
    Life(const int h, const int w)
      : height_(h), width_(w) {}
    ~Life() {
      delete currField_;
      delete nextField_;
    }
    void createLife(const std::vector<std::pair<int,int>>& field_points);
    void step();

    friend std::ostream& operator<<(std::ostream& s, const Life& f);
  private:
    Field* currField_;
    Field* nextField_;
    int height_;
    int width_;
};

#endif /* CONWAY_GAME_OF_LIFE_H_65634F7D_43D5_4EBB_9CC3_79B75B997B58 */
