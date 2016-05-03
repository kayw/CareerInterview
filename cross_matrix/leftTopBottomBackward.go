package career_interview

import (
	"fmt"
	"math"
)

//http://stackoverflow.com/questions/32630503/find-path-cross-matrix-with-max-sum-forward-then-backward
//simpler than adventure, only two paths
//walk from upper left to lower right, then walk backward, visited node can't be walked again from smartstudy
func emptyMatrix(mat [][]int, rows, cols int) {
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			mat[i][j] = 0
		}
	}
}
func setNextRowMax(row, coli, colj int, matrixDp [2][][]int, matrix [][]int) {
	nextSum := matrixDp[row&1][coli][colj] + matrix[row+1][coli] + matrix[row+1][colj]
	if nextSum > matrixDp[(row+1)&1][coli][colj] {
		matrixDp[(row+1)&1][coli][colj] = nextSum
	}
}
func SumBackPathDP(matrix [][]int) int {
	var columns int
	rows := len(matrix)
	if rows > 0 {
		columns = len(matrix[0])
	}
	if rows <= 2 && columns <= 2 {
		sum := 0
		for _, cols := range matrix {
			for _, num := range cols {
				sum += num
			}
		}
		return sum
	}
	var matrixDp [2][][]int
	for i := 0; i < 2; i++ {
		matrixDp[i] = make([][]int, rows)
		for j := range matrixDp[i] {
			matrixDp[i][j] = make([]int, columns)
		}
	}
	//matrixDp[0][0][1] = matrix[0][1]
	matrixDp[0][0][1] = matrix[0][0] + matrix[0][1]
	for r := 0; r < rows; r++ {
		// leftmost move right
		for i := 0; i+1 < columns; i++ {
			for j := i + 1; j < columns; j++ {
				nextSum := matrixDp[(r)&1][i][j] + matrix[r][i+1]
				if nextSum > matrixDp[(r)&1][i+1][j] {
					matrixDp[(r)&1][i+1][j] = nextSum
				}
			}
		}
		// rightmost move right
		for i := 0; i < columns; i++ {
			for j := i + 1; j+1 < columns; j++ {
				nextSum := matrixDp[(r)&1][i][j] + matrix[r][j+1]
				if nextSum > matrixDp[(r)&1][i][j+1] {
					matrixDp[(r)&1][i][j+1] = nextSum
				}
			}
		}
		if r+1 < rows {
			emptyMatrix(matrixDp[(r+1)&1], rows, columns)
			// move down one row
			for i := 0; i < columns; i++ {
				for j := i + 1; j < columns; j++ {
					setNextRowMax(r, i, j, matrixDp, matrix)
				}
			}
		}
		for _, m2d := range matrixDp {
			for _, cols := range m2d {
				for _, elem := range cols {
					fmt.Printf("%d ", elem)
				}
				fmt.Print("\n")
			}
			fmt.Print("\n")
		}
		fmt.Print("\n")
	}
	/*
		for _, m2d := range matrixDp {
			for _, cols := range m2d {
				for _, elem := range cols {
					fmt.Printf("%d ", elem)
				}
				fmt.Print("\n")
			}
			fmt.Print("\n")
		}
	*/
	return matrixDp[(rows-1)&1][columns-2][columns-1]
}

func SumPathMirror(matrix [][]int) int {
	mirrorMat := make([][]int, len(matrix)*2-1)
	for i := 0; i < len(matrix)*2-1; i++ {
		mirrorMat[i] = make([]int, len(matrix[0])*2-1)
	}
	for i := 0; i < len(matrix); i++ {
		for j, num := range matrix[i] {
			mirrorMat[i][j] = num
		}
	}
	for i := 0; i < len(matrix); i++ {
		for j := len(matrix[0]); j < len(mirrorMat[0]); j++ {
			mirrorMat[i][j] = math.MinInt64
		}
	}
	for i := len(matrix); i < len(mirrorMat); i++ {
		for j := 0; j < len(matrix[0])-1; j++ {
			mirrorMat[i][j] = math.MinInt64
		}
	}
	for i := len(matrix) - 1; i < len(mirrorMat); i++ {
		for j := len(matrix[0]) - 1; j < len(mirrorMat[0]); j++ {
			mirrorMat[i][j] = matrix[len(mirrorMat)-i-1][len(mirrorMat[0])-j-1]
		}
	}
	for i := 0; i < len(mirrorMat); i++ {
		for j := 0; j < len(mirrorMat[0]); j++ {
			fmt.Printf("%d ", mirrorMat[i][j])
		}
		fmt.Print("\n")
	}
	var dp [2][]int
	for i := 0; i < 2; i++ {
		dp[i] = make([]int, len(mirrorMat[0]))
	}
	dp[0][0] = mirrorMat[0][0]
	for r := 0; r < len(mirrorMat); r++ {
		for col := 0; col < len(mirrorMat[0]); col++ {
			// can't mark mirrored postion as visited easily
			if r+1 < len(mirrorMat) && dp[(r+1)&1][col] < dp[r&1][col]+mirrorMat[r+1][col] {
				dp[(r+1)&1][col] = dp[r&1][col] + mirrorMat[r+1][col]
				//			mirrorMat[len(mirrorMat)-r-1-1][len(mirrorMat[0])-col-1] = math.MinInt64

			}
			if col+1 < len(mirrorMat[0]) && dp[r&1][col+1] < dp[r&1][col]+mirrorMat[r][col+1] {
				dp[r&1][col+1] = dp[r&1][col] + mirrorMat[r][col+1]
				//			mirrorMat[len(mirrorMat)-r-1][len(mirrorMat[0])-col-1-1] = math.MinInt64
			}
		}
		/*
			for i := 0; i < 2; i++ {
				for _, dpv := range dp[i] {
					fmt.Printf("%d ", dpv)
				}
				fmt.Print("\n")
			}
			for i := 0; i < len(mirrorMat); i++ {
				for j := 0; j < len(mirrorMat[0]); j++ {
					fmt.Printf("%d ", mirrorMat[i][j])
				}
				fmt.Print("\n")
			}
		*/
	}
	return dp[(len(mirrorMat)-1)&1][len(mirrorMat[0])-1]
}

