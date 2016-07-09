/*
 * http://www.mitbbs.com/article_t/JobHunting/33093381.html
 * 定义一个interface， 把node 和 list of node 定义在同一个interface下
 *
 * 这个interface里面只有一个method 就是 iterator
 * Interface NestedNodeList<E>
 * 然后，node的类型的iterator的实现是：
 * iterator里面有个bool变量
 * 如果这个node已经取过了，就是true，没有取过就是false
 * node iterator 的 hasnext()方法就是用这个bool来判断
 * next()的方法就返回 node的值并把这个bool的状态更新
 * 然后NodeList 用一个private 的list 放入 NestedNodeList 为interface的类型
 * 所以既可以放入node， 也可以放入里一个nested Nodelist本身
 * 然后NodeList的iterator就是 深度优先 dfs 的遍历这个list
 * recursive的call list里面的每个iterator
 *
 * Program an iterator for a List which may include nodes or List
 * {0, {1, 2}, 3, {4, {5, 6}}} Iterator returns 0 1 2 3 4 5 6
*/
package NestedIterator;

public interface NestedNodeList<E> extends Iterable<E> {

}


package NestedIterator;
import java.util.Iterator;
public class Node<E> implements NestedNodeList<E> {
	private E val;

	public Node(E val) {
		this.val = val;
	}

	@Override
	public Iterator<E> iterator() {
		return new NodeIterator();
	}

	private class NodeIterator implements Iterator<E> {
		private boolean iterated = false;

		@Override
		public boolean hasNext() {
			return !iterated;
		}

		@Override
		public E next() {
			if (hasNext()) {
				iterated = true;
				return val;
			}
			return null;
		}

	}

}


import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class NodeList<E> implements NestedNodeList<E> {
	private List<NestedNodeList<E>> nodeList;

	public NodeList() {
		this.nodeList = new ArrayList<>();
	}

	@Override
	public Iterator<E> iterator() {
		return new NodeListIterator();
	}

	public void add(NestedNodeList<E> nodes) {
		nodeList.add(nodes);
	}

	private class NodeListIterator implements Iterator<E> {
		private int idx = 0;
		Iterator<E> iter;

		@Override
		public boolean hasNext() {
			if (idx >= nodeList.size())
				return false;
			if (iter == null)
				iter = nodeList.get(idx).iterator();

			if (iter.hasNext())
				return true;

			idx += 1;
			if (idx >= nodeList.size())
				return false;
			iter = nodeList.get(idx).iterator();
			return iter.hasNext();
		}

		@Override
		public E next() {
			if (hasNext()) {
				return iter.next();
			}
			return null;
		}

	}

	public static final void main(String[] args) {

		NodeList<Integer> list0 = new NodeList<>();
		NodeList<Integer> list1 = new NodeList<>();
		NodeList<Integer> list2 = new NodeList<>();
		NodeList<Integer> list3 = new NodeList<>();
		Node<Integer> node0 = new Node<>(0);
		Node<Integer> node1 = new Node<>(1);
		Node<Integer> node2 = new Node<>(2);
		Node<Integer> node3 = new Node<>(3);
		Node<Integer> node4 = new Node<>(4);
		Node<Integer> node5 = new Node<>(5);
		Node<Integer> node6 = new Node<>(6);
		list3.add(node5);
		list3.add(node6);
		list2.add(node4);
		list2.add(list3);
		list2.add(node4);
		list2.add(list3);
		list1.add(node1);
		list1.add(node2);
		list0.add(node0);
		list0.add(list1);
		list0.add(node3);
		list0.add(list2);

		for (int i : list0) {
			System.out.println(i);
		}

	}

}

```c++
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>

using namespace std;

class NestedInteger {
public:
    NestedInteger(int i) : integer(i), isInt(true) {}
    NestedInteger(vector<NestedInteger> l) : nestedList(l), isInt(false) {}
   
    // Return true if this NestedInteger holds a single integer, rather than
a nested list.
    bool isInteger() {
        return isInt;
    }
   
    // Return the single integer that this NestedInteger holds, if it holds
a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() {
        return integer;
    }

    // Return the nested list that this NestedInteger holds, if it holds a
nested list
    // The result is undefined if this NestedInteger holds a single integer
    vector<NestedInteger> &getList() {
        return nestedList;
    }

    bool isInt;
    int integer;
    vector<NestedInteger> nestedList;
};

class NestedIntegerIterator {
public:
    NestedIntegerIterator(vector<NestedInteger> &nestedList) {
        s.push({nestedList.begin(), nestedList.end()});
    }
   
    int next() {
        return (s.top()[0]++)->getInteger();
    }
   
    bool hasNext() {
        while (!s.empty()) {
            while (!s.empty() && s.top()[0] == s.top()[1]) {
                s.pop();
                if (!s.empty())
                    ++s.top()[0];
            }
           
            if (!s.empty() && s.top()[0]->isInteger())
                return true;
           
            while (!s.empty() && !s.top()[0]->isInteger())
                s.push({s.top()[0]->getList().begin(), s.top()[0]->getList()
.end()});
        }
        return false;
    }

private:
    stack<vector<vector<NestedInteger>::iterator>> s;
};

int main()
{
    {
        vector<NestedInteger> l = {NestedInteger(0), NestedInteger({
NestedInteger(1), NestedInteger(2)}), NestedInteger(3), NestedInteger({
NestedInteger(4), NestedInteger({NestedInteger(5), NestedInteger(6)})})};
        NestedIntegerIterator ni(l);
        while (ni.hasNext())
            cout << ni.next() << endl;
    }
    return 0;
}
```
