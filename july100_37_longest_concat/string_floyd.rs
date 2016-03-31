// http://blog.csdn.net/acezhangcunyi/article/details/6629965
// http://blog.csdn.net/cxllyg/article/details/7606599
fn is_connected(pre_str : &str, suf_str: &str) -> bool {
    pre_str[1..pre_str.len()] == suf_str[0..suf_str.len() - 1]
}
fn longest_acylic(strings : Vec<&str>) -> i32 {
    let mut graph: Vec<Vec<i32>> = Vec::new();
    let len = strings.len();
    for i in 0..len {
        graph.push(Vec::new());
        for j in 0..len {
            // if strings[i] is self connected
            // it's a cyle
            if is_connected(strings[i], strings[j]) {
                graph[i].push(1);
            } else {
                graph[i].push(0);
            }
        }
    }
    for k in 0..len {
        for i in 0..len {
            for j in 0..len {
                if graph[i][k] != 0 && graph[k][j] != 0 && graph[i][j] < graph[i][k] + graph[k][j] {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
    for i in 0..len {
        if graph[i][i] > 1 {
            return -1;
        }
    }
    let mut max = 0;
    for i in 0..len {
        for j in 0..len {
            if graph[i][j] > max {
                max = graph[i][j];
            }
        }
    }
    // todo construct longest path
    // http://blog.csdn.net/cxllyg/article/details/7606599
    // https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm#Path reconstruction
    return max;
}

#[test]
fn test_longest() {
    // http://blog.csdn.net/cxllyg/article/details/7606599
    let strings = vec![
        "abcd",
        "qwer",
        "bcde",
        "wert",
        "erty",
        "cdeh",
        "tyui",
        "rtyu",
    ];
    let length = longest_acylic(strings);
    assert_eq!(length, 4);
}

#[test]
fn test_longest_with_cycle() {
    let strings = vec![
        "qwer",
        "weqw",
        "eqwe",
        "qweq",
    ];
    let length = longest_acylic(strings);
    assert_eq!(length, -1);
}
// todo topological
// http://stackoverflow.com/questions/18450062/is-there-any-algorithm-which-can-find-all-critical-paths-in-dag
// https://en.wikipedia.org/wiki/Longest_path_problem
// https://www.quora.com/What-is-an-algorithm-to-find-a-longest-path-in-a-unweighted-directed-acyclic-graph
