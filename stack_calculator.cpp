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

bool Parentheses_Check(string s);//입력받은 식 괄호 검사 함수
void infix_to_postfix(string infix);//infix식을 postfix로 변경하는 함수
void postfix_calc(vector<char> v);//postfix를 계산하는 함수

bool Parentheses_Check(string s)
{
	//pre:입력받은 식
	//post:괄호 검사시 괄호의 짝이 맞지 않으면 에러와 그에 상응하는 문구 출력

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
		if (!isdigit(infix[i]) && infix[i] != '.')//한자리수가 아닌경우 숫자와 연산자 구분해주기 
		{
			postfix.push_back(' ');
		}

		if (isdigit(infix[i]) || infix[i] == '.')//한자리수이거나 소수점이면 push
		{
			postfix.push_back(infix[i]);
		}
		else if (infix[i] == '(' || infix[i] == '[' || infix[i] == '{')//왼쪽괄호인 경우 스택에 push
		{
			s.push(infix[i]);
		}
		else if (strchr("*/", infix[i]))//우선순위1번 -> 그냥 넣는다
		{
			/*while (!s.empty())
			{
				postfix.push_back(s.top());
				s.pop();
			}*/
			s.push(infix[i]);
		}
		else if (strchr("+-", infix[i]))//우선순위 2번 -> top에 우선순위 1번있는지 검사
		{
			while (!s.empty() && strchr("*/",s.top()))
			{
				postfix.push_back(s.top());
				s.pop();
			}
			s.push(infix[i]);
		}
		else if (infix[i] == ')' || infix[i] == ']' || infix[i] == '}')//오른쪽괄호이면 왼쪽괄호를 만날때까지 pop!
		{
			while (s.top() != '('&&s.top() != '['&&s.top() != '{')
			{
				postfix.push_back(s.top());
				s.pop();
			}
			s.pop();
		}

	}

	while (!s.empty())//스택에 남아있으면 pop
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
	//pre : postfix로 변환된 식
	//post : 결과 값 혹은 error출력

	char numbers[MAX];

	stack<double>st;

	double op1, op2;
	double result, val;
	double num;
	int j;

	for (int i = 0; i < v.size(); i++)
	{
		val = 0;

		if (isdigit(v[i]))//숫자일때
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
			num = atof(numbers);//문자열을 실수로 변환

			st.push(num);
			i--;
		}
		else if (strchr("*/+-", v[i]))//연산자일때
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

	//소수점 3번째자리까지(반올림해서) 출력하기
	cout << fixed;
	cout.precision(3);
	cout << "output : " << st.top() << endl;

	while (!st.empty())//다음 연산을 위해 stack를 비워줌
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