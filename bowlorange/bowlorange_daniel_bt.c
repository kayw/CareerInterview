/*
 * Copyright (c) 2011 Daniel Hartmeier <daniel@benzedrine.cx>
 * All rights reserved.
 *
 * http://www.bittorrent.com/company/about/developer_challenge
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
 *
 * Slightly adapt the recursive "n C k" algorithm found on the page above
 * and add a rather naive distance check.
 *
 * $ gcc -O3 -o prog prog.c
 * $ time ./prog
 * 1 2 4 5 10 11 13 14 28
 * 1 2 4 5 10 11 13 14 29
 * 1 2 4 5 10 11 13 14 30
 * 1 2 4 5 10 11 13 14 31
 * 7555794
 * real    0m2.543s
 *
 * Edit 1: improved valid() check, 13.1 -> 3.1 seconds
 * Edit 2: O(n) valid() check, down to 2.5 seconds
 *
 */

#include <stdio.h>

unsigned count = 0;

int
valid(int v[], int c)
{
	int a = 1, b, e;

	for (b = 2; b < c; ++b) {
		e = v[b] - v[c] + v[b];
		if (v[a] > e) 
			continue;
		while (v[a] < e)
			a++;
		if (v[a] == e)
			return (0);
	}
	return (1);
}

void
combinations(int v[], int start, int n, int k, int maxk)
{
	int i;

	if (k > maxk) {
		if (++count % 1000000 == 0) {
			for (i = 1; i <= maxk; ++i)
				printf("%d ", v[i]);
			printf("\n");
		}
		return;
	}
	for (i = start; i <= n; ++i) {
		v[k] = i;
		if (valid(v, k))
			combinations(v, i + 1, n, k + 1, maxk);
	}
}

int main()
{
	int v[10];

	combinations(v, 1, 40, 1, 9);
	printf("%u\n", count);
	return (0);
}
