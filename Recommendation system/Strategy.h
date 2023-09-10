#ifndef Strategy_h
#define Strategy_h

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;
///              user  to  item tabel               RecomdList            At most K Proposed Items           user size      item size
void Algorithm(vector<vector<double>> Table, vector<vector<int>>& RecomdList, const int K, const int user_size, const int item_size)
{
	//(sol4)   

	vector<vector<double>> costumertocostumer_relation(user_size);    
	for (int i = 0; i < user_size; i++)
	{
		costumertocostumer_relation[i].resize(user_size, 0);
	}

	vector<double>distance_square(item_size);
	double total_distance_square;
	double counter;

	vector<vector<double>>totalscore_table(user_size);
	for (int i = 0; i < user_size; i++)
	{
		totalscore_table[i].resize(item_size, 0);
	}

	double relationship;
	bool judge_whether_have_relation;

	for (int currentpointto_user = 0; currentpointto_user < user_size; currentpointto_user++)   
	{
		for (int i = 0; i < user_size; i++)      
		{
			total_distance_square = 0;
			relationship = 0;
			judge_whether_have_relation = 0;
			counter = 1;
			if (currentpointto_user == i)                 
			{
				continue;
			}
			else
			{
				for (int currentpointto_item = 0; currentpointto_item < item_size; currentpointto_item++)
				{
					if (Table[currentpointto_user][currentpointto_item] != -1 && Table[i][currentpointto_item] != -1)
					{
						distance_square[currentpointto_item] = (Table[currentpointto_user][currentpointto_item] - Table[i][currentpointto_item]) * (Table[currentpointto_user][currentpointto_item] - Table[i][currentpointto_item]);
						total_distance_square += distance_square[currentpointto_item];
						judge_whether_have_relation = 1;
						if (distance_square[currentpointto_item] <= 1)        //distance=0or1
						{
							counter += 15;                                   
						}
					}
					else
					{
						continue;
					}
				}
			}
			if (judge_whether_have_relation == 1)
			{
				relationship = counter / (1 + sqrt(total_distance_square));
				costumertocostumer_relation[currentpointto_user][i] = relationship;  
				costumertocostumer_relation[i][currentpointto_user] = relationship;
			}
			else
			{
				costumertocostumer_relation[currentpointto_user][i] = 0;   
				costumertocostumer_relation[i][currentpointto_user] = 0;
			}
		}
	}

	vector<vector<double>> costumertocostumerrelation_sort;
	costumertocostumerrelation_sort = costumertocostumer_relation;

	for (int i = 0; i < user_size; i++)      //row
	{

		sort(costumertocostumerrelation_sort[i].begin(), costumertocostumerrelation_sort[i].end(), greater<double>());
		for (int k = 0; k < user_size; k++)            
		{
			if (costumertocostumerrelation_sort[i][k] == 0)
			{
				break;
			}
			for (int j = 0; j < user_size; j++)          
			{
				if (costumertocostumerrelation_sort[i][k] == costumertocostumer_relation[i][j])           
				{
					costumertocostumer_relation[i][j] = -1;
					for (int l = 0; l < item_size; l++)    
					{
						if (Table[i][l] != -1)     
						{
							totalscore_table[i][l] = -1;
						}
						else if (Table[i][l] == -1)
						{
							if (Table[j][l] != -1)       
							{
								totalscore_table[i][l] += (costumertocostumerrelation_sort[i][k] * Table[j][l]);      
							}
						}
					}
					break;
				}
			}
		}
	}
	for (int i = 0; i < user_size; i++)
	{
		for (int j = 0; j < user_size; j++)
		{
			cout << costumertocostumerrelation_sort[i][j] << "!";
		}
		cout << endl << "WWWWWWW" << endl;
	}
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;

	vector<vector<double>>totalscore_table_sort;
	totalscore_table_sort = totalscore_table;

	for (int i = 0; i < user_size; i++)
	{
		sort(totalscore_table_sort[i].begin(), totalscore_table_sort[i].end(), greater<double>());
	}

	for (int j = 0; j < user_size; j++)       //user++
	{
		for (int l = 0; l < K; l++)           //score_sort item++
		{
			for (int m = 0; m < item_size; m++)      //score item++
			{
				if (totalscore_table_sort[j][l] != -1)
				{
					if (totalscore_table_sort[j][l] == totalscore_table[j][m])
					{
						RecomdList[j][l] = m;
						totalscore_table[j][m] = -1;
						break;
					}
				}
			}
		}
	}
}
#endif /* Strategy_h */
