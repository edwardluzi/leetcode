import java.util.ArrayList;
import java.util.List;

public class Solution
{
	private final int leftward = 0;
	private final int rightward = 1;
	private final int topward = 2;
	private final int downward = 3;

	public List<Integer> spiralOrder(int[][] matrix)
	{
		List<Integer> spiralList = new ArrayList<Integer>();

		int rows = matrix.length;

		if (rows > 0)
		{
			int cols = matrix[0].length;

			if (cols > 0)
			{
				int row = 0;
				int col = 0;

				int left = 0;
				int top = 0;
				int right = cols - 1;
				int bottom = rows - 1;

				int direction = rightward;

				while (left <= right && top <= bottom)
				{
					spiralList.add(matrix[row][col]);

					switch (direction)
					{
						case rightward:
						{
							if (col < right)
							{
								col++;
							}
							else
							{
								top++;
								row++;
								direction = downward;
							}

							break;
						}
						case leftward:
						{
							if (col > left)
							{
								col--;
							}
							else
							{
								bottom--;
								row--;
								direction = topward;
							}

							break;
						}
						case topward:
						{
							if (row > top)
							{
								row--;
							}
							else
							{
								left++;
								col++;
								direction = rightward;
							}

							break;
						}
						default:
						{
							if (row < bottom)
							{
								row++;
							}
							else
							{
								right--;
								col--;
								direction = leftward;
							}

							break;
						}
					}
				}
			}
		}

		return spiralList;
	}
}
