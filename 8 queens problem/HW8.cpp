#include <stdlib.h>
#include <iostream>


using namespace std;

int have_checked[7], row, column;

double temp; //防呆用
void dwarf(int);


int main()
{

	while (1)  //可重複輸入
	{
		row = 0;
		


		while (true)
		{
			//防呆
			bool judge = 1;

			cout << "please input column index from 0 to 6 on row0:" << endl;
			char  temp1[10] = {};     //每次還原

			cin >> temp1;

			for (size_t i = 0; i < 10; i++)//防字母
			{
				if (!(temp1[i] == '0' || temp1[i] == '1' || temp1[i] == '2' || temp1[i] == '3' || temp1[i] == '4' || temp1[i] == '5' || temp1[i] == '6' || temp1[i] == '\0'))
				{
					judge = 0;
				}
			}
			
			temp = atof(temp1);//字串轉浮點數
			
			if (temp != 0 && temp != 1 && temp != 2 && temp != 3 && temp != 4 && temp != 5 && temp != 6)//防小數
			{
				judge = 0;
			}
			if (judge == 0)
			{
				cout << "input error" << endl;
			    
			}
			else
			{
				column = (int)temp;//浮點轉整數
				break;
			}

		}



		for (int i = 0; i < 7; i++)   //(0.0)(1.0)(2.0)(3.0)(4.0)(5.0)(6.0)
		{
			have_checked[0] = i;                //第一列有7個位置可以填
			dwarf(1);                  //從row_point_to=1開始check(row=1)
		}
		cout << endl;
	}
}



void dwarf(int row_point_to)      //第一列7種結果的其中一種(跑七次)
{
	if (row_point_to < 7)        //放drawf
	{
		for (int k = 0; k < 7; k++)    //(have_checked[l],l) ==>上面已填好的變數              (k,row_point_to)==>正要放入的dwarf
		{
			for (int l = 0; l < row_point_to; l++)
			{
				if ((have_checked[l] == k) || ((have_checked[l] - k) == (l - row_point_to)) || ((have_checked[l] - k) == (row_point_to - l)))  //想放的drawf跟上面已放的相同column,x=y,x=-y就break
					break;
				if (l == (row_point_to - 1))
				{  
					have_checked[row_point_to] = k;  //keep 正確值進去
					dwarf(row_point_to + 1);        //若 (k,row_point_to)可以放入==>進入下一行檢查，若找不到適合解return到呼叫他的地方然後l++
				}
			}
		}
	}
	if (row_point_to == 7)   //若全部跑完，有7種結果的其中一種詳解ex(0.0)有4解 
	{

		if (have_checked[row] == (column))
		{
			for (int r = 0; r < 7; r++)
			{
				cout << have_checked[r] << " ";      //印出使用者輸入的解
			}
			cout << endl;
		}
	}
}
