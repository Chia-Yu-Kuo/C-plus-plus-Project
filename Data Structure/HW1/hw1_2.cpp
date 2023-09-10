#include <iostream> 
#include <string.h>
#include  "Stack.h"


using namespace std;

int main() 
{
	int right_parenthesis=0;
	Stack< char > charstack;
	char str[1000] = { "\0" };					//enought??
	cout << "Enter a string= : ";
	cin.getline(str,1000);

	
	for (int i = 0 ;i<strlen(str) ; i++)
	{
		if (charstack.empty())
		{
			if (str[i] == '(')
			{
				charstack.push(str[i]);
			}
			else
			{
				right_parenthesis++;
			}
		}
		else
		{
			if (str[i] == '(')
			{
				charstack.push(str[i]);
			}
			else
			{
				charstack.pop();
			}
		}
	}


	cout << "output=: " << right_parenthesis + charstack.getsize()<<endl;

	system("pause");
	return(0);
}


// begin with )  ?? sol??