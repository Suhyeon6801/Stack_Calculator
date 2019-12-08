#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;

const int MAX = 1010;

bool Parentheses_Check(string s);//�Է¹��� �� ��ȣ �˻� �Լ�
void infix_to_postfix(string infix);//infix���� postfix�� �����ϴ� �Լ�
void postfix_calc(vector<char> v);//postfix�� ����ϴ� �Լ�

bool Parentheses_Check(string s)
{
	//pre:�Է¹��� ��
	//post:��ȣ �˻�� ��ȣ�� ¦�� ���� ������ ������ �׿� �����ϴ� ���� ���

	stack <char> st;
	//int length = strlen(ch);
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '(' || s[i] == '[' || s[i] == '{')
		{
			st.push(s[i]);
		}
		else if (s[i] == ')')
		{
			if (st.top() == '(')	st.pop();
		}
		else if (s[i] == ']')
		{
			if (st.top() == '[')	st.pop();
		}
		else if (s[i] == '}')
		{
			if (st.top() == '{')	st.pop();
		}
		else continue;
	}

	if (!st.empty())	return false;

	return true;
}

void infix_to_postfix(string infix)
{
	//pre:infix
	//post:postfix

	vector<char> postfix;
	stack<char> s;

	for (int i = 0; i < infix.length(); i++)
	{
		if (!isdigit(infix[i]) && infix[i] != '.')//���ڸ����� �ƴѰ�� ���ڿ� ������ �������ֱ� 
		{
			postfix.push_back(' ');
		}

		if (isdigit(infix[i]) || infix[i] == '.')//���ڸ����̰ų� �Ҽ����̸� push
		{
			postfix.push_back(infix[i]);
		}
		else if (infix[i] == '(' || infix[i] == '[' || infix[i] == '{')//���ʰ�ȣ�� ��� ���ÿ� push
		{
			s.push(infix[i]);
		}
		else if (strchr("*/", infix[i]))//�켱����1�� -> �׳� �ִ´�
		{
			/*while (!s.empty())
			{
				postfix.push_back(s.top());
				s.pop();
			}*/
			s.push(infix[i]);
		}
		else if (strchr("+-", infix[i]))//�켱���� 2�� -> top�� �켱���� 1���ִ��� �˻�
		{
			while (!s.empty() && strchr("*/",s.top()))
			{
				postfix.push_back(s.top());
				s.pop();
			}
			s.push(infix[i]);
		}
		else if (infix[i] == ')' || infix[i] == ']' || infix[i] == '}')//�����ʰ�ȣ�̸� ���ʰ�ȣ�� ���������� pop!
		{
			while (s.top() != '('&&s.top() != '['&&s.top() != '{')
			{
				postfix.push_back(s.top());
				s.pop();
			}
			s.pop();
		}

	}

	while (!s.empty())//���ÿ� ���������� pop
	{
		postfix.push_back(s.top());
		s.pop();
	}

	//cout << "postfix : ";
	//for (int i = 0; i < postfix.size(); i++)
	//{
	//	cout << postfix[i];
	//}
	//cout << endl;

	postfix_calc(postfix);
}

void postfix_calc(vector<char> v)
{
	//pre : postfix�� ��ȯ�� ��
	//post : ��� �� Ȥ�� error���

	char numbers[MAX];

	stack<double>st;

	double op1, op2;
	double result, val;
	double num;
	int j;

	for (int i = 0; i < v.size(); i++)
	{
		val = 0;

		if (isdigit(v[i]))//�����϶�
		{
			j = 0;
			memset(numbers, 0, sizeof(numbers));
			while (1)
			{
				if (v[i] == '.' || isdigit(v[i]))
				{
					numbers[j++] = v[i++];
				}
				else
				{
					break;
				}
			}
			num = atof(numbers);//���ڿ��� �Ǽ��� ��ȯ

			st.push(num);
			i--;
		}
		else if (strchr("*/+-", v[i]))//�������϶�
		{
			op2 = st.top();
			st.pop();
			op1 = st.top();
			st.pop();

			if (v[i] == '*')
			{
				val = op1 * op2;
				st.push(val);
			}
			if (v[i] == '/')
			{
				if (op2 == 0.0)
				{
					cout << "Error!: divide by zero" << endl;
					return;
				}
				val = op1 / op2;
				st.push(val);
			}
			if (v[i] == '+')
			{
				val = op1 + op2;
				st.push(val);
			}
			if (v[i] == '-')
			{
				val = op1 - op2;
				st.push(val);
			}
		}
	}

	//�Ҽ��� 3��°�ڸ�����(�ݿø��ؼ�) ����ϱ�
	cout << fixed;
	cout.precision(3);
	cout << "output : " << st.top() << endl;

	while (!st.empty())//���� ������ ���� stack�� �����
	{
		st.pop();
	}
}

int main()
{
	string input;
	const string EXIT = "EOI";

	while (1)
	{
		cout << "input:";
		cin >> input;

		if (input.compare(EXIT)==0)	break;
		else
		{
			if (!Parentheses_Check(input))	cout << "Error!: unbalanced parentheses" << endl;
			else
			{
				infix_to_postfix(input);
			}
		}
	}
	return 0;
}