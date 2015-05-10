/* http://www.bittorrent.com/company/about/developer_challenge
 * 
 *   You have 40 bowls, all placed in a line at exact intervals of 1 meter.
 *   You also have 9 oranges. You wish to place all the oranges in the bowls,
 *   no more than one orange in each bowl, so that there are no three oranges
 *   A, B, and C such that the distance between A and B is equal to the
 *   distance between B and C. How many ways can you arrange the oranges in
 *   the bowls?
 *
 * In other words, consider all 40-bit numbers with exactly 9 bits set,
 * and find out how many of them fulfill the additional distance requirement.
 *
 * Algorithms for Permutations and Combinations
 * http://cs.utsa.edu/~dj/cs3343/lecture25.html
 */
#if 0
#include<stdio.h>
#define ORANGES 9
#define BOWLS	40
static int oranges[ORANGES];
static int used[BOWLS];
int search(int n, int m)
{
    int i,j,res = 0;
    if(n == ORANGES - 1)
    {
        for(; m < BOWLS; ++m) {
            /* for the last oranges
             * add the unused bowl position
             */
            res += !used[m];
        }
    }
    else
    {
        for(; m < BOWLS; ++m)
        {
            /* if not available, continue*/
            if(used[m])
                continue;
            for(i = n - 1; i >= 0; --i)
            {
                /*
                 * This B position make sure for every A,
                 * no C exist such that |A-B| = |B-C|
                 * mark these C position even though no oranges are placed there
                 */
                j = 2*m - oranges[i];
                if(j >= BOWLS)
                    break;
                ++used[j];
            }
            /* mark Nth orange's position */
            oranges[n] = m;
            res += search(n + 1, m + 1);
            /*
             * Revert marked position for the next loop
             */
            while(++i < n)
                --used[2*m - oranges[i]];
            /**
             * for(i = 0; i < n; ++i)
             * {
             *      int j = 2*m - orange[i];
             *      if(0 <= j && j < BOWLS)
             *          --used[j];
             * }
             */
        }
    }
    return res;
}

int main() {
    printf("%d\n", search(0, 0));
    return 0;
}
#endif

//#if 0
/* template version */
#include <stdio.h>

#define N  9  /* number of oranges */
#define M 40  /* number of bowls */

static int places[N];
static int blocked[M];

template<int n>
inline int search(int m)
{
    int i, j, res = 0;
    for (; m < M; ++m)
    {
        if (blocked[m]) continue;
        for (i = n - 1; i >= 0; --i)
        {
            j = 2*m - places[i];
            if (j >= M) break;
            ++blocked[j];
        }
        places[n] = m;
        res += search<n + 1>(m + 1);
        while (++i < n) --blocked[2*m - places[i]];
    }
    return res;
}

template<>
inline int search<N-1>(int m)
{
    int res = 0;
    for (; m < M; ++m) res += !blocked[m];
    return res;
}

int main()
{
        printf("%d\n", search<0>(0));
            return 0;
}
//#endif
