fn get_count_of_digit1s(n: isize ) -> isize {
   let mut prefix = [0; 10];
   let mut suffix: [isize; 10] = [0; 10];
   let mut digit = [0; 10];
   let mut i = 0;
   let mut base = 1;
   let mut count = 0;
   while base < n {
       suffix[i] = n % base;
       digit[i] = ((n % (base * 10)) - suffix[i]) / base;
       prefix[i] = (n - suffix[i] - digit[i] * base) / 10;
       i += 1;
       base *= 10;
   }
   // println!("prefix: {:?}, suffix: {:?}, digit: {:?}", prefix, suffix, digit);
   base = 1;
   for j in 0..i {
       if digit[j] == 0 {
           count += prefix[j];
       } else if digit[j] == 1 {
           count += prefix[j] + suffix[j] + 1;
       } else {
           count += prefix[j] + base;
       }
       base *= 10;
   }
   // println!("{}", count);
   count
}

#[test]
fn test_1s_of_12() {
    assert!(get_count_of_digit1s(12) == 5);
}
#[test]
fn test_1s_of_2() {
    assert!(get_count_of_digit1s(2) == 1);
}
#[test]
fn test_1s_of_102() {
    assert!(get_count_of_digit1s(102) == 24);
}
#[test]
fn test_1s_of_112() {
    /*
     * 1 10 11 .. 19 21 31 .. 91 100 101 .. 109 110 111 112
     */
    assert!(get_count_of_digit1s(112) == 38);
}
