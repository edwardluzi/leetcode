#include "stdafx.h"

#include <algorithm> 
#include <cctype>
#include <functional> 
#include <locale>
#include <string>

using namespace std;

enum State
{
	Unknown,
	FirstNumber,
	FollowedNumber,
	FirstDecimal,
	FollowedDecimal
};

class Solution
{
public:

	static bool isNumber(string s)
	{
		string decimal;
		string exponent;

		s = trim(s);

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
		static string number = "0123456789";

		State state = Unknown;
		char token = 0;

		while (s.length() > 0)
		{
			token = s.at(0);

			switch (state)
			{
			case Unknown:
			{
							if (token == '-' && allowMinus)
							{
								state = FirstNumber;
								s.erase(s.begin());
								value.push_back(token);
							}
							else if (token == '+' && allowPlus)
							{
								state = FirstNumber;
								s.erase(s.begin());
								value.push_back(token);
							}
							else if (number.find(token) != string::npos)
							{
								state = FollowedNumber;
								s.erase(s.begin());
								value.push_back(token);
							}
							else
							{
								return false;
							}

							break;
			}
			case FirstNumber:
			{
							if (number.find(token) != string::npos)
							{
								state = FollowedNumber;
								s.erase(s.begin());
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
							if (number.find(token) != string::npos)
							{
								state = FollowedNumber;
								s.erase(s.begin());
								value.push_back(token);
							}
							else
							{
								return true;
							}
							break;
			}
			}
		}

		return state == FollowedNumber;
	}

	static bool readDecimal(string& s, string& value)
	{
		static string number = "0123456789";

		State state = Unknown;
		char token = 0;

		while (s.length() > 0)
		{
			token = s.at(0);

			switch (state)
			{
			case Unknown:
			{
							if (token == '+')
							{
								state = FirstNumber;
								s.erase(s.begin());
								value.push_back(token);
							}
							else if (token == '-')
							{
								state = FirstNumber;
								s.erase(s.begin());
								value.push_back(token);
							}
							else if (token == '.')
							{
								state = FirstDecimal;
								s.erase(s.begin());
								value.push_back(token);
							}
							else if (number.find(token) != string::npos)
							{
								state = FollowedNumber;
								s.erase(s.begin());
								value.push_back(token);
							}
							else
							{
								return false;
							}

							break;
			}
			case FirstNumber:
			{
								if (number.find(token) != string::npos)
								{
									state = FollowedNumber;
									s.erase(s.begin());
									value.push_back(token);
								}
								else if (token == '.')
								{
									state = FirstDecimal;
									s.erase(s.begin());
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
								   if (number.find(token) != string::npos)
								   {
									   state = FollowedNumber;
									   s.erase(s.begin());
									   value.push_back(token);
								   }
								   else if (token == '.')
								   {
									   state = FirstDecimal;
									   s.erase(s.begin());
									   value.push_back(token);
								   }
								   else
								   {
									   return true;
								   }

								   break;
			}
			case FirstDecimal:
			{
								 if (number.find(token) != string::npos)
								 {
									 state = FollowedDecimal;
									 s.erase(s.begin());
									 value.push_back(token);
								 }
								 else if (token == '.')
								 {
									 return false;
								 }
								 else
								 {
									 return true;
								 }

								 break;
			}
			case FollowedDecimal:
			{
									if (number.find(token) != string::npos)
									{
										state = FollowedDecimal;
										s.erase(s.begin());
										value.push_back(token);
									}
									else if (token == '.')
									{
										return false;
									}
									else
									{
										return true;
									}
									break;
			}
			}
		}

		return state != Unknown;
	}

	// trim from start
	static inline std::string &ltrim(std::string &s) {
		s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(std::isspace))));
		return s;
	}

	// trim from end
	static inline std::string &rtrim(std::string &s) {
		s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
		return s;
	}

	// trim from both ends
	static inline std::string &trim(std::string &s) {
		return ltrim(rtrim(s));
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	string s = "0";
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

