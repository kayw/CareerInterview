//http://blog.csdn.net/xufei96/article/details/5982397
//1、2、4、7、11、15[15]   4+11=15 ouput is  4,11
#![feature(convert)]
type IndexPair =  (isize,isize);
fn find_index_equal_sum(array: &[isize], sum: isize) -> IndexPair {
    let mut hi_idx = array.len() as isize - 1;
    let mut lo_idx = 0;
    let mut ip = (lo_idx, hi_idx);
    while lo_idx < hi_idx {
        let idx_sum = array[hi_idx as usize] + array[lo_idx as usize];
        if idx_sum > sum {
            hi_idx -= 1;
        }  else if idx_sum < sum {
            lo_idx += 1;
        } else {
            ip = (lo_idx, hi_idx);
            break;
        }
    }
    ip
}

#[cfg(test)]
mod test {
    #[test]
    fn test_find_index_equal_sum() {
        let arr = vec![1, 2, 4, 7, 11, 15];
        let pair = ::find_index_equal_sum(arr.as_slice(), 15);

        match pair {
            (lo, hi) => {
                assert_eq!(lo, 2);
                assert_eq!(hi, 4);
            },
            //_ => {}
        };

        let (lo, _) = super::find_index_equal_sum(arr.as_slice(), 15);
        assert_eq!(lo, 2);
    }
}
