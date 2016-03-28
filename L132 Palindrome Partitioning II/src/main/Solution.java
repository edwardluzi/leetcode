import java.util.Arrays;
import java.util.LinkedList;

public class Solution
{
	private boolean[][] pattern = null;

	public int minCut(String s)
	{
		int length = s.length();

		if (length <= 1)
		{
			return 0;
		}

		this.pattern = new boolean[length][length];

		for (int right = 0; right < length; right++)
		{
			for (int left = right; left >= 0; left--)
			{
				if (s.charAt(left) == s.charAt(right) && (left + 1 > right - 1 || this.pattern[left + 1][right - 1]))
				{
					this.pattern[left][right] = true;
				}
			}
		}

		return bfs();
	}

	private int bfs()
	{
		int len = this.pattern.length;
		int[] minCuts = new int[len + 1];
		Arrays.fill(minCuts, Integer.MAX_VALUE);

		LinkedList<Integer> queue = new LinkedList<Integer>();

		minCuts[0] = 0;
		queue.addLast(0);

		while (queue.size() > 0)
		{
			int pos = queue.removeFirst();
			int dist = minCuts[pos] + 1;

			for (int stop = pos; stop < len; stop++)
			{
				if (this.pattern[pos][stop])
				{
					if (minCuts[stop + 1] > dist)
					{
						minCuts[stop + 1] = dist;

						if (stop + 1 != len)
						{
							queue.addLast(stop + 1);
						}
					}
				}
			}
		}

		return minCuts[len] - 1;
	}
}