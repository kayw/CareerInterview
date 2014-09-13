package java_base;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;


public class BSTree<ValueType> {
	public void createBSTree(ValueType[] values){
		rootNode_ = new BSTreeNode<ValueType>();
		createBSTTreeHelper(rootNode_, values, 0, values.length - 1);
	}
	//http://stackoverflow.com/questions/11069429/new-arraylistint-failing-in-java
	public static void createTree(BSTree<Integer> tree, int nodeNum) {
		Random r = new Random();
		//http://stackoverflow.com/questions/12452864/cannot-make-a-static-reference-to-the-non-static-type-myrunnable
		//http://bbs.csdn.net/topics/90235972
		List<Integer> l = new ArrayList<Integer>();
		int i = 0;
		//http://stackoverflow.com/a/363692
		while(i++ < nodeNum){
			l.add(r.nextInt(100) );
		}
		//http://stackoverflow.com/a/18441978
		Collections.sort(l);
		//http://stackoverflow.com/questions/9572795/convert-list-to-array-in-java
		//http://blog.csdn.net/guopengzhang/article/details/5497875
		tree.createBSTree((Integer[]) l.toArray(new Integer[l.size()]) );
	}
	private void createBSTTreeHelper(BSTreeNode<ValueType> rootNode,
			ValueType[] values, int startId, int endId) {
		if (startId > endId) {
			return;
		}
		int mid = startId + ((endId - startId)>>1);
		rootNode.data_ = values[mid];
		rootNode.leftChild_ = new BSTreeNode<ValueType>();
		createBSTTreeHelper(rootNode.leftChild_, values, startId, mid-1);
		rootNode.rightChild_ = new BSTreeNode<ValueType>();
		createBSTTreeHelper(rootNode.rightChild_, values, mid+1, endId);
	}
	public void setRootNode(BSTreeNode<ValueType> rootNode_) {
		this.rootNode_ = rootNode_;
	}
	public BSTreeNode<ValueType> getRootNode() {
		return rootNode_;
	}
	private BSTreeNode<ValueType> rootNode_;
	
	@SuppressWarnings("hiding")
	public class BSTreeNode<ValueType> {
		private ValueType data_;
		BSTreeNode<ValueType> leftChild_ = null;
		BSTreeNode<ValueType> rightChild_ = null;
		public void setData(ValueType data_) {
			this.data_ = data_;
		}
		public ValueType getData() {
			return data_;
		}
		public BSTreeNode<ValueType> getLeftChild() {
			return leftChild_;
		}
		public BSTreeNode<ValueType> getRightChild() {
			return rightChild_;
		}
	}

}
