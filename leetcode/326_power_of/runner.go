package career_interview

import "math"

func round(val float64) float64 {
	/*
		if val < 0 {
			return int(val - 0.5)
		}
		return int(val + 0.5)
	*/
	if val < 0 {
		return math.Ceil(val - 0.5)
	}
	return math.Floor(val + 0.5)
}

//https://www.hrwhisper.me/leetcode-power-of-three/
func IsPowerOfThree(n int) bool {
	if n < 0 {
		return false
	}
	return int(math.Pow(3, round(math.Log(float64(n))/math.Log(3.0)))) == n
}

// http://blog.csdn.net/foreverling/article/details/50603378
func IsPowerOfTwo(n int) bool {
	if n < 0 {
		return false
	}
	return n&(n-1) == 0
}
