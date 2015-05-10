
fn continumax_param_pass<'a>(output: &mut String, input: &'a str) -> usize {
    //libstd/sys/windows/process.rs fn append_arg(cmd: &mut String, arg: &str)
    //
    //stackoverflow.com/questions/19649005/why-using-rust-does-passing-a-mutable-struct-to-a-function-result-in-immutable-f
    let mut max_len = 0;
    let mut so_far_len = 0;
    let mut so_far_begin = 0;
    let mut idx = 0usize;
    let input_len = input.len();
    //blog.csdn.net/fanwu72/article/details/8794505
    while idx < input_len {
        /*while '1' <= input.char_at(idx) && input.char_at(idx) <= '9' {
            idx += 1;
            so_far_len += 1;
        }*/
        loop {
            match input.char_at(idx) {
                '0' ... '9' => {
                    idx += 1;
                    so_far_len += 1;
                    if idx >= input_len {
                        break;
                    }
                },
                _ => {
                    idx += 1;
                    break;
                }
            }
        }
        if so_far_len > max_len {
            max_len = so_far_len;
            so_far_begin = idx - 1 - so_far_len;
        }
        so_far_len = 0;
    }
    //todo unable to assign the output with the input str slice which is created local
    //libcore/fmt/builder impl<'a, 'b: 'a> fmt::Write for PadAdapter<'a, 'b>: same mut str overwrite
    //output = input.slice_chars(so_far_begin, so_far_begin + max_len);
    
        println!("{}", so_far_begin);
        println!("{}", max_len);
    for i in so_far_begin..(so_far_begin + max_len) {
        println!("{}", input.char_at(i));
        output.push(input.char_at(i));
    }
    max_len
}

fn continumax<'a>(input: &'a str) -> (&'a str, usize) {
    let mut max_len = 0;
    let mut so_far_len = 0;
    let mut so_far_begin = 0;
    //http://stackoverflow.com/questions/22118221/rust-how-do-you-iterate-over-a-string-by-character
    for (idx, ch) in input.chars().enumerate() {
      if '0' <= ch && ch <= '9' {
          println!("{}",ch);
          so_far_len += 1;
      }
      else {
          if so_far_len > max_len {
              max_len = so_far_len;
              so_far_begin = idx - so_far_len;
          }
          so_far_len = 0;
      }
    }
    if so_far_len > max_len {
        //this's ugly, but seems necessary,otherwise we need do it in a check end of string loop
        // like the version above
        //
        // see also this one same pattern: http://blog.csdn.net/ylf13/article/details/12884897
        max_len = so_far_len;
    }
    //http://stackoverflow.com/questions/24542115/how-to-index-a-string-in-rust
    //http://stackoverflow.com/questions/28615756/how-do-i-borrow-an-iterator
    //let input_iter = input.chars();
    //output = input_iter.clone().skip(so_far_begin).take(so_far_len);
    let output = input.slice_chars(so_far_begin, so_far_begin + max_len);
    println!("{}", max_len);
    (output, max_len)
}

#[test]
fn test_continumax() {
    let input_str = "fn1234end123456sad";
    let (output_buffer, max_len) = continumax(input_str);
    assert_eq!(max_len, 6);
    assert_eq!(output_buffer, "123456");

    let mut output_str: String = String::new();//from_str("");
    //let mut output_str: Iterator;
    let white_sep_input = "sf233 2342 djf3";
    let max_len = continumax_param_pass(&mut output_str, white_sep_input);
    assert_eq!(max_len, 4);
    assert_eq!(output_str, String::from_str("2342"));
}
