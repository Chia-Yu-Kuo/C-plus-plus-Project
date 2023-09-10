#include <iostream> 

using namespace std;



int main() 
{
	int size;
	int max=0;
	int difference;

	cout << "Totol day=: ";
	cin >> size;

	cout << "each day price: ";
	int* arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		cin >> arr[i];
	}

	for (int i = 0; i < size-1 ; i++)
	{
		for (int j = i+1; j < size; j++)
		{
			difference = arr[j] - arr[i];

			if (difference>max)
			{
				max = difference;
			}
		}
	}

	cout  <<"earning:= " << max <<endl;


	system("pause");
	return 0;
}