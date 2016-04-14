//http://en.wikipedia.org/wiki/Josephus_problem
//http://www.exploringbinary.com/powers-of-two-in-the-josephus-problem/
//https://people.math.ethz.ch/~halorenz/publications/pdf/jos.pdf
package career_interview

func JosephProblem(n int, m int) int {
	fi := 0
	//i means ith round of killing
	for i := /*1*/ 2; i <= n; i++ {
		fi = (fi + m) % i
	}
	return fi //+ 1
}

func JosephCircleIncorrectThought(n int, m int) int {
	fi := 0
	for i := n; i > 1; i-- {
		fi = (fi + m) % i
	}
	return fi + 1
}
