

import static org.junit.Assert.*;

import java.util.Arrays;
import java.util.List;

import org.junit.Test;
//http://www.vogella.com/tutorials/JUnit/article.html

public class IsPostOrderTest {

	//http://stackoverflow.com/questions/8068470/java-initialize-an-int-array-in-a-constructor
	//http://stackoverflow.com/questions/1005073/initialization-of-an-arraylist-in-one-line
	@Test
	public void twoSubTreeSuccess() {
		List<Integer> fromBookSeq = Arrays.asList(5, 7, 6, 9, 11, 10, 8);
		assertTrue(PostOrderArrayHelper.isPostOrder(fromBookSeq, 0, fromBookSeq.size() - 1) );
		assertTrue(PostOrderArrayHelper.isPostOrder_predicate(fromBookSeq, 0, fromBookSeq.size() - 1) );
	}

	@Test
	public void singleSubTreeSuccess() {
		List<Integer> singleLinkTreeOrder = Arrays.asList(3,2,1);
		assertTrue(PostOrderArrayHelper.isPostOrder(singleLinkTreeOrder, 0, singleLinkTreeOrder.size() - 1) );
		assertTrue("first determine the start == end", PostOrderArrayHelper.isPostOrder_predicate(singleLinkTreeOrder, 0, singleLinkTreeOrder.size() -1) );
	}
	
	@Test
	public void subTreeOrderFail(){
		List<Integer> nonPostOrderArray = Arrays.asList(11, 7, 9, 8);
		assertFalse("not a post order binary tree", PostOrderArrayHelper.isPostOrder(nonPostOrderArray, 0, nonPostOrderArray.size() - 1) );
	}
	
	@Test
	public void nonRecurSuccessAndFail() {
		List<Integer> fromBookSeq = Arrays.asList(5, 7, 6, 9, 11, 10, 8);
		assertTrue(PostOrderArrayHelper.isPostOrder_norecur((Integer[])fromBookSeq.toArray() ) );
		Integer[] nonPostOrderArray = {11, 7, 9, 8};
		assertFalse("not a post order binary tree", PostOrderArrayHelper.isPostOrder_norecur(nonPostOrderArray) );
		Integer[] nonPostOrderSub = {11, 7, 12};
		assertFalse("not a post order binary tree", PostOrderArrayHelper.isPostOrder_norecur(nonPostOrderSub) ); // ==> wrong non-recursive implementation
	}
}
