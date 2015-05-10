struct LinkedNode<T> {
    value_ : T,
    next_ : Option<Box<LinkedNode<T>>>
}

impl<T> LinkedNode<T> {
    fn kth_to_last(head: &Box<LinkedNode<T>>, k: int) -> Option<&Box<LinkedNode<T>>> {
        if k < 0 {
            fail!("bad argument");
            //return None;
        }
        let mut to_end_cursor = head;
        for i in range(0, k-1) {
            match to_end_cursor.next_ {
                Some(ref node) => { to_end_cursor = node; }
                None => { return None; }
            }
        }
        let mut k_tolast_cursor = head;
        //http://nickdesaulniers.github.io/blog/2013/05/07/rust-pattern-matching-and-the-option-type/
        loop {
            match to_end_cursor.next_ {
                Some(ref to_end_node) => {
                    to_end_cursor = to_end_node;
                },
                None => break
            }
            match k_tolast_cursor.next_ {
                Some(ref k_tolast_node) => {
                    k_tolast_cursor = k_tolast_node;
                }
                None => { fail!("impossible reach the node end");}
            }
        }
        Some(k_tolast_cursor)
    }
}

#[cfg(test)]
mod tests {
    use super::LinkedNode;
    #[test]
    fn test_k_to_last() {
        let mut head = box LinkedNode { value_: "first", next_: None };
        let mut sec = box LinkedNode { value_: "second", next_: None };
        let mut third = box LinkedNode { value_: "third", next_: None };
        let mut fourth = box LinkedNode { value_: "fourth", next_: None };
        let fifth = box LinkedNode { value_: "fifth", next_: None };
        fourth.next_ = Some(fifth);
        third.next_ = Some(fourth);
        sec.next_ = Some(third);
        head.next_ = Some(sec);
        let sec_to_last_node = LinkedNode::kth_to_last(&head, 2);
        assert_eq!(sec_to_last_node.unwrap().value_, "fourth");
    }
}
