#include "stdafx.h"

#include <vector>
#include <stack>
#include <string>

using namespace std;

class Solution
{
public:

	static const int NA = 0x7FFFFFFF;

public:

	static int evalRPN(vector<string>& tokens)
	{
		int operand = 0;
		int operand1 = 0;
		int operand2 = 0;

		stack<int> operands;

		for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++)
		{
			if (isOperand(*it, operand))
			{
				if (popAndCheckOperands(operands, operand1, operand2))
				{
					switch (operand)
					{
					case 1:
						operands.push(operand1 + operand2);
						break;
					case 2:
						operands.push(operand1 - operand2);
						break;
					case 3:
						operands.push(operand1 * operand2);
						break;
					case 4:
						if (operand2 != 0)
						{
							operands.push(operand1 / operand2);
						}
						else
						{
							return NA;
						}
						break;
					}
				}
				else
				{
					return NA;
				}
			}
			else
			{
				operands.push(operand);
			}
		}

		if (operands.size() == 1)
		{
			return operands.top();
		}
		else
		{
			return NA;
		}
	}

private:

	static inline bool popAndCheckOperands(stack<int>& operands, int& operand1, int& operand2)
	{
		if (operands.size() < 2)
		{
			printf("Invalid input.");
			return false;
		}

		operand2 = operands.top();
		operands.pop();
		operand1 = operands.top();
		operands.pop();

		return true;
	}

	static inline string& trim(string& text)
	{
		if (!text.empty())
		{
			text.erase(0, text.find_first_not_of((" \n\r\t")));
			text.erase(text.find_last_not_of((" \n\r\t")) + 1);
		}

		return text;
	}

	static inline bool isOperand(string& token, int& operand)
	{
		token = trim(token);

		if (token.size() == 1)
		{
			switch (token[0])
			{
			case '+':
				operand = 1;
				return true;
			case '-':
				operand = 2;
				return true;
			case '*':
				operand = 3;
				return true;
			case '/':
				operand = 4;
				return true;
			default:
				operand = atoi(token.c_str());
				return false;
			}
		}
		else
		{
			operand = atoi(token.c_str());
			return false;
		}
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> tokens;

	tokens.push_back("2");
	tokens.push_back("1");
	tokens.push_back("+");
	tokens.push_back("3");
	tokens.push_back("*");

	int result = Solution::evalRPN(tokens);

	tokens.clear();
	tokens.push_back("4");
	tokens.push_back("3");
	tokens.push_back("-");

	result = Solution::evalRPN(tokens);
	return 0;
}

