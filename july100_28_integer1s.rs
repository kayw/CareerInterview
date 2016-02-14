fn count_of_1s_in_number(num: isize) -> isize {
    let mut count = 0;
    let mut n = num;
    while n != 0 {
        n &= n-1;
        count += 1;
    }
    return count;
}

#[test]
fn test_count1s() {
    let n = 6;
    let num1s = count_of_1s_in_number(n);
    assert_eq!(num1s, 2);
}