//https://github.com/yinyinbigdata/mytopcoder/blob/master/topcoder-lesson/Dynamic%20Programming/dpsulotion.cpp
/*////StarAdventure
vector<string> board;
int dp[2][50+5][50+5][50+5];

class StartAdventure{
public:
	int getScore(int x,int y){
		return board[x-1][y-1]-'0';
	}
	int getScore(int x,int y1,int y2, int y3){
		return getScore(x,y1)+getScore(x,y2)+getScore(x,y3);
	}
	int mostStars(vector<string> level){
		int rows=level.size();
		int cols=level[0].size();
		board=level;
		if(cols<=3){
			int res=0;
			for(int i=1;i<=rows;++i)
			  for(int j=1;j<=cols;++j)
				rew+=getScore(i,j);
			return res;
		}
		memset(dp,0,sizeof(dp));
		for(int r=1;r<=rows;++r){
			memset(dp[(r+1)&1],0,sizeof(dp[(r+1)&1]));
			// 0)Move down
			for(int i=1;i<=cols;++i)
			  for(int j=i+1;j<=cols;++j)
				for(int k=j+1;k<=cols;++k)
				  dp[(r+1)&1][i][j][k]>?=dp[r&1][i][j][k]+getScore(r,i,j,k);
			// 1) Move the leftmost column.
			for(int i=1;i<=cols;++i)
			  for(int j=i+2;j<=cols;++j)
				for(int k=j+1;k<=cols;++k)
				  dp[(r+1)&1][i+1][j][k]>?=dp[(r+1)&1][i][j][k]+getScore(r,i+1);
			// 2) Move the middle column
			for(int i=1;i<=cols;++i)
			  for(int j=i+1;j<=cols;++j)
				for(int k=j+2;k<=cols;++k)
				  dp[(r+1)&1][i][j+1][k]>?=dp[(r+1)&1][i][j][k]+getScore(r,j+1);
			// 3) Move the right column
			for(int i=1;i<=cols;++i)
			  for(int j=i+1;j<=cols;++j)
				for(int k=j+1;k+1<=cols;++k)
				  dp[(r+1)&1][i][j][k+1]>?=dp[(r+1)&1][i][j][k]+getSrore(r,k+1);
		}
		return dp[(rows+1)&1][cols-2][cols-1][cols];
	}
};

//StarAdventure
using System; using System.Collections; using System.Text;
public class StarAdventure {
	 public int mostStars(string[] L) {
int X=L[0].Length, Y=L.Length, XY=X+Y;
int[,,] best = new int[X,X,X]; // best score with paths at the given X positions
int[,,] b2 = new int[X,X,X];
for (int A=0; A<X; A++) for (int B=0; B<X; B++) for (int C=0; C<X; C++)
 best[A,B,C] = -999999999;
best[0,0,0] = 0;
for (int t=1; t<=X+Y-2; t++)
 {
 for (int A=0; A<X; A++) for (int B=0; B<X; B++) for (int C=0; C<X; C++)
  {
  int aa = t-A, bb=t-B, cc=t-C;
  if (aa < 0 || bb < 0 || cc < 0 || aa >= Y || bb >= Y || cc >= Y) continue;
  int bestHere = 0;
  int delta = (int)L[aa][A] - 48;
  if (B != A) delta += (int)L[bb][B] - 48;
  if (C != A && C != B) delta += (int)L[cc][C] - 48;
  if ( A>0 &&  B>0 &&  C>0) bestHere = Math.Max(bestHere, best[A-1, B-1, C-1] + delta);
  if ( A>0 &&  B>0 && cc>0) bestHere = Math.Max(bestHere, best[A-1, B-1, C  ] + delta);
  if ( A>0 && bb>0 &&  C>0) bestHere = Math.Max(bestHere, best[A-1, B,   C-1] + delta);
  if ( A>0 && bb>0 && cc>0) bestHere = Math.Max(bestHere, best[A-1, B,   C  ] + delta);
  if (aa>0 &&  B>0 &&  C>0) bestHere = Math.Max(bestHere, best[A,   B-1, C-1] + delta);
  if (aa>0 &&  B>0 && cc>0) bestHere = Math.Max(bestHere, best[A,   B-1, C  ] + delta);
  if (aa>0 && bb>0 &&  C>0) bestHere = Math.Max(bestHere, best[A,   B,   C-1] + delta);
  if (aa>0 && bb>0 && cc>0) bestHere = Math.Max(bestHere, best[A,   B,   C  ] + delta);
  b2[A,B,C] = bestHere;
  }

 int[,,] temp = best; best = b2; b2 = temp;
 }

return best[X-1,X-1,X-1];
}


//StarAdventure
int mem[102][51][51][51];

vs l;

int doit(int x1, int y1, int x2, int y2, int x3, int y3)
{
  if (x1>=l[0].sz||y1>=l.sz||x2>=l[0].sz||y2>=l.sz||x3>=l[0].sz||y3>=l.sz) return 0;
  int m=x1+y1;
  if (mem[m][x1][x2][x3]) return mem[m][x1][x2][x3]-1;

  int ret=l[y1][x1]-'0';
  if (mp(x1,y1)!=mp(x2,y2)) ret += l[y2][x2]-'0';
  if (mp(x1,y1)!=mp(x3,y3)&&mp(x2,y2)!=mp(x3,y3)) ret += l[y3][x3]-'0';

  int add=0;
  ri(2) rj(2) rk(2)
  add >?= doit((i?x1+1:x1),(i?y1:y1+1),(j?x2+1:x2),(j?y2:y2+1),(k?x3+1:x3),(k?y3:y3+1));

  ret += add;
  mem[m][x1][x2][x3] = ret + 1;

  return ret;
}

class StarAdventure {
  public:
  int mostStars(vector <string> level) {

// BEGIN CUT HERE
    static bool s_FirstTime = true; if (s_FirstTime) { s_FirstTime = false; run_test(-1); }
// END CUT HERE
bz(mem);

l=level;

return doit(0,0,0,0,0,0);

  }*/

