#http://stackoverflow.com/questions/137783/expand-a-random-range-from-15-to-17
#http://stackoverflow.com/questions/137783/expand-a-random-range-from-15-to-17/842343#842343
#http://www.cnblogs.com/dwdxdy/archive/2012/07/28/2613135.html
#http://www.cppblog.com/hardtry/archive/2011/10/09/157556.html
#!/usr/bin/env python
import random
import math

rand5_calls = 0
def rand5():
    global rand5_calls
    rand5_calls += 1
    return random.randint(1,5)#random.randint(0,4)

def rand7():
    i = 5*(rand5()-1)  + rand5()
    """
    while True:
        if i > 21:
            i = 5*(rand5() - 1) + rand5()
        else:
            result = i%7 + 1
            i = 5*(rand5() - 1) + rand5()
            yield result
            """
    while i > 21:
        i = 5*(rand5() - 1) + rand5()
    return i%7 + 1 

def rand7_gen():
    state = 0
    pow5 = 1
    pow7 = 7
    while True:
        if state / pow5 == (state + pow7) / pow5:
            result = state / pow5
            state = (state - result * pow5) * 7
            pow7 *= 7
            yield result
        else:
            state = 5 * state + pow7 * rand5()
            pow5 *= 5

if __name__ == '__main__':
    N = 10000
    """
    r7 = rand7_gen()
    #r7 = rand7()
    x = list(next(r7) for i in range(N))
    """
    x = list(rand7() for i in range(N))
    distr = [x.count(i + 1) for i in range(7)]
    expmean = N / 7.0
    expstddev = math.sqrt(N * (1.0/7.0) * (6.0/7.0))

    print '%d TRIALS' % N
    print 'Expected mean: %.1f' % expmean
    print 'Expected standard deviation: %.1f' % expstddev
    print
    print 'DISTRIBUTION:'
    for i in range(7):
        print '%d: %d   (%+.3f stddevs)' % (i, distr[i], (distr[i] - expmean) / expstddev)
    print 'Calls to rand5: %d (average of %f per call to rand7)' % (rand5_calls, float(rand5_calls) / N)
