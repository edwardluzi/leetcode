#include "stdafx.h"

#include <stddef.h>
#include <cstdio>
#include <string>

using namespace std;

enum State
{
	Unknown, FirstNumber, FollowedNumber, FirstDecimal, FollowedDecimal
};

class Solution
{
public:

	static bool isNumber(string s)
	{
		string decimal;
		string exponent;

		trim(s);

		if (!readDecimal(s, decimal))
		{
			return false;
		}

		if (decimal == "+." || decimal == "-." || decimal == ".")
		{
			return false;
		}

		if (s.length() > 0)
		{
			if (s.at(0) == 'e' || s.at(0) == 'E')
			{
				s.erase(s.begin());

				if (!readInteger(s, exponent, true, true))
				{
					return false;
				}

				return s.length() == 0;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}

	static bool readInteger(string& s, string& value, bool allowMinus, bool allowPlus)
	{
		State state = Unknown;
		size_t length = s.length();
		size_t index = 0;

		for (; index < length; index++)
		{
			char token = s[index];

			switch (state)
			{
				case Unknown:
				{
					switch (token)
					{
						case '-':
						{
							if (!allowMinus)
							{
								return false;
							}
							state = FirstNumber;
							value.push_back(token);
							break;
						}
						case '+':
						{
							if (!allowPlus)
							{
								return false;
							}
							state = FirstNumber;
							value.push_back(token);
							break;
						}
						default:
						{
							if (isNumber(token))
							{
								state = FollowedNumber;
								value.push_back(token);
							}
							else
							{
								return false;
							}
						}
					}

					break;
				}
				case FirstNumber:
				{
					if (isNumber(token))
					{
						state = FollowedNumber;
						value.push_back(token);
					}
					else
					{
						return false;
					}

					break;
				}
				case FollowedNumber:
				{
					if (isNumber(token))
					{
						state = FollowedNumber;
						value.push_back(token);
					}
					else
					{
						s.erase(0, index);
						return true;
					}

					break;
				}
			}
		}

		s.erase(0, index);

		return state == FollowedNumber;
	}

	static bool readDecimal(string& s, string& value)
	{
		State state = Unknown;
		size_t length = s.length();
		size_t index = 0;

		for (; index < length; index++)
		{
			char token = s[index];

			switch (state)
			{
				case Unknown:
				{
					switch (token)
					{
						case '+':
						{
							state = FirstNumber;
							value.push_back(token);
							break;
						}
						case '-':
						{
							state = FirstNumber;
							value.push_back(token);
							break;
						}
						case '.':
						{
							state = FirstDecimal;
							value.push_back(token);
							break;
						}
						default:
						{
							if (isNumber(token))
							{
								state = FollowedNumber;
								value.push_back(token);
							}
							else
							{
								return false;
							}
						}
					}
					break;
				}
				case FirstNumber:
				{
					switch (token)
					{
						case '.':
						{
							state = FirstDecimal;
							value.push_back(token);
							break;
						}
						default:
						{
							if (isNumber(token))
							{
								state = FollowedNumber;
								value.push_back(token);
							}
							else
							{
								return false;
							}

							break;
						}
					}

					break;
				}
				case FollowedNumber:
				{
					switch (token)
					{
						case '.':
						{
							state = FirstDecimal;
							value.push_back(token);
							break;
						}
						default:
						{
							if (isNumber(token))
							{
								state = FollowedNumber;
								value.push_back(token);
							}
							else
							{
								s.erase(0, index);
								return true;
							}

							break;
						}
					}

					break;
				}
				case FirstDecimal:
				{
					switch (token)
					{
						case '.':
						{
							return false;
						}
						default:
						{
							if (isNumber(token))
							{
								state = FollowedDecimal;
								value.push_back(token);
							}
							else
							{
								s.erase(0, index);
								return true;
							}
						}
					}

					break;
				}
				case FollowedDecimal:
				{
					switch (token)
					{
						case '.':
						{
							return false;
						}
						default:
						{
							if (isNumber(token))
							{
								state = FollowedDecimal;
								value.push_back(token);
							}

							else
							{
								s.erase(0, index);
								return true;
							}

							break;
						}
					}

					break;
				}
			}
		}

		s.erase(0, index);

		return state != Unknown;
	}

	static inline bool isNumber(char c)
	{
		return c >= '0' && c <= '9';
	}

	static inline void ltrim(string& s)
	{
		s.erase(0, s.find_first_not_of(' '));
	}

	static inline void rtrim(string& s)
	{
		s.erase(s.find_last_not_of(' ') + 1, s.length());
	}

	static inline void trim(string& s)
	{
		ltrim(s);
		rtrim(s);
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	string s = " 0  ";
	printf("%s ==> %s\n", s.c_str(), Solution::isNumber(s) ? "True" : "False");

	s = " 0.1 ";
	printf("%s ==> %s\n", s.c_str(), Solution::isNumber(s) ? "True" : "False");

	s = "abc";
	printf("%s ==> %s\n", s.c_str(), Solution::isNumber(s) ? "True" : "False");

	s = "1 a";
	printf("%s ==> %s\n", s.c_str(), Solution::isNumber(s) ? "True" : "False");

	s = "2e10";
	printf("%s ==> %s\n", s.c_str(), Solution::isNumber(s) ? "True" : "False");

	s = ".1";
	printf("%s ==> %s\n", s.c_str(), Solution::isNumber(s) ? "True" : "False");

	s = ".789866e-3";
	printf("%s ==> %s\n", s.c_str(), Solution::isNumber(s) ? "True" : "False");

	s = "3.";
	printf("%s ==> %s\n", s.c_str(), Solution::isNumber(s) ? "True" : "False");

	s = "+.8";
	printf("%s ==> %s\n", s.c_str(), Solution::isNumber(s) ? "True" : "False");

	s = "+3.";
	printf("%s ==> %s\n", s.c_str(), Solution::isNumber(s) ? "True" : "False");

	s = "-3.";
	printf("%s ==> %s\n", s.c_str(), Solution::isNumber(s) ? "True" : "False");

	s = "-.8";
	printf("%s ==> %s\n", s.c_str(), Solution::isNumber(s) ? "True" : "False");

	s = ".1.";
	printf("%s ==> %s\n", s.c_str(), Solution::isNumber(s) ? "True" : "False");

	s = " 005047e+6";
	printf("%s ==> %s\n", s.c_str(), Solution::isNumber(s) ? "True" : "False");

	return 0;
}

