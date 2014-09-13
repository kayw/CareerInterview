
import java.util.ArrayList;
import java.util.List;

import java_base.BSTree;


public class PostTreePrintFitVector {
	public static void main(String[] args) {
		BSTree<Integer> tree = new BSTree<Integer>();
		BSTree.createTree(tree, 10);
		BSTree<Integer>.BSTreeNode<Integer> root = tree.getRootNode();
	    List<Integer> randarray = new ArrayList<Integer>();
	    postOrderPrint(root, randarray);
	    if (PostOrderArrayHelper./*<Integer>*/isPostOrder(randarray, 0, randarray.size()-1)) {
			System.out.println("post order");
		} else {
			System.out.println("non post order");
		}
	}

	private static void postOrderPrint(BSTree<Integer>.BSTreeNode<Integer> root,
			List<Integer> randarray) {
		if (root != null && root.getData() != null) {
			postOrderPrint(root.getLeftChild(), randarray);
			postOrderPrint(root.getRightChild(), randarray);
			randarray.add(root.getData() );
		}
		
	}
}
