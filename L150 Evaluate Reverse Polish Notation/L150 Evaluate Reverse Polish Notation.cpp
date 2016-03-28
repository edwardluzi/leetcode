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
		int op = 0;
		int operand1 = 0;
		int operand2 = 0;

		stack<int> operands;

		for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
		{
			if (isOperator(*it, op))
			{
				if (popOperands(operands, operand1, operand2))
				{
					switch (op)
					{
						case 1:
						{
								  operands.push(operand1 + operand2);
								  break;
						}
						case 2:
						{
								  operands.push(operand1 - operand2);
								  break;
						}
						case 3:
						{
								  operands.push(operand1 * operand2);
								  break;
						}
						case 4:
						{
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
				}
				else
				{
					return NA;
				}
			}
			else
			{
				operands.push(op);
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

	static inline bool popOperands(stack<int>& operands, int& operand1, int& operand2)
	{
		if (operands.size() < 2)
		{
			return false;
		}

		operand2 = operands.top();
		operands.pop();

		operand1 = operands.top();
		operands.pop();

		return true;
	}

	static inline bool isOperator(string& token, int& op)
	{
		if (token.size() == 1)
		{
			switch (token[0])
			{
				case '+':
				{
							op = 1;
							return true;
				}
				case '-':
				{
							op = 2;
							return true;
				}
				case '*':
				{
							op = 3;
							return true;
				}
				case '/':
				{
							op = 4;
							return true;
				}
			}
		}

		op = atoi(token.c_str());

		return false;
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

	printf(result == 9 ? "Okay\n" : "Failed\n");

	tokens.clear();
	tokens.push_back("4");
	tokens.push_back("3");
	tokens.push_back("-");

	result = Solution::evalRPN(tokens);

	printf(result == 1 ? "Okay\n" : "Failed\n");

	return 0;
}

