#!/usr/bin/env python
# encoding: utf-8
#import json
from random import randrange
def islandsByWaterLevel(plots, levels):
    islands_per_level = [0]*max(max(plots)+1, max(levels)+1)
    previous_plot = 0
    for plot in plots:
        if plot > previous_plot:
            islands_per_level[plot - 1] = islands_per_level[plot-1] + 1
            #http://stackoverflow.com/questions/1319214/shorter-more-pythonic-way-of-writing-an-if-statement
            if previous_plot:  
                islands_per_level[previous_plot-1] = islands_per_level[previous_plot-1] -1
        previous_plot = plot
    #print islands_per_level
    tmp = islands_per_level[-1]
    #http://stackoverflow.com/questions/869885/loop-backwards-using-indices-in-python
    for i in reversed(xrange(len(islands_per_level) ) ):
        islands_per_level[i] = islands_per_level[i] + tmp
        if islands_per_level[i]:
            tmp = islands_per_level[i]
    #print islands_per_level
    return [islands_per_level[level] for level in levels]

def formatReadableList(L):
    return "[" + ",".join('%s' %l for l in L) + "]"

def outputArgumentResult(P, W):
    with open("case-data","a") as f:
        """
        "http://stackoverflow.com/questions/899103/python-write-a-list-to-a-file
        json.dump(plots, f)
        json.dump(" ", f)
        json.dump(waters, f)
        """
        #http://stackoverflow.com/questions/3820312/python-write-a-list-of-tuples-to-a-file
        #http://stackoverflow.com/questions/17225287/python-2-7-write-and-read-a-list-from-file
        #f.write("["+",".join('%s' %p for p in plots) + "] ")
        #f.write("["+",".join('%s' %w for w in waters) + "] ")
        f.write(formatReadableList(P))
        f.write(" ")
        f.write(formatReadableList(W))
        f.write(" ")
        islands = islandsByWaterLevel(P, W)
        f.write(formatReadableList(islands))
        f.write('\n')
    #f.close()

def simple_case():
    plots = [2,1,3,2,3]
    waters = [0,1,2,3,1]
    outputArgumentResult(plots, waters)

"""
min_max
min and max values  0.110 s.    OK
triple
three elements  0.030 s.    OK
"""
def triple_minmax_case():
    plots= [100000, 6789, 0]
    waters = [0, 378, 100000]
    outputArgumentResult(plots, waters)

"""
extreme_small
only one element    0.030 s.    OK
"""
def one_small_case():
    plots= [79]
    waters = [42]
    outputArgumentResult(plots, waters)
    
"""
small_random
random small sequences, length = ~500   0.110 s.    OK
"""
def small_random_case():
    #http://www.newsmth.net/bbstcon.php?board=Python&gid=104563
    #plots = list({random() for _ in xrange(100000)})[:500]
    #http://stackoverflow.com/questions/5555712/generate-a-random-number-in-python
    #http://effbot.org/pyfaq/how-do-i-generate-random-numbers-in-python.htm
    plots = list({randrange(0, 100000+1) for _ in xrange(500)})
    waters = list({randrange(0, 100000+1) for _ in xrange(400)})
    outputArgumentResult(plots, waters)
"""
medium_random
random medium sequences, length = ~10,000   0.150 s.    OK
"""
def medium_random_case():
    plots = list({randrange(0, 100000+1) for _ in xrange(9000)})
    waters = list({randrange(0, 100000+1) for _ in xrange(10000)})
    outputArgumentResult(plots, waters)


"""
large_random
random lare sequences, length = ~30,000     0.260 s.    OK
"""
def large_random_case():
    plots = list({randrange(0, 100000+1) for _ in xrange(30000)})
    waters = list({randrange(0, 100000+1) for _ in xrange(30000)})
    outputArgumentResult(plots, waters)

"""
large_range
[10001, 10002, ..., 40000], length = ~30,000    0.220 s.    OK
exteme_large
all the same values
"""
def large_case():
    plots = [10001 for _ in xrange(30000)]
    waters = [10001 + _ for _ in xrange(30000)]
    outputArgumentResult(plots, waters)

if __name__ == '__main__':
    #http://stackoverflow.com/questions/2769061/how-to-erase-the-file-contents-of-text-file-in-python-and-c
    open("case-data",'w').close()
    simple_case()
    triple_minmax_case()
    one_small_case()
    small_random_case()
    medium_random_case()
    large_random_case()
    large_case()
