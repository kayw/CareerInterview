#!/usr/bin/env python
# -*- coding: utf-8 -*-
#filename: clrs3e_2-4.py
#date: 2013 十月 03 23:28:48

def calc_inversions(permutationArray, start, end):
    """
    end - stop index


    """
    if start >= end:
        return 0
    mid = (start + end)/2
    #print "start: ",start,"mid: ",mid,"end: ",end
    inversions = calc_inversions(permutationArray, start, mid)
    #print "total plus left calc:",inversions
    inversions = inversions + calc_inversions(permutationArray, mid+1, end)
    #print "total plus right calc:",inversions

    inversions = inversions + merge_inversions(permutationArray, start, mid, end)
    return inversions

def merge_inversions(permutationArray, start, midian, end):
    leftArray = [permutationArray[start + i] for i in range(midian - start + 1)]
    rightArray = [permutationArray[midian + i + 1] for i in range(end - midian)]
    #print leftArray,rightArray
    i = j = 0
    k = start
    inversions = 0
    #for perm in permutationArray:
    while k <= end:
        if i >= len(leftArray):
            break
        elif j >= len(rightArray) or leftArray[i] <= rightArray[j]:
            permutationArray[k] = leftArray[i]
            i = i + 1
            # j reprensents the passed value in rightArray which is less than leftArray[i]
            inversions = inversions + j
        else:
            #inversions = inversions + 1
            #print leftArray[i], rightArray[j]
            permutationArray[k] = rightArray[j]
            j = j + 1
        k = k + 1
    return inversions

if __name__ == "__main__":
    A = [1,8,7,6]
    print calc_inversions(A, 0, len(A)-1)
    #print A
    A = [6,5,4,3,2,1]
    print calc_inversions(A,0, len(A)-1)
    A = [5,4,6,2,3]
    print calc_inversions(A,0, len(A)-1)
