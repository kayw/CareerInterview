fn knock_out(winners: &Vec<Vec<i32>>, orders: &Vec<i32>) -> Vec<i32>{
    let mut round = orders.len();
    //results.extend(orders.iter().cloned());
    let mut results = orders.clone();
    while round > 1 {
        let mut i = 0;
        let mut j = 0usize;
        while i < round {
            let winner = if i == round -1 { i } else { winners[i][i + 1] as usize };
            results.swap(j, winner);
            j+=1;
            i+=2;
        }
        round /= 2;
    }
    results
}

#[test]
fn test_knock_out() {
    let winners = vec![vec![0,0,2,0], vec![0,1,2,3],vec![2,1,2,3], vec![0,3,3,3]];
    let orders = vec![3,1,0,2];
    let results = knock_out(&winners, &orders);
    assert_eq!(results[0], 3);
    assert_eq!(results[1], 2);
}

#[test]
fn test_knock_out_csdn_ylf13() {
    //http://blog.csdn.net/ylf13/article/details/13627263
    let winners = vec![vec![0,1,0,3], vec![1,1,2,1],vec![0,2,2,2], vec![3,1,2,3]];
    let orders = vec![2,0,1,3];
    let results = knock_out(&winners, &orders);
    assert_eq!(results[0], 1);
    assert_eq!(results[1], 0);
}
