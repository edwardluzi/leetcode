import static org.junit.Assert.assertTrue;

import org.junit.Test;

public class SolutionTest
{
	@Test
	public void test1()
	{
		String expected = "BACNC";
		Solution solution = new Solution();
		String result = solution.minWindow("ADCOBECODEBACNC", "ABCC");
	
		assertTrue(expected.compareTo(result) == 0);
	}
	
	@Test
	public void test2()
	{
		String expected = "aa";
		Solution solution = new Solution();
		String result = solution.minWindow("aa", "aa");
	
		assertTrue(expected.compareTo(result) == 0);
	}
}
