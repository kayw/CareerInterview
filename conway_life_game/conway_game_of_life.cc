//http://codereview.stackexchange.com/questions/42718/conways-game-of-life
#include <chrono>
#include <thread>
#include "conway_game_of_life.h"

bool Field::nextStep(int x, int y) {
  // Count the adjacent cells that are alive.
  int alive = 0;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if ((i != 0 ||j != 0) && isAlive(x+i, y+j)) {
        ++alive;
      }
    }
  }
  // Return next state according to the game rules:
  //   exactly 3 neighbors: on,
  //   exactly 2 neighbors: maintain current state,
  //   otherwise: off.
  return alive == 3 || (alive == 2 && isAlive(x,y));
}

void Life::createLife(const std::vector<std::pair<int,int>>& field_points) {
  currField_ = new Field(height_, width_);
  for(auto& fp : field_points) {
    currField_->set(fp.second, fp.first, true);
  }
  nextField_ = new Field(height_, width_);
}

void Life::step(){
// Step advances the game by one instant, recomputing and updating all cells.
  // Update the state of the next field (b) from the current field (a).
  for (int y = 0; y < height_; ++y) {
    for (int x = 0; x < width_; ++x) {
      nextField_->set(x, y, currField_->nextStep(x, y));
    }
  }
  // Swap fields a and b.
  std::swap(currField_, nextField_);
}

std::ostream& operator<<(std::ostream& s, const Life& f){
  for (int i = 0; i < f.height_; ++i) {
    for (int j = 0; j < f.width_; ++j) {
      if (f.currField_->isAlive(i,j)) {
        s << '*'; 
      }
      else{
        s << ' ';
      }
    }
    s << std::endl;
  }
  for (int j = 0; j < f.width_; ++j) {
    s << '-';
  }
  s << std::endl;
  return s;
}

int main(int /*argc*/, char */*argv*/[]) {
  std::vector<std::pair<int,int>> vp;
#ifdef BLINKER_LIFE
  Life blinker(5,5);
  vp.push_back(std::make_pair(2,1));
  vp.push_back(std::make_pair(2,2));
  vp.push_back(std::make_pair(2,3));
  blinker.createLife(vp);
  for (int i = 0; i < 5; ++i) {
    std::cout << blinker; 
    blinker.step();
		//http://stackoverflow.com/questions/5801813/c-usleep-is-obsolete-workarounds-for-windows-mingw
		std::this_thread::sleep_for(std::chrono::microseconds(100000));
  }
#endif
  vp.clear();
  int width = 15;
  int height = 40;
  Life l(width, height);

  std::default_random_engine gen;//((std::random_device() )() );
  std::uniform_int_distribution<int> disW(0, width-1);
  std::uniform_int_distribution<int> disH(0, height-1);
#if 0
  RandInt widthdist{0, width};
  RandInt heightdist(0, height);
#endif
  for (int i = 0; i < (height*width)/4; ++i) {
    //vp.push_back(std::make_pair(widthdist(), heightdist()));
    vp.push_back(std::make_pair(disW(gen), disH(gen)));
  }
  l.createLife(vp);
  for (int i = 0; i < 40; ++i) {
    l.step();
    std::cout << l; 
		//http://stackoverflow.com/questions/5801813/c-usleep-is-obsolete-workarounds-for-windows-mingw
		std::this_thread::sleep_for(std::chrono::microseconds(100000));
  }
  return 0;
}
//http://www.janwillemtulp.com/2011/03/22/tutorial-conways-game-of-life-in-d3/
