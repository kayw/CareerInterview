//http://stackoverflow.com/questions/14878228/creating-a-random-tree
//https://github.com/rust-lang/rust/issues/4992
//
//http://stackoverflow.com/questions/24394211/difficulty-with-rust-binary-tree-implementation
//https://gist.github.com/rossmurray/5129924
//http://stackoverflow.com/questions/24503572/tree-fold-in-rust
//http://stackoverflow.com/questions/21791786/rudimentary-tree-and-pointers-in-rust
//http://stackoverflow.com/questions/21435202/canonical-implementation-of-mutable-trees

#![feature(box_syntax)]
#![feature(rand)]
#![feature(convert)]
//extern crate debug;
use std::mem::swap;
// http://192.168.56.7/rustdoc/rand/trait.Rng.html
use std::__rand::{thread_rng, Rng};//http://stackoverflow.com/questions/19671845/how-can-i-generate-a-random-number-within-a-range-in-rust
use std::cmp::max;
pub struct RandomTree<V> {
    //https://github.com/rust-lang/rust/issues/9629
    //http://cmr.github.io/blog/2013/08/13/rust-by-concept/
    //http://stackoverflow.com/questions/16879287/mutable-struct-fields
  root_: Box<TreeNode<V>>
}

//#[deriving(Clone)]
struct TreeNode<V> {
    value_: V,
    children_: Vec<Box<TreeNode<V>>>
}

impl<V:Ord+Clone+std::fmt::Display> RandomTree<V> {
    //http://stackoverflow.com/questions/3522454/java-tree-data-structure
    //http://www.quesucede.com/page/show/id/java-tree-implementation
    fn new_tree(value: V) -> RandomTree<V> {
        RandomTree {
            root_ : box TreeNode { value_: value, children_: Vec::new() }
        }
    }

//http://stackoverflow.com/questions/13501216/how-to-find-the-max-distance-between-a-set-of-nodes-on-a-tree
    fn diameter(self) -> isize {
        let mut depth = 0;
        RandomTree::diameter_helper(&self.root_, &mut depth)
    }

    fn diameter_helper(root: &Box<TreeNode<V>>, depth: &mut isize) -> isize {
        if root.is_leaf() {
            *depth = 0;
            0
        }
        else {
        let mut max_depth = 0;
        let mut sec_max_depth = 0;
        let mut max_diameter = 0;
        let mut tmp_depth = 0;
        for child_node in root.children_.iter() {
            let tmp_diameter = RandomTree::diameter_helper(child_node, &mut tmp_depth);
            println!("depth for node {}:{}",child_node.value_, tmp_depth);
            max_diameter = max(max_diameter, tmp_diameter);
            //let tmp_depth = RandomTree::height_helper(child_node);
            if tmp_depth > max_depth {
                sec_max_depth = max_depth;
                max_depth = tmp_depth;
            } else if tmp_depth > sec_max_depth {
                sec_max_depth = tmp_depth;
            }
        }
        *depth = max_depth + 1;
        max(max_diameter, max_depth + sec_max_depth + 2)
        }
    }

//http://cs.brown.edu/cgc/jdsl/tutorial/lesson06/RandomTreeBuilder.java.html
    fn build_random_tree(node_vals: &Vec<V>) -> RandomTree<V> {
        let mut root = box TreeNode{ value_: node_vals[0].clone(), children_: Vec::new() };
        RandomTree::build_random_tree_helper(&mut root, node_vals, 1, node_vals.len() as isize - 1);
        RandomTree { root_ : root }
    }

    fn build_random_tree_helper(cur_root: &mut Box<TreeNode<V>>, node_vals: &Vec<V>, val_pos: usize, children_size: isize) {
    // val_pos start at the remaining nodeval vector position
        //TODO: bfs
        let mut size_vec : Vec<isize> = Vec::new();
        let mut to_build = children_size;
        while to_build > 0 {
            let children_num =
                if to_build > 1 {
                    thread_rng().gen_range(1, to_build)
                } else {
                    1
                };
            to_build -= children_num;
            size_vec.push(children_num);
        }
        RandomTree::<V>::permute(&mut size_vec);
        let mut child_pos = val_pos + size_vec.len();
        for i in 0..size_vec.len() {
            //see todo in private-lab:bound_unconstrainted_type(vec_index_move_generic)
            let mut child = box TreeNode{ value_: node_vals[val_pos+i].clone(), children_: vec![] };
            RandomTree::build_random_tree_helper(&mut child, node_vals, child_pos, size_vec[i]-1);// nodevals after the father node allocate
            child_pos += size_vec[i] as usize - 1;
            cur_root.add_node(child);
            //cur_root.children_.push(child);
        }
    }

    //http://stackoverflow.com/questions/13619520/in-rust-does-modifying-a-borrowed-pointer-change-the-original-value
    fn permute(sizes: &mut Vec<isize>) {
        //https://github.com/rust-lang/rust/issues/1817
        for i in (1..sizes.len()).rev() { //https://internals.rust-lang.org/t/step-by-on-negative-numbers/2231/3
            let j = thread_rng().gen_range(0, i);
            if j < i {
                sizes.as_mut_slice().swap(i as usize, j as usize);
            }
        }
    }

