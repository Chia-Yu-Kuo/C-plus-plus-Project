#include <stdlib.h>
#include <iostream>


using namespace std;

int have_checked[7], row, column;

double temp; //���b��
void dwarf(int);


int main()
{

	while (1)  //�i���ƿ�J
	{
		row = 0;
		


		while (true)
		{
			//���b
			bool judge = 1;

			cout << "please input column index from 0 to 6 on row0:" << endl;
			char  temp1[10] = {};     //�C���٭�

			cin >> temp1;

			for (size_t i = 0; i < 10; i++)//���r��
			{
				if (!(temp1[i] == '0' || temp1[i] == '1' || temp1[i] == '2' || temp1[i] == '3' || temp1[i] == '4' || temp1[i] == '5' || temp1[i] == '6' || temp1[i] == '\0'))
				{
					judge = 0;
				}
			}
			
			temp = atof(temp1);//�r����B�I��
			
			if (temp != 0 && temp != 1 && temp != 2 && temp != 3 && temp != 4 && temp != 5 && temp != 6)//���p��
			{
				judge = 0;
			}
			if (judge == 0)
			{
				cout << "input error" << endl;
			    
			}
			else
			{
				column = (int)temp;//�B�I����
				break;
			}

		}



		for (int i = 0; i < 7; i++)   //(0.0)(1.0)(2.0)(3.0)(4.0)(5.0)(6.0)
		{
			have_checked[0] = i;                //�Ĥ@�C��7�Ӧ�m�i�H��
			dwarf(1);                  //�qrow_point_to=1�}�lcheck(row=1)
		}
		cout << endl;
	}
}



void dwarf(int row_point_to)      //�Ĥ@�C7�ص��G���䤤�@��(�]�C��)
{
	if (row_point_to < 7)        //��drawf
	{
		for (int k = 0; k < 7; k++)    //(have_checked[l],l) ==>�W���w��n���ܼ�              (k,row_point_to)==>���n��J��dwarf
		{
			for (int l = 0; l < row_point_to; l++)
			{
				if ((have_checked[l] == k) || ((have_checked[l] - k) == (l - row_point_to)) || ((have_checked[l] - k) == (row_point_to - l)))  //�Q��drawf��W���w�񪺬ۦPcolumn,x=y,x=-y�Nbreak
					break;
				if (l == (row_point_to - 1))
				{  
					have_checked[row_point_to] = k;  //keep ���T�ȶi�h
					dwarf(row_point_to + 1);        //�Y (k,row_point_to)�i�H��J==>�i�J�U�@���ˬd�A�Y�䤣��A�X��return��I�s�L���a��M��l++
				}
			}
		}
	}
	if (row_point_to == 7)   //�Y�����]���A��7�ص��G���䤤�@�ظԸ�ex(0.0)��4�� 
	{

		if (have_checked[row] == (column))
		{
			for (int r = 0; r < 7; r++)
			{
				cout << have_checked[r] << " ";      //�L�X�ϥΪ̿�J����
			}
			cout << endl;
		}
	}
}
