import static org.junit.Assert.*;

import java.util.Arrays;
import java.util.List;

import org.junit.Test;

public class SolutionTest
{
	@Test
	public void test1()
	{
		Integer[] expected = { 1, 2, 3, 6, 9, 8, 7, 4, 5 };

		int[][] matrix = new int[][] { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };

		Solution solution = new Solution();

		List<Integer> result = solution.spiralOrder(matrix);

		assertTrue(Arrays.equals(expected, result.toArray(new Integer[expected.length])));
	}

	@Test
	public void test2()
	{
		Integer[] expected = { 1, 2, 3, 6, 5, 4 };

		int[][] matrix = new int[][] { { 1, 2, 3 }, { 4, 5, 6 } };

		Solution solution = new Solution();

		List<Integer> result = solution.spiralOrder(matrix);

		assertTrue(Arrays.equals(expected, result.toArray(new Integer[expected.length])));
	}

	@Test
	public void test3()
	{
		Integer[] expected = { 1 };

		int[][] matrix = new int[][] { { 1 } };

		Solution solution = new Solution();

		List<Integer> result = solution.spiralOrder(matrix);

		assertTrue(Arrays.equals(expected, result.toArray(new Integer[expected.length])));
	}
}