//https://www.topcoder.com/community/data-science/data-science-tutorials/dynamic-programming-from-novice-to-advanced/
//http://massivealgorithms.blogspot.com/2015/12/staradventure-topcoder.html
/* lower right means bottom right
The latest version of your favorite adventure game has just been released. On each level you search for stars that earn you points. Simply moving over a location containing stars allows you to acquire them. To help you on your journey, you are given an overhead map of the level in a String[]. Each character in level describes the number of stars at that location. You begin in the upper left spot of the map (character 0 of element 0 of level). On the current stage you must move according to the following rules:

1) On the first pass you may only move downward or rightward each move (not diagonally) until you reach the lower right corner.
2) The second pass begins in the lower right corner where the first pass ended, and proceeds back to the beginning using only upward and leftward steps (not diagonal).
3) The final pass, like the first pass, begins in the upper left corner and proceeds to the lower right corner using only rightward and downward (not diagonal) steps.

Once the stars on a spot are claimed, they cannot be claimed again on a future pass. Return the largest possible number of stars that can be acquired.
0)


{"01",
"11"}

Returns: 3

1)


{"0999999999"
,"9999999999"
,"9999999999"
,"9999999999"
,"9999999999"
,"9999999999"
,"9999999999"
,"9999999999"
,"9999999999"
,"9999999999"}

Returns: 450

2)


{"012"
,"012"
,"012"
,"012"
,"012"
,"012"
,"012"}

Returns: 21

3)


{"0123456789",
"1123456789",
"2223456789",
"3333456789",
"4444456789",
"5555556789",
"6666666789",
"7777777789",
"8888888889",
"9999999999"}

Returns: 335
*/
//https://github.com/gabesoft/topc/blob/master/src.archive.1/dynamic/StarAdventure.java

//http://stackoverflow.com/questions/26011746/maximum-sum-when-going-through-matrix-for-number-of-turns  related search problem
/*
public static int travel (int i, int j,int k)
{
	//value temporarily takes the position's value
	int value;

	//if position is out of matrix bounds
	if(i>=x||j>=y||i<0||j<0)
	{
		return 0;
	}
	else
	{
		//makes the value in point (i,j) = 0
		value=M[i][j];
		M[i][j]=0;

		//if the number of turns has been reached
		if(k==turns)
		{
			//restores value at position
			M[i][j]=value;
			return M[i][j];
		}
		else
		{
			int sum = 0;
			//loop for going to all 8 neighbors
			for(int line=-1;line<2;line++)
			{
				for(int col=-1;col<2;col++)
				{
					//if the position is the same
					if(!(col==0&&line==0))
					{
						sum=Math.max(travel(i+line,j+col,k+1), sum);
					}
				}
			}

			//restores value at position
			M[i][j]=value;

			//returns sum so far
			return sum+M[i][j];
		}
	}
}
*/
