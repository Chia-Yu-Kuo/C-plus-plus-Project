#include <iostream> 
#include <string.h>
#include  "Queue.h"

using namespace std;

bool no_money(int arr[5][3] ) 
{
	for (int i = 0; i < 5; i++)
	{
		if (arr[i][1]>0)
		{
			return false;
			break;
		}
	}
	return true;
}


int main() 
{

	int data[5][3];	
	int player;
	int time = 0;
	int size;
	
	Queue line,time_queue,temp;
	
	cout << "5 people arrive time: "<<endl;
	for (int i = 0; i < 5; i++)//time
	{
		cin >> data[i][0];
	}
	cout << "5 people each has money: " << endl;
	for (int i = 0; i < 5; i++)//money
	{
		cin >> data[i][1];
	}
	for (int i = 0; i < 5; i++)//has in line?
	{
		data[i][2]=0;
	}

	/*
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << data[i][j];
		}
		cout << endl;
	}
	*/


	while (!no_money(data))
	{
		//push in line  (never in line player)
		for (int i = 0; i < 5; i++)
		{		
			if (data[i][1] > 0)		//�٦���
			{		
				if (data[i][0] == time)
				{
					temp.Push(i);				//���ƪ�+��i�ө�����
					data[i][2] = 1;
				}
				if (data[i][2] == 0) //�٨S�i�hline�L								�p�ߨ�̥i�ೣ�o��(�ҥH==time �M<time���)
				{
					if (data[i][0] < time)		//�ɶ�<t�����٨S�iline
					{
						line.Push(i);
						data[i][2] = 1;
					}
				}
			}
		}
		
		//test = temp.getFront();


		while(!temp.IsEmpty())
		{			
			line.Push(temp.getFront());
			temp.Pop();
		}
		
		if (line.IsEmpty())			//��t=0�C�H
		{
			time++;
			time_queue.Push(120);
			continue;
		}
		

		
		//play
		player = line.getFront();
		if (data[player][1]>=2)      //��$2
		{
			time_queue.Push(player);
			time_queue.Push(player);


			time += 2;
			data[player][0] = time;
			data[player][1] -= 2;
		}
		else //if(data[player][1]==1)//��$1
		{
			time_queue.Push(player);

			time += 1;
			data[player][0] = time;
			data[player][1] -= 1;			//no money
		}
		line.Pop();
		data[player][2] = 1;
		
		/*
		//test
		cout <<"time" << time << endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cout << data[i][j]<<"   ";
			}
			cout << endl;
		}
		cout << endl;
		*/

	}

	size = time_queue.getSize();																		//for (int i = 0; i <time_queue.getSize(); i++)	  will error �]��time.getsize�Dconst
	for (int i = 0; i < size; i++)
	{
		if (time_queue.getFront()!=120)
		{
			cout << "time: " << i << "    player: " << time_queue.getFront() << endl;
		}
		else
		{
			cout << "time: " << i << "    player: " <<  'x' << endl;
		}
		
		time_queue.Pop();
	}



	system("pause");
	return(0);
}