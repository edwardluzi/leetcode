import static org.junit.Assert.assertTrue;

import org.junit.Test;

public class SolutionTest
{
	@Test
	public void test1()
	{
		String expected = "One Hundred Twenty Three";
		Solution solution = new Solution();
		String result = solution.numberToWords(123);
	
		assertTrue(expected.compareTo(result) == 0);
	}

	@Test
	public void test2()
	{
		String expected = "Twelve Thousand Three Hundred Forty Five";
		Solution solution = new Solution();
		String result = solution.numberToWords(12345);
	
		assertTrue(expected.compareTo(result) == 0);
	}

	@Test
	public void test3()
	{
		String expected = "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven";
		Solution solution = new Solution();
		String result = solution.numberToWords(1234567);
	
		assertTrue(expected.compareTo(result) == 0);
	}
	
	@Test
	public void test4()
	{
		String expected = "One Million Ten";
		Solution solution = new Solution();
		String result = solution.numberToWords(1000010);
	
		assertTrue(expected.compareTo(result) == 0);
	}
	
	@Test
	public void test5()
	{
		String expected = "One Hundred Twenty Three";
		Solution solution = new Solution();
		String result = solution.numberToWords(123);
	
		assertTrue(expected.compareTo(result) == 0);
	}
	
	@Test
	public void test6()
	{
		String expected = "One Hundred Thousand";
		Solution solution = new Solution();
		String result = solution.numberToWords(100000);
	
		assertTrue(expected.compareTo(result) == 0);
	}
}
