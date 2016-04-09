package career_interview

func PlusOne(digits []int) []int {
	length := len(digits)
	remainder := 1
	newDigits := []int{0}
	newDigits = append(newDigits, digits...)
	for i := length; i >= 0; i-- {
		newDigit := newDigits[i] + remainder
		newDigits[i] = newDigit % 10
		remainder = newDigit / 10
		if remainder == 0 {
			break
		}
	}
	if newDigits[0] == 0 {
		return newDigits[1:]
	} else {
		return newDigits
	}
}
