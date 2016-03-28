public class Solution
{
	private static final String[] units = new String[] { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
			"Eight", "Nine" };
	private static final String[] teens = new String[] { "", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
			"Sixteen", "Seventeen", "Eighteen", "Nineteen" };
	private static final String[] tens = new String[] { "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty",
			"Seventy", "Eighty", "Ninety" };
	private static final String[] thousands = new String[] { "", "Thousand", "Million", "Billion" };

	private static final String hundred = "Hundred";
	private static final String zero = "Zero";

	public String numberToWords(int num)
	{
		if (num == 0)
		{
			return zero;
		}

		String representation = "";
		int thousandIndex = 0;

		while (num > 0)
		{
			int mod = num % 1000;
			num = num / 1000;

			if (mod != 0)
			{
				String r = "";

				if (mod / 100 > 0)
				{
					r = units[mod / 100] + " " + hundred;
				}

				mod = mod % 100;

				if (mod / 10 > 0)
				{
					if (mod % 10 == 0)
					{
						r += " " + tens[mod / 10];
					}
					else
					{
						if (mod >= 11 && mod <= 19)
						{
							r += " " + teens[mod - 10];
						}
						else
						{
							r += " " + tens[mod / 10] + " " + units[mod % 10];
						}
					}
				}
				else if(mod > 0)
				{
					r += " " + units[mod];
				}

				r += " " + thousands[thousandIndex];

				r = r.trim();

				representation = r + " " + representation;
			}

			thousandIndex++;
		}

		return representation.trim();
	}
}