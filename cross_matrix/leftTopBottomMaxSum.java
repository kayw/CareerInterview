//https://www.careercup.com/question?id=21423662
/*
Given an NxM (N rows and M columns) integer matrix with non-negative values (0..MAX_INT inclusive). What is the maximum sum from going top left (0, 0) to bottom right (N-1, M-1) ? The condition is that when you're at point (p, q), you can only move to either right (p, q+1) or down (p+1, q).
Expected time complexity O(N*M)
Expected space complexity O(N+M) 
*/

/*
The basic dynamic programming approach keeps the max so far for any given cell in a 2d array and
then at each position you check whether your current max for that cell plus
the value for the right cell / bottom cell is larger than the value currently in the right and bottom cell.
This takes N*M space. You can reduce this to O(N+M) space by realizing that you only ever need to keep the values for the current and the next row to calculate the values for the next row. 
*/

package a5;
/*
 * {{1,3,7,2,1},{1,4,7,6,4},{1,2,7,1,2},{5,4,2,10,7},{3,4,5,6,7}}
 */

public class leftTopBottomMaxSum {

	public static void main(String[] args) {
		int [][] matrix = 
		{	{2,3,4,1},
			{1,1,3,9},
			{2,2,3,1},
			{2,2,3,1}
		};

		findBestPath(matrix);
		findBestPath2(matrix);
	}

	public static void findBestPath(int [][] matrix)
	{
		int [][] cost = new int[matrix.length][matrix[0].length];
		int [][][] parent = new int[matrix.length][matrix[0].length][2];
		for(int i = 0; i < matrix.length; i++)
		{
			for(int j = 0; j < matrix[0].length; j++)
			{
				cost[i][j] = Integer.MIN_VALUE;
				parent[i][j] = new int[2];
			}
		}
		cost[0][0] = matrix[0][0];

		for(int i = 0; i < matrix.length; i++)
		{
			for(int j = 0; j < matrix[0].length; j++)
			{
				if(i+1 < matrix.length && cost[i][j] + matrix[i+1][j] > cost[i+1][j])
				{
					cost[i+1][j] = cost[i][j] + matrix[i+1][j] ;
					parent[i+1][j][0] = i;
					parent[i+1][j][1] = j;					
				}
				if(j+1 < matrix.length && cost[i][j] + matrix[i][j+1] > cost[i][j+1])
				{
					cost[i][j+1] = cost[i][j] + matrix[i][j+1] ;
					parent[i][j+1][0] = i;
					parent[i][j+1][1] = j;					
				}
			}
		}

		System.out.println("Max is " + cost[matrix.length-1][matrix[0].length-1]);
		int [] at = parent[matrix.length-1][matrix[0].length-1];
		System.out.print((matrix.length-1) + ":" + (matrix[0].length-1) + "(" + matrix[matrix.length-1][matrix[0].length-1] + "), ");
		while(!(at[0] == 0 && at[1] == 0))
		{
			System.out.print(at[0] + ":" + at[1] + "(" + matrix[at[0]][at[1]] + "), ");
			at = parent[at[0]][at[1]];
		}
		System.out.print(at[0] + ":" + at[1] + "(" + matrix[at[0]][at[1]] + "), ");
	}

	public static void findBestPath2(int [][] matrix)
	{
		int [][] cost = new int[2][matrix[0].length];
		cost[0][0] = matrix[0][0];

		for(int i = 0; i < matrix.length; i++)
		{
			int iUp = 0;
			int iAt = 0;
			if(i % 2 == 0)
			{
				iUp = 1;
				iAt = 0;
			}
			else
			{
				iUp = 0;
				iAt = 1;
			}
			for(int j = 0; j < matrix[0].length; j++)
			{
				if(i+1 < matrix.length && cost[iAt][j] + matrix[i+1][j] > cost[iUp][j])
				{
					cost[iUp][j] = cost[iAt][j] + matrix[i+1][j] ;
				}
				if(j+1 < matrix.length && cost[iAt][j] + matrix[i][j+1] > cost[iAt][j+1])
				{
					cost[iAt][j+1] = cost[iAt][j] + matrix[i][j+1] ;
				}
			}
		}
		if(matrix.length % 2 == 0)
		{
			System.out.println("Max is " + cost[1][matrix[0].length-1]);
		}
		else
		{
			System.out.println("Max is " + cost[0][matrix[0].length-1]);			
		}
	}

}
