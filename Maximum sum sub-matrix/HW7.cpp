#include <iostream>
#include<cstdlib>//�üƥ�
#include<ctime>
#include<iomanip>//�ƪ���
using namespace std;




int main()
{
	int select;//�P�_�⥴�٬O�q������
	int a;//row
	int b;//column

	cout << "�п�Jrow�j�p" << endl;
	cin >> a;
	cout << "�п�Jcolumn�j�p" << endl;
	cin >> b;

	int **C;//C is aXb matrix
	C = new int *[a];//�scolumn array ��pointer array
	for (int i = 0; i < a; i++)
	{
		C[i] = new int[b];
	}

	
	cout << "�n�ۤv��J�Ʀr�Х�1   �n�q�����ͽХ�2" << endl;
	cin >> select;


	if (select==1)//�⥴
	{
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < b; j++)
			{
				cin>>C[i][j] ;
			}
		}
	}



	srand(time(0));
	if (select==2)
	{
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < b; j++)
			{
				C[i][j] = rand() % 200 - 100;
			}
		}
	}

	cout << "original matrix is:" << endl;//�L
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			cout<<setw(j+5)<<C[i][j];
		}
		cout << endl;
	}



	//���submatrix


	{
		int sum=0;
		int maxsum = -2147483647, another_maxsum = -2147483647;//int_min
		int row_begin, row_end, another_row_begin, another_row_end;
		int column_begin, column_end, another_column_begin, another_column_end;

		for (size_t i = 0; i < a; i++)//scan the matrix from up to down
		{
			for (size_t j = i; j < a; j++)
			{
				for (size_t k = 0; k < b; k++)//scan the matrix from left to right
				{
					for (size_t l = k; l < b; l++)
					{

						sum = 0;

						for (size_t r=i ;r<=j; r++)//calculate the sum of submatrix 
						{

							for (size_t c = k; c <= l; c++)
							{
								
								sum = sum+C[r][c];							
							}

						}

						if (sum > maxsum)//�n�O�̤j��
						{

							maxsum = sum;
							row_begin = i;
							row_end = j;
							column_begin = k;
							column_end = l;

						}else if (sum == maxsum)//���P�˦�max����matrix
						{
							another_maxsum = sum;
							another_row_begin = i;
							another_row_end = j;
							another_column_begin = k;
							another_column_end = l;
						}
						


					}
				}

			}

		}

		cout << endl;
		cout << "sub-matrix is:" << endl;//�Lsubmatrix
		for (int i = row_begin; i <= row_end; i++)
		{
			for (int j = column_begin; j <= column_end; j++)
			{
				cout << setw(j + 5) << C[i][j];
			}
			cout << endl;
		}

		
		cout << endl;
		if (maxsum == another_maxsum)//�Y���ۦPmax�ȱosubmatrix
		{
			cout << "another sub-matrix is:" << endl;//�Lsubmatrix
			for (int i = another_row_begin; i <= another_row_end; i++)
			{
				for (int j = another_column_begin; j <= another_column_end; j++)
				{
					cout << setw(j + 5) << C[i][j];
				}
				cout << endl;
			}
		}
		
		
		cout << endl;//�L�̤j��
		cout << "Maximum of submatrix is:" << endl;
		cout << maxsum << endl;
		
	
	}

	return 0;
}






















