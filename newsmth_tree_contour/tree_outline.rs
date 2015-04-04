给个精确定义，没有左兄弟的节点是左边界，没有右兄弟的节点是右边界，左右儿子缺了一
个的是底边界。

先输出根，接着第1层左边，第二层左边，第n层左边。
然后从左向右输出底边（不一定同层），底边左右精确定义没想好，但这个不会有歧义，你
肯定懂得。
最后第m层右边，m-1层右边，最后第一层右边，结束。

重复节点只打印一次。比如根节点既是左边又是右边，最后不打

左右的精确定义：中序遍历先出来的节点是后面的左边

根和叶子很好判断，对于边节点，可以对于遍历函数传入两个leftmost和rightmost参数，
任意为真即可打印。子节点遍历时，左子树传入leftmost和false，右子树传入false和
rightmost即可。

         0
        / \
       1   2
      / \ / \
     3  4 5  6
            / \
           7   8
0 1 3 4 7 8 6 2

但是这个没啥难度啊。先广度遍历一遍，标出每一层的第一个节点和最后一个节点?
然后深度遍历，碰到标记或孩子数不为2的节点就输出。。

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *left;
    struct node *right;
    int value;
} node;

static void traversal(node *root);

static void root_first(node *node, int leftmost);
static void root_last(node *node, int rightmost);

static node *generate_tree(int count);
static void print(node *node);

int main(void)
{
    node *root = generate_tree(8);

    traversal(root);

    return 0;
}

static void traversal(node *root)
{
    print(root);
    root_first(root->left, 1);
    root_last(root->right, 1);
#modifed
      if (node == NULL) {
          return;
      }

      if (node->left == NULL) {
          print(node);
          traversal(node->right, 0, rightmost);
      } else if (node->right == NULL) {
          traversal(node->left, leftmost, 0);
          print(node);
      } else {
          if (leftmost == 1) {
              print(node);
          }

          traversal(node->left, leftmost, 0);
          traversal(node->right, 0, rightmost);

          if (rightmost == 1) {
              print(node);
          }
      }
#end
}

static void root_first(node *node, int leftmost)
{
    if (node == NULL) {
        return;
    }

    if (leftmost == 1 || (node->left == NULL && node->right == NULL)) {
        print(node);
    }

    root_first(node->left, leftmost);
    root_first(node->right, 0);

}

static void root_last(node *node, int rightmost)
{
    if (node == NULL) {
        return;
    }

    root_last(node->left, 0);
    root_last(node->right, rightmost);

    if (rightmost == 1 || (node->left == NULL || node->right == NULL)) {
        print(node);
    }
}

static node *generate_tree(int count)
{
    node *nodes = (node *)malloc(count * sizeof(node));
    int i = 0;

    for (i = 0; i < count; ++i) {

        nodes[i].value = i;
        if (2 * i + 1 < count) {
            nodes[i].left = &nodes[2 * i + 1];
        } else {
            nodes[i].left = NULL;
        }
        if (2 * i + 2 < count) {
            nodes[i].right = &nodes[2 * i + 2];
        } else {
            nodes[i].right = NULL;
        }
    }

    return nodes;
}

static void print(node *node)
{
    printf("v = %d\n", node->value);
}

          0
         / \
        1   2
       / \ / \
      3  4 5  6
            \
             8
    1                1
     \              /
     2             2
     / \          / \
    3  4         3   4          1234

if (leftmost) {
 先序遍历
}
else if (not rightmost) {
  中序遍历//过滤左右儿子都有的节点。
}
else {
  后序遍历 
}

    1
   /  \
  2   3
   \
    4
    /\
   5 6
124563

这题的终极释义就一个：你拿个铅笔自己围绕这颗树画一圈，先经过哪个节点就输出哪个节点。

void traverse(Node node, boolean left, boolean right) {
  boolean left_left = false;
  boolean left_right = false;
  boolean right_left = false;
  boolean right_right = false;

  if (node.left == null) {
       if (node.right == null) {
              //没有儿子，只处理好自己就ok了
       }
       else {
             right_left = left
             right_right = right;
       }
  }
  else {
       if (right == null) {
             left_left = left;
             left_right = right;
       }
       else {
            if (left) {
                 left_left = left;
                 left_right = false;
            }
            if (right) {
                right_left = false;
                right_right = right;
            }
       }
  }
}


           0
        /    \
       1      2
      / \    / \
     3   4  5   6
           /\
          7  8
         /\  /\
        9 10 11 12

对节点5 leftmost和rightmost同时为false，所以只有9 10 11 12会打印出来。
但是如果删除节点6的话，按照你的算法，对于节点5 rightmost为true，会把5和8多打印出
按照“轮廓”的常识，7算左轮廓，8算右轮廓  leftmost和rightmost的处理得改。

我觉得我的伪代码也不成立（好像也是成立的，待会儿仔细想想）。
合理的顺序应该是0 1 3 4 7 9 10 11 12 8 6

对于你说的这种情况，可以定义一个简单的“边界”节点条件，即：
当该节点的左右兄弟和左右子树不同时存在。

这种判定条件的话，肯定需要额外的数据结构来存储节点的左右兄弟信息。

