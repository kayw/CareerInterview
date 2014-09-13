import java.util.List;


//http://stackoverflow.com/questions/11831791/illegal-modifier-error-for-static-class
public /*static*/ class PostOrderArrayHelper {
	//http://stackoverflow.com/questions/936377/static-method-in-a-generic-class
	public static<T extends Comparable<T>> boolean isPostOrder(List<T> orderArray, int start, int end) {
		//http://stackoverflow.com/questions/7139200/nested-multiline-comments-in-java
//	if (false) {
//		if (start >= end){
//			return true;
//		}
//		int i = end - 1;
//		//http://stackoverflow.com/questions/18814182/the-type-of-the-expression-must-be-an-array-type-but-it-resolved-to-arraylist-t
//		while (/*orderArray.get(end) > orderArray.get(i)*/orderArray.get(end).compareTo(orderArray.get(i)) < 0 && i >= start) {
//			--i;
//		}
//		if (!isPostOrder(orderArray, i+1, end-1)) {
//			return false;
//		T[] stack = {Integer.MIN_VALUE, Integer.MAX_VALUE }; 
//		for (T t : orderArray) {
//		}
//		T[] stack = {Integer.MIN_VALUE, Integer.MAX_VALUE }; 
//		for (T t : orderArray) {
//		int j = ++i;
//		while (/*orderArray.get(end) < orderArray.get(i)*/orderArray.get(end).compareTo(orderArray.get(i)) > 0 && i >= start) {
//			--i;
//		}
//		return isPostOrder(orderArray, start, j);
//	}
	//http://blog.csdn.net/yx0628/article/details/24596563
		int middle = start;
		while(middle < end) {
			if (orderArray.get(middle).compareTo(orderArray.get(end) ) < 0) {
				++middle;
			}
			else {
				break;
			}
		}
		for (int i = middle; i < end; ++i) {
			if (orderArray.get(i).compareTo(orderArray.get(end) ) < 0) {
				return false;
			}
		}
		
		boolean leftPostorder = true;
		boolean rightPostorder = true;
		if (start < middle - 1) {
			leftPostorder = isPostOrder(orderArray, start, middle -1);
		}
		if (middle < end -1) {
			rightPostorder = isPostOrder(orderArray, middle, end - 1);
		}
		return (leftPostorder && rightPostorder);
	}
	
	//http://www.cnblogs.com/moor/archive/2011/03/29/1999109.html
	public static/*<T extends Comparable<T>>*/ boolean isPostOrder_norecur(Integer[] orderArray) {
		//http://stackoverflow.com/questions/14922270/how-is-this-illegal
		//http://stackoverflow.com/questions/8438879/expanding-an-array
		//http://stackoverflow.com/questions/14837185/how-can-we-dynamically-allocate-and-grow-an-array
		int[] stack = new int[orderArray.length + 2];
		stack[0] = Integer.MIN_VALUE;
		stack[1] = Integer.MAX_VALUE;
		//ArrayList<Integer> stack = new ArrayList<Integer>(Arrays.asList(Integer.MIN_VALUE, Integer.MAX_VALUE) );

		int top=1; //栈顶指针

		for(int i=orderArray.length-1; i>=0; --i)
		{
			if (orderArray[i]>=stack[top])        //如果不能插入到栈中，返回false
				return false;

			while (orderArray[i]<stack[top])       //在栈中查找第一个不大于a[i]的数
			{
				--top;
			}
			if (orderArray[i] == stack[top])       //如果啊a[i]与栈中元素相同返回false
				return false;

			//  把栈中比a[i]大的那个数向右移一个位置，把a[i]插到栈中
			top += 2;                   
			stack[top] = stack[top-1];
			stack[top-1] = orderArray[i];
		}

		return   true;
	}
	
	//http://my.oschina.net/u/1470003/blog/223599
	public static<T extends Comparable<T>> boolean isPostOrder_predicate(List<T> orderArray, int s, int e) {

		int i,j;
		if(s == e)
			return true; 

		for(i=0;i<e && orderArray.get(i).compareTo(orderArray.get(e)) < 0;i++);
		if(i != 0 && !isPostOrder_predicate(orderArray,s,i-1) )
			return false;

		for(j=i;j<e && orderArray.get(j).compareTo(orderArray.get(e)) > 0;j++);
		if(j==e && isPostOrder_predicate(orderArray,i,j-1) )
			return true;
		else
			return false;
	}
}