    fn print_tree(&self) {
        //http://www.rustforrubyists.com/book/chapter-10.html
        //http://stackoverflow.com/questions/21747136/how-do-i-print-the-type-of-a-variable-in-rust
        //println!("{:?}", node.value_);
        let mut children = Vec::new();
        children.push(&self.root_);
        let mut next_level_children = Vec::new();
        while children.len() > 0 {
            let child = children.remove(0);
            print!(" {}({})", child.value_, child.children_.len());
            for next_child in child.children_.iter() {
                next_level_children.push(next_child);
            }
            //next_level_children.append(child.children_.as_slice());
            if children.len() == 0 {
                print!("\n");
                //rust/borrowck-mut-uniq.rs  src/librustdoc/fold.rs
                swap(&mut children, &mut next_level_children);
            }
        }
    }

    fn height(&self) -> isize {
        RandomTree::height_helper(&self.root_)
    }

    fn height_helper(root: &Box<TreeNode<V>>) -> isize {
       let mut cur_height = 0;
       for child_node in root.children_.iter() {
           let childheight = RandomTree::height_helper(child_node);
           let this_height = childheight + 1;
           if this_height > cur_height {
               cur_height = this_height;
           }
       }
       cur_height
    }

    fn print_tree_in_level(&self) {
        //TODO print pretty
        let h = self.height()+1;
        let mut node_queue = Vec::new();
        node_queue.push(&self.root_);
        for level in 0..h {
            for node in node_queue.iter() {
                print!("{} ",node.value_);
            }
            print!("\n");
            //let mut tmp_nodes = 0;
            let nodes_in_level = node_queue.len();
            for _ in 0..nodes_in_level {
                let node = node_queue.remove(0);
                for child_node in node.children_.iter() {
                    node_queue.push(child_node);
                }
            }
        }
    }
}


impl<V:Ord> TreeNode<V> {
    fn is_leaf(&self) -> bool {
        return self.children_.len() == 0;
    }

    fn add_node(&mut self, child: Box<TreeNode<V>>) {
        self.children_.push(child);
    }
}

#[cfg(test)]
mod test_random_tree {
    use super::RandomTree;
    use super::TreeNode;
    #[test]
    fn test_random_create() {
        let vals = vec![11,5,6,3,7,9,2];
        let tree : RandomTree<isize> = RandomTree::build_random_tree(&vals);
        //http://stackoverflow.com/questions/25106554/println-doesnt-work-in-rust-unit-tests
        //--nocature
        tree.print_tree();
        tree.print_tree_in_level();
    }

    #[test]
    fn test_spanning_subtree_diameter() {
        //        root
        //      b1          b2
        //  leaf1  leaf2     b3
        //                  leaf3
        let l1 = box TreeNode { value_ : "leaf1", children_: Vec::new() };
        let l2 = box TreeNode { value_: "leaf2", children_: Vec::new() };
        let mut branch1 = box TreeNode { value_: "b1", children_: Vec::new() };
        branch1.add_node(l1);
        branch1.add_node(l2);
        let l3 = box TreeNode { value_ : "leaf3", children_: Vec::new() };
        let mut b3 = box TreeNode { value_: "b3", children_: Vec::new() };
        b3.add_node(l3);
        let mut b2 = box TreeNode { value_: "b2", children_: Vec::new() };
        b2.add_node(b3);
        let mut tree : RandomTree<&str> = RandomTree::new_tree("root");
        tree.root_.add_node(branch1);
        tree.root_.add_node(b2);
        assert!(tree.diameter() == 5);
    }

    #[test]
    fn test_single_subtree_diameter() {
        //           root
        //        b1           l4
        //    b3  b4  l3
        //   b6   b7
        //  l1    l2
        let l1 = box TreeNode { value_: "l1", children_: Vec::new() };
        let mut b6 = box TreeNode { value_: "b6", children_: Vec::new() };
        b6.add_node(l1);
        let mut b3 = box TreeNode { value_: "b3", children_: Vec::new() };
        b3.add_node(b6);
        let l2 = box TreeNode { value_ : "l2", children_: Vec::new() };
        let mut b7 = box TreeNode { value_: "b7", children_: Vec::new() };
        b7.add_node(l2);
        let mut b4 = box TreeNode { value_: "b4", children_: Vec::new() };
        b4.add_node(b7);
        let l3 = box TreeNode { value_: "l3", children_: Vec::new() };
        let mut b1 = box TreeNode { value_: "b1", children_: Vec::new() };
        b1.add_node(b3);
        b1.add_node(b4);
        b1.add_node(l3);
        let l4 = box TreeNode::<&str>{ value_: "l4", children_: Vec::new() };
        let mut tree : RandomTree<&str> = RandomTree::new_tree("root");
        tree.root_.add_node(b1);
        tree.root_.add_node(l4);
        assert!(tree.diameter() == 6);
    }
}
