//https://gist.github.com/988699
//#if 0
#include<stdio.h>

#define BOWLS 40
#define ORANGES 9


int count = 0;
// All the places in which an orange can't be placed are 1's
int used[BOWLS];
// // A list of the oranges already placed.
int oranges[ORANGES];

int turn;
int y;
int tmp_index;

void check(int x) {
    if (turn == ORANGES) {
        ++count;
        return;
    }

    for(; x < BOWLS; ++x) {
        // Only check available positions.
        if (!used[x]) {
            // Mark this position as used.
            used[x] += 1;
            // This position is called "B"
            // For every A, make sure no C exists such that |A-B| = |B-C|
            // I.e. mark them as used even though no oranges are placed there.
            for(y = 0; y < turn; ++y) {
                tmp_index = x + x - oranges[y];
                if (tmp_index >= 0 && tmp_index < BOWLS) {
                    used[tmp_index] += 1;
                }
            }

            // The orange on this turn is placed on "x"
            oranges[turn] = x;
            ++turn;
            check(x+1);
            --turn;
            // Revert the "used" markers placed this turn.
            for(y = 0; y < turn; ++y) {
                tmp_index = x + x - oranges[y];
                if (tmp_index >= 0 && tmp_index < BOWLS) {
                    used[tmp_index] -= 1;
                }
            }
            used[x] -= 1;
        }
    }
}

int main() {
    check(0);
    printf("%d\n", count);
}
//#endif

#if 0
//https://gist.github.com/989108/
#include<stdio.h>

const int BOWLS = 40;
const int ORANGES = 9;


int count = 0;
// All the places in which an orange can't be placed are 1's
 int used[BOWLS];
// A list of the oranges already placed.
int oranges[ORANGES];

int turn = 0;
int y;
int tmp_index;

template <int turn>
inline void check(int x) {
    for(; x < BOWLS - (ORANGES - turn - 1); ++x) {
        // Only check available positions.
        if (!used[x]) {
            // Mark this position as used.
            used[x] += 1;
            // This position is called "B"
            // For every A, make sure no C exists such that |A-B| = |B-C|
            // I.e. mark them as used even though no oranges are placed there.
            for(y = 0; y < turn; ++y) {
                tmp_index = x + x - oranges[y];
                if (tmp_index >= 0 && tmp_index < BOWLS) {
                    used[tmp_index] += 1;
                }
            }

            // The orange on this turn is placed on "x"
            oranges[turn] = x;
            check<turn+1>(x+1);

            // Revert the "used" markers placed this turn.
            for(y = 0; y < turn; ++y) {
                tmp_index = x + x - oranges[y];
                if (tmp_index >= 0 && tmp_index < BOWLS) {
                    used[tmp_index] -= 1;
                }
            }
            used[x] -= 1;
        }
    }
}

template <>
inline void check<ORANGES>(int x) {
    ++count;
}


int main() {
    check<0>(0);
    printf("%d\n", count);
}
#endif
