#!/usr/bin/env python
# -*- coding: utf-8 -*-
def PrefixFromCLRS(pattern, prefix):
    prefix.append(-1)
    k = -1
    for q in xrange(1, len(pattern)):
        while(k > -1 and pattern[k+1] != pattern[q]):
            k = prefix[k]
        if(pattern[k+1] == pattern[q]):
            k = k+1
        prefix.append(k)
#    k = 0
#    for q in xrange(1, len(pattern)):
#        while(k > 0 and pattern[k] != pattern[q]):
#            k = prefix[k]
#        if(pattern[k] == pattern[q]):
#            k = k+1
#        prefix.append(k)


#for 1 <= i < m, suff[i]=max{k : x[i-k+1 .. i]=x[m-k .. m-1]} 0 if no exist
def SuffixList(pattern):
    m = len(pattern)
    suffixlist = [-1]*m
    suffixlist[m-1] = m
    i = m -2;
    while(i >= 0):
        q = i
        while(q>=0 and pattern[q] == pattern[m-1-i + q]):
            q = q-1
        suffixlist[i] = i - q
        i = i-1
    return suffixlist

#http://acm.hust.edu.cn/vjudge/problem/viewSource.action?id=287061
#http://www.cnblogs.com/a180285/archive/2011/12/15/BM_algorithm.html
def SuffixMap(pattern, suffix):
    suffix.append(-1)
    m = len(pattern)
    suffix[m-1] = m
    i = m -2;
    while(i > 0):
        q = i
        while(q>0 and pattern[q] == pattern[m-1-i + q]):
            q = q-1
        suffix[i] = i - q
        i = i-1
    suffix = SortedDictByKey(suffix)

def SortedDictByKey(dictmap):
    #http://stackoverflow.com/questions/613183/python-sort-a-dictionary-by-value
    return dict(sorted(dictmap.iteritems(), key=lambda x: x[0]) )

def GoodSuffixFromCLRS(pattern):
    prefix = []
    PrefixFromCLRS(pattern, prefix)
    pp = pattern[::-1]#http://stackoverflow.com/questions/931092/reverse-a-string-in-python
    prefixstoke = []
    PrefixFromCLRS(pp, prefixstoke)
    j = 0
    m = len(pattern)
    goodsuffix = [-1]*(m+1)
    while(j <= m):
        goodsuffix[j] = m -1 - prefix[m-1]
        j = j+1
    l = 1
    while(l < m):
        j = m-1 - prefixstoke[l]
        if(goodsuffix[j] > l - prefixstoke[l]):
            goodsuffix[j] = l -prefixstoke[l]
        l = l+1
    return goodsuffix

#http://www-igm.univ-mlv.fr/~lecroq/string/node14.html#SECTION00140
def GoodSuffixFromLECROQ(pattern):
    suffix = SuffixList(pattern)
    i = 0
    m = len(pattern)
    goodsuffix = [-1]*m
    while(i < m):
        goodsuffix[i] = m
        i = i+1
    j = 0
    i = m -1
    while(i >= 0):
        if(suffix[i] == i+1):
            while(j < m-1-i):
                if(goodsuffix[j] == m):
                    goodsuffix[j] = m -1-i
                j = j+1
        i = i -1
    i = 0
    while(i <= m-2):
        goodsuffix[m-1- suffix[i] ] = m - 1 -i
        i = i+1
    return goodsuffix

#http://www.cnblogs.com/10jschen/archive/2012/08/19/2646120.html
#http://www.slyar.com/blog/kmp-next-nextval.html
def NextList(pattern, nextlist):
    i = 0
    j = -1
    m = len(pattern)
    nextlist.append(-1)#nextlist=[-1] not assign but modify the reference
    #http://stackoverflow.com/questions/986006/python-how-do-i-pass-a-variable-by-reference
    while(i <m):
        while( -1 != j and pattern[j] != pattern[i] ):
            j = nextlist[j]
        i = i + 1
        j = j + 1
        nextlist.append(j)

def Nextval(pattern, nextval):
    nextval.append(-1)
    k = -1
    m = len(pattern)
    i = 0
    while(i < m):
        while (k > -1 and pattern[i] != pattern[k]):
            k =nextval[k];
        i= i+1
        if(i == m):
            break
        k=k+1
        if (pattern[i] == pattern[k]):
            nextval.append(nextval[k])
        else:
            nextval.append(k)
    

if __name__ == "__main__":
    pattern = "abcabcbd"
    nextlist = []
    NextList(pattern, nextlist)
    print "next"
    for a in nextlist:
        print a

    nextval = []
    Nextval(pattern, nextval)
    print "nextval"
    for a in nextval:
        print a

    prefixFromCLRS = []
    PrefixFromCLRS(pattern, prefixFromCLRS)
    print "PrefixFromCLRS"
    for a in prefixFromCLRS:
        print a

    suffix = SuffixList(pattern)
    print "suffix"
    for a in suffix:
        print a

    goodsuffix = GoodSuffixFromCLRS(pattern)
    print "GoodSuffixFromCLRS"
    for a in goodsuffix:
        print a
    goodsuffix = GoodSuffixFromLECROQ(pattern)
    print "GoodSuffixFromLECROQ"
    for a in goodsuffix:
        print a

    pattern = "gcagagag"
    suffix = SuffixList(pattern)
    print "suffix of gcagagag"
    for a in suffix:
        print a
    goodsuffix = GoodSuffixFromLECROQ(pattern)
    print "GoodSuffixFromLECROQ of gcagagag"
    for a in goodsuffix:
        print a
    goodsuffix = GoodSuffixFromCLRS(pattern)
    print "GoodSuffixFromCLRS of gcagagag"
    for a in goodsuffix:
        print a
