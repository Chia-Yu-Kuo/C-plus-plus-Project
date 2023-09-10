#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<cstring>
#include<algorithm>

using namespace std;


class Kmap
{
private:
	string original;
	vector<string>seperated;
	vector<vector<int>> map_temp;

public:
	Kmap()
	{
		//	vector<vector<int>> matrix(4, vector<int>(4,0));
		map_temp.resize(4);
		for (int i = 0; i < 4; i++)
		{
			map_temp[i].resize(4, 0);
		}

		map.resize(4);                            ////pair's map
		for (int i = 0; i < 4; i++)
		{
			map[i].resize(4);
			for (int j = 0; j < 4; j++)
			{
				map[i][j].first = 0;
			}
		}

		groupSolutions.resize(16);						//max solutions 16*8 
		essential.resize(16);
		remains.resize(16);		//need select biggest prime implicant
		essential_minterm.resize(16);
		remains_minterm.resize(16);

	}

	//build map


	int matrix[4][4] = { {0,4,12,8},{1,5,13,9} ,{3,7,15,11}, {2,6,14,10} };

	string getOriginal();
	int getSeperatedSize();
	vector<string>getSeperated();
	//	int** getMatrix();
	//	void setMatrix();
	void printOriginal();
	void printTempMap();
	void printMap();
	void printSeperated();
	void readSop();
	vector<int> mintermNumber(string, vector<int>);
	///切字串
	void sopProcess(string original);
	vector<string>split(string original, string need_remove);
	///////
	void keyInmap(int matrix[4][4], vector<int>);
	int mintermNum[16] = { 0 };



	///////////////////////////////////////////////////////
	//simplify
private:
	vector<vector<pair<int, int>>>map;
	vector<vector<pair<int, int>>> groupSolutions;
	int groupSolutions_size;
	vector<vector<pair<int, int>>>essential;
	int essential_size;
	vector<vector<pair<int, int>>>remains;			//need select " loop most 1  in groupsolutins (if equal ==> OR   )
	int remains_size;
	vector<vector<int>>essential_minterm;
	vector<vector<int>>remains_minterm;
	string f;

public:

	void simplify();
	void findPrimeImpliment(int, int, int);
	int isEssential(int);
	void closeOnMatrix(vector<pair<int, int>>);
	int loopRemain(int, int, int);
	void keyINMinterm();
	void printSimplify(int, int);
	string printChar(int, vector<int>&, int);

};

string Kmap::getOriginal()
{
	return original;
}
int Kmap::getSeperatedSize()
{
	return seperated.size();
}

void  Kmap::readSop()
{
	ifstream  ifile;
	ifile.open("input.txt");
	if (false == ifile.is_open())
	{
		cerr << "open file error" << endl;
	}
	string origi;
	getline(ifile, origi);

	ifile.close();



	original = origi;

}

vector<string> Kmap::getSeperated()
{
	return seperated;
}
/*
int** Kmap::getMatrix()
{

	int* ptr[4] = { matrix[0],matrix[1],matrix[2],matrix[3] };

	return ptr;
}
*/

void Kmap::sopProcess(string original)
{
	seperated = split(original, "+");


	/*
	for (int i = 0; i < seprated.size(); i++)
	{
		cout << seprated[i] << endl;
	}
	*/
}


vector<string> Kmap::split(string original, string need_remove)
{
	vector<string>result;
	int current = 0; //最初由 0 的位置開始找
	int next = 0;
	while (next != -1)
	{
		next = original.find_first_of(need_remove, current); //尋找從current開始，出現splitSep的第一個位置(找不到則回傳-1)
		if (next != current)
		{
			string tmp = original.substr(current, next - current);
			if (!tmp.empty())  //忽略空字串(若不寫的話，尾巴都是分割符會錯)
			{
				result.push_back(tmp);
			}
		}
		current = next + 1; //下次由 next + 1 的位置開始找起。
	}
	return result;

}
vector<int> Kmap::mintermNumber(string term, vector<int> a)               //a[8]為記錄term再map上最多可能的mintermNum
{
	int weights[9] = { 0,2,2,0,2,0,0,0,2 };          //0  1   2(被削)

	for (string::iterator it = term.begin(); it != term.end(); it++)
	{
		switch (*it)
		{
		case 'a':
		case'A':
			weights[8] = 1;
			break;
		case'b':
		case'B':
			weights[4] = 1;
			break;
		case'c':
		case'C':
			weights[2] = 1;
			break;
		case'd':
		case'D':
			weights[1] = 1;
			break;
		case'(':
		case')':
			break;
		default:										//////////		''''''			
			if (*(it - 1) == 'A' || *(it - 1) == 'a')
			{
				weights[8] = 0;
			}
			else if (*(it - 1) == 'B' || *(it - 1) == 'b')
			{
				weights[4] = 0;
			}
			else if (*(it - 1) == 'C' || *(it - 1) == 'c')
			{
				weights[2] = 0;
			}
			else if (*(it - 1) == 'D' || *(it - 1) == 'd')
			{
				weights[1] = 0;
			}

			break;
		}
	}
	/*
	for (size_t i = 0; i < 8; i++)
	{
		cout << weights[i];

	}
	*/

	//算可能minterm

	int sum = 0;
	vector<int> possibleSum;
	int j = 0;
	for (int i = 0; i < 9; i++)		//i為跑weight
	{

		if (weights[i] != 2)
		{
			sum += i * weights[i];
		}
		if (weights[i] == 2)
		{
			possibleSum.push_back(i * 0);
			j++;
			possibleSum.push_back(i * 1);
			j++;
		}

	}

	//排列組合加起來
	if (possibleSum.size() == 0)
	{
		a.push_back(sum);
	}
	else if (possibleSum.size() == 2)
	{
		a.push_back(sum);
		a.push_back(sum + possibleSum[1]);
	}
	else if (possibleSum.size() == 4)
	{
		a.push_back(sum);
		a.push_back(sum + possibleSum[1]);
		a.push_back(sum + possibleSum[3]);
		a.push_back(sum + possibleSum[1] + possibleSum[3]);
	}
	else if (possibleSum.size() == 4)
	{
		a.push_back(sum);
		a.push_back(sum + possibleSum[1]);
		a.push_back(sum + possibleSum[3]);
		a.push_back(sum + possibleSum[5]);
		a.push_back(sum + possibleSum[1] + possibleSum[3]);
		a.push_back(sum + possibleSum[3] + possibleSum[5]);
		a.push_back(sum + possibleSum[5] + possibleSum[1]);
		a.push_back(sum + possibleSum[1] + possibleSum[3] + possibleSum[5]);
	}



	return a;
}
void Kmap::keyInmap(int matrix[4][4], vector<int>minter_number)
{
	for (int i = 0; i < minter_number.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				map[j][k].second = matrix[j][k];

				if (minter_number[i] == matrix[j][k])
				{
					map_temp[j][k] = 1;
					map[j][k].first = 1;
				}

			}
		}


	}
}

void Kmap::printSeperated()
{
	for (int i = 0; i < seperated.size(); i++)
	{
		cout << seperated[i] << endl;
	}
}
void Kmap::printOriginal()
{
	cout << original << endl;
}

void Kmap::printTempMap()
{
	for (int i = 0; i < map_temp.size(); i++)
	{
		for (int j = 0; j < map_temp[i].size(); j++)
		{
			cout << map_temp[i][j] << " ";
		}
		cout << endl;
	}

}
void Kmap::printMap()
{
	ofstream ofile;
	ofile.open("output.txt");
	if (false == ofile.is_open())
	{
		cerr << "open file error" << endl;
	}

	char ch[8] = { '0','0','0','1','1','1','1','0' };
	char ch1[4] = { '0','0','1','1' };
	char ch2[4] = { '0','1','1','0' };
	cout << "\t=============KMAP=============" << endl << endl << endl;
	ofile << "\t=============KMAP=============" << endl << endl << endl;

	cout << " \t CD\\AB| ";
	ofile << " \t CD\\AB| ";
	for (int i = 0; i < 8; i++)
	{
		cout << ch[i];
		ofile << ch[i++];
		cout << ch[i] << " |  ";
		ofile << ch[i] << " |  ";
	}
	cout << endl;
	ofile << endl;
	cout << "\t--------------------------------" << endl;
	ofile << "\t--------------------------------" << endl;

	for (int i = 0; i < 4; i++)
	{
		cout << " \t   ";
		ofile << " \t   ";
		cout << ch1[i] << ch2[i] << " | ";
		ofile << ch1[i] << ch2[i] << " | ";
		for (int j = 0; j < 4; j++)
		{
			cout << map_temp[i][j] << "  |  ";
			ofile << map_temp[i][j] << "  |  ";
		}
		cout << endl;
		ofile << endl;
		cout << "\t--------------------------------" << endl;
		ofile << "\t--------------------------------" << endl;
	}
	ofile.close();
}
/*
cout << "==================================KMAP=================================" << endl;
cout << "  \\AB |									" << endl;
cout << " CD\\	|   00  |	01	|	11	|	10		" << endl;
cout << "-----------------------------------------------------------------------" << endl;
cout << "00	|	|		|		|			" << endl;
cout << "-----------------------------------------------------------------------" << endl;
cout << "01	|	|		|		|			" << endl;
cout << "-----------------------------------------------------------------------" << endl;
cout << "11	|	|		|		|			" << endl;
cout << "-----------------------------------------------------------------------" << endl;
cout << "10	|	|		|		|			" << endl;
*/
/*
		cout << "    \t   |    |     |     |     |     |     |     |   " << endl;

// 畫
for (v = column - 1; v >= 0; --v)
{
	cout << (v + 1) << "   \t   | ";
	for (u = 0; u < row; ++u)
	{
		c = container[u][v];

		if (c == '1')
		{
			c = 'o';
		}
		else if (c == '2')
		{
			c = 'x';
		}
		cout << c << "  |  ";

	}
	cout << endl;
	// 空一行
	cout << "    \t   |    |     |     |     |     |     |     |   " << endl;
}


*/



//simplifyer
void Kmap::simplify()
{
	int k = 0;		//groupSolution row size
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j].first == 1)
			{
				findPrimeImpliment(i, j, k);
				k++;
			}
		}

	}
	groupSolutions_size = k;

	pair<int, int> p3 = groupSolutions[0][2];
	pair<int, int> p4 = groupSolutions[0][1];



	//find whether essential


	int essential_rowSize;
	essential_rowSize = isEssential(k);
	essential_size = essential_rowSize;

	int o = essential[1][3].first;
	int p = essential[1][3].second;
	//close
	for (int i = 0; i < essential.size(); i++)
	{
		closeOnMatrix(essential[i]);
	}

	//check the remains

	int remains_rowSize = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map_temp[i][j] == 1)
			{
				remains_rowSize = loopRemain(k, i, j);
			}

		}
	}
	remains_size = remains_rowSize;

	keyINMinterm();
	printSimplify(essential_rowSize, remains_rowSize);
}


void Kmap::findPrimeImpliment(int i, int j, int rowIndex)
{
	vector<pair<int, int>>group;
	pair<int, int> index;
	bool foundGroup = false;
	int neighbor[4][2] = {
							{0,1},//right
							{1,0},//down
							{0,-1},//left
							{-1,0}//ip
	};
	//1*1
	index.first = i;		//1
	index.second = j;
	group.push_back(index);

	for (int n = 0; n < 4; n++)			//check for each direction  (neighbor)
	{
		//2*1	
		int q = (i + neighbor[n][0] + 4) % 4;
		int w = (j + neighbor[n][1] + 4) % 4;
		int e = map_temp[(i + neighbor[n][0] + 4) % 4][(j + neighbor[n][1] + 4) % 4];


		if (map_temp[(i + neighbor[n][0] + 4) % 4][(j + neighbor[n][1] + 4) % 4] == 1)
		{
			index.first = (i + neighbor[n][0] + 4) % 4;		//2
			index.second = (j + neighbor[n][1] + 4) % 4;
			group.push_back(index);

			//4*1
			q = (i + 2 * neighbor[n][0] + 4) % 4;
			w = (j + 2 * neighbor[n][1] + 4) % 4;
			e = (i + 3 * neighbor[n][0] + 4) % 4;
			int r = (j + 3 * neighbor[n][1] + 4) % 4;
			int t = map_temp[(i + 2 * neighbor[n][0] + 4) % 4][(j + 2 * neighbor[n][1] + 4) % 4];
			int y = map_temp[(i + 3 * neighbor[n][0] + 4) % 4][(j + 3 * neighbor[n][1] + 4) % 4];


			if (map_temp[(i + 2 * neighbor[n][0] + 4) % 4][(j + 2 * neighbor[n][1] + 4) % 4] == 1 && map_temp[(i + 3 * neighbor[n][0] + 4) % 4][(j + 3 * neighbor[n][1] + 4) % 4] == 1)
			{
				index.first = (i + 2 * neighbor[n][0] + 4) % 4;		//3
				index.second = (j + 2 * neighbor[n][1] + 4) % 4;
				group.push_back(index);

				index.first = (i + 3 * neighbor[n][0] + 4) % 4;		//4
				index.second = (j + 3 * neighbor[n][1] + 4) % 4;
				group.push_back(index);

				if (map_temp[(i + 0 * neighbor[n][0] + neighbor[(n + 1) % 4][0] + 4) % 4][(j + 0 * neighbor[n][1] + neighbor[(n + 1) % 4][1] + 4) % 4] == 1 &&	// neighbor[(n + 1) % 4 is another 4*1   
					map_temp[(i + 1 * neighbor[n][0] + neighbor[(n + 1) % 4][0] + 4) % 4][(j + 1 * neighbor[n][1] + neighbor[(n + 1) % 4][1] + 4) % 4] == 1 &&	//if is 4*1 ,then it moves right or left
					map_temp[(i + 2 * neighbor[n][0] + neighbor[(n + 1) % 4][0] + 4) % 4][(j + 2 * neighbor[n][1] + neighbor[(n + 1) % 4][1] + 4) % 4] == 1 &&	//if is 1*4 ,then it moves up or down
					map_temp[(i + 3 * neighbor[n][0] + neighbor[(n + 1) % 4][0] + 4) % 4][(j + 3 * neighbor[n][1] + neighbor[(n + 1) % 4][1] + 4) % 4] == 1)
				{
					index.first = (i + 0 * neighbor[n][0] + neighbor[(n + 1) % 4][0] + 4) % 4;		//5
					index.second = (j + 0 * neighbor[n][1] + neighbor[(n + 1) % 4][1] + 4) % 4;
					group.push_back(index);

					index.first = (i + 1 * neighbor[n][0] + neighbor[(n + 1) % 4][0] + 4) % 4;		//6
					index.second = (j + 1 * neighbor[n][1] + neighbor[(n + 1) % 4][1] + 4) % 4;
					group.push_back(index);

					index.first = (i + 2 * neighbor[n][0] + neighbor[(n + 1) % 4][0] + 4) % 4;		//7
					index.second = (j + 2 * neighbor[n][1] + neighbor[(n + 1) % 4][1] + 4) % 4;
					group.push_back(index);

					index.first = (i + 3 * neighbor[n][0] + neighbor[(n + 1) % 4][0] + 4) % 4;		//8
					index.second = (j + 3 * neighbor[n][1] + neighbor[(n + 1) % 4][1] + 4) % 4;
					group.push_back(index);

					//end this index group

					groupSolutions[rowIndex] = group;


					foundGroup = true;
					group.clear();
					break;
				}
			}
			//2*2
			else if (map_temp[(i + 0 * neighbor[n][0] + neighbor[(n + 1) % 4][0] + 4) % 4][(j + 0 * neighbor[n][1] + neighbor[(n + 1) % 4][1] + 4) % 4] == 1 &&		//上正方
				map_temp[(i + 1 * neighbor[n][0] + neighbor[(n + 1) % 4][0] + 4) % 4][(j + 1 * neighbor[n][1] + neighbor[(n + 1) % 4][1] + 4) % 4] == 1)
			{
				index.first = (i + 0 * neighbor[n][0] + neighbor[(n + 1) % 4][0] + 4) % 4;		//3
				index.second = (j + 0 * neighbor[n][1] + neighbor[(n + 1) % 4][1] + 4) % 4;
				group.push_back(index);

				index.first = (i + 1 * neighbor[n][0] + neighbor[(n + 1) % 4][0] + 4) % 4;		//4
				index.second = (j + 1 * neighbor[n][1] + neighbor[(n + 1) % 4][1] + 4) % 4;
				group.push_back(index);
			}

			else if (map_temp[(i + 0 * neighbor[n][0] - neighbor[(n + 1) % 4][0] + 4) % 4][(j + 0 * neighbor[n][1] - neighbor[(n + 1) % 4][1] + 4) % 4] == 1 &&		//下正方
				map_temp[(i + 1 * neighbor[n][0] - neighbor[(n + 1) % 4][0] + 4) % 4][(j + 1 * neighbor[n][1] - neighbor[(n + 1) % 4][1] + 4) % 4] == 1)
			{
				index.first = (i + 0 * neighbor[n][0] - neighbor[(n + 1) % 4][0] + 4) % 4;		//3
				index.second = (j + 0 * neighbor[n][1] - neighbor[(n + 1) % 4][1] + 4) % 4;
				group.push_back(index);

				index.first = (i + 1 * neighbor[n][0] - neighbor[(n + 1) % 4][0] + 4) % 4;		//4
				index.second = (j + 1 * neighbor[n][1] - neighbor[(n + 1) % 4][1] + 4) % 4;
				group.push_back(index);
			}

			if (!groupSolutions[rowIndex].empty())
			{
				groupSolutions[rowIndex] = group;
			}
			else
			{
				for (int g = 0; g < group.size(); g++)
				{
					groupSolutions[rowIndex].push_back(group[g]);
					//cout << groupSolutions[rowIndex][g].first << " " << groupSolutions[rowIndex][g].second << endl;
				}
			}

			foundGroup = true;
			group.clear();

			// if have 2*1 through the follow ==>be the first elemesnt of another prime implicant,if have not 2*1 through the follow ==>be the last element (itself)
			index.first = i;	//1	  
			index.second = j;
			group.push_back(index);

		}

	}
	if (foundGroup == false)
	{
		groupSolutions[rowIndex] = group;
	}

}

int Kmap::isEssential(int vectorSize)
{
	int rowindex = 0;
	for (int i = 0; i < vectorSize; i++)
	{
		int counter = 0;
		for (int j = 0; j < groupSolutions[i].size(); j++)
		{

			pair<int, int> p2 = groupSolutions[i][j];
			pair<int, int> p1 = groupSolutions[i][0];
			if (groupSolutions[i][j] == groupSolutions[i][0])
			{
				if (true)
				{
					counter++;
				}

			}
		}
		if (counter == 1)		//is essential
		{
			essential[rowindex] = groupSolutions[i];
			rowindex++;
		}
	}

	return rowindex;
}

void Kmap::closeOnMatrix(vector<pair<int, int>>needRemove)
{
	for (int i = 0; i < needRemove.size(); i++)
	{
		map_temp[needRemove[i].first][needRemove[i].second] = 0;
	}
}

int Kmap::loopRemain(int vectorSize, int i, int j)
{
	pair<int, int> index_max(0, 1);		//store biggest prime implicant
	int counter = 1;
	int n = 0;

	//find biggest implicant
	for (int k = 0; k < vectorSize; k++)
	{
		if (groupSolutions[k][0].first == i && groupSolutions[k][0].second == j)			//the all prime ans in groupSolution
		{
			for (int index = 0; index < groupSolutions[k].size(); index++)
			{
				if (!(groupSolutions[k][0].first == i && groupSolutions[k][0].second == j))
				{
					counter++;
				}
				else
				{
					if (counter > index_max.second)
					{
						index_max.first = index;
						index_max.second = counter;
					}
					else if (counter == index_max.second)			//OR may present in ans			//////*/*/*/*///////////////////////////////////////////////////////////////////////////
					{

					}

					counter = 1;
				}
			}
			//store biggest implicant
			for (int w = index_max.first; w < (index_max.first + index_max.second); w++)
			{
				remains[n].push_back(groupSolutions[k][w]);

				//remove mapt_emp
				map_temp[groupSolutions[k][w].first][groupSolutions[k][w].second] = 0;

			}
			n++;
		}
		break;		//not same row ==>break
	}
	return n;
}

void Kmap::keyINMinterm()
{
	//essential

	for (int i = 0; i < essential_size; i++)
	{
		for (int j = 0; j < essential[i].size(); j++)
		{
			essential_minterm[i].push_back(matrix[essential[i][j].first][essential[i][j].second]);
		}
		std::sort(essential_minterm[i].begin(), essential_minterm[i].end());
	}

	for (int i = 0; i < essential_size - 1; i++)
	{
		for (int j = i + 1; j < essential_size; j++)
		{
			if (essential_minterm[i] == essential_minterm[j])
			{
				essential_minterm[j].clear();
			}
		}
	}

	//remains
	for (int i = 0; i < remains_size; i++)
	{
		for (int j = 0; j < remains_minterm[i].size(); j++)
		{
			remains_minterm[i].push_back(matrix[remains[i][j].first][remains[i][j].second]);
		}
		std::sort(remains_minterm[i].begin(), remains_minterm[i].end());
	}
	for (int i = 0; i < remains_size - 1; i++)
	{
		for (int j = i + 1; j < remains_size; j++)
		{
			if (remains_minterm[i] == remains_minterm[j])
			{
				remains_minterm[j].clear();
			}
		}
	}

}


void Kmap::printSimplify(int essential_rowSize, int remain_rowSize)
{
	ofstream ofile;
	ofile.open("output.txt", ios::app);
	if (false == ofile.is_open())
	{
		cerr << "open file error" << endl;
	}

	//essential
	cout << endl;
	ofile << endl;

	int counter = 1;
	for (int i = 0; i < essential_rowSize; i++)				//跑group
	{
		if (!(essential_minterm[i].empty()))
		{
			cout << "group" << counter << " :";
			ofile << "group" << counter << " :";
			for (int j = 0; j < essential_minterm[i].size(); j++)
			{
				cout << essential_minterm[i][j] << " ";
				ofile << essential_minterm[i][j] << " ";
			}
			cout << endl;
			ofile << endl;

			//char
			cout << "simplification of group" << counter << " ==>";

			f += printChar(essential_minterm[i].size(), essential_minterm[i], counter);
			f += "+";

			cout << endl;
			ofile << endl;
			counter++;
		}
	}

	//remains

	ofile << endl << endl;
	for (int i = 0; i < remain_rowSize; i++)
	{
		if (!(remains_minterm[i].empty()))
		{
			cout << "group" << counter << " :";
			ofile << "group" << counter << " :";
			for (int j = 0; j < remains_minterm[i].size(); j++)
			{
				cout << remains_minterm[i][j] << " ";
				ofile << remains_minterm[i][j] << " ";
			}
			cout << endl;
			ofile << endl;

			//char
			cout << "simplification of group" << counter << " ==>";

			f += printChar(remains_minterm[i].size(), remains_minterm[i], counter);
			f += "+";

			cout << endl;
			ofile << endl;
			counter++;
		}
	}
	f.pop_back();
	cout << "F(A,B,C,D) =" << f;
	ofile << "F(A,B,C,D) =" << f;
	ofile.close();
}


string Kmap::printChar(int minterms_num, vector<int>& minterm, int counter)
{
	ofstream ofile;
	ofile.open("output.txt", ios::app);
	if (false == ofile.is_open())
	{
		cerr << "open file error" << endl;
	}
	ofile << "simplification of group" << counter << " ==>";

	string temp;
	int value;
	int charTable[16][4];
	for (int i = 0; i < 16; i++)
	{
		value = i;
		for (int j = 3; j > -1; j--)
		{
			charTable[i][j] = value % 2;
			value /= 2;
		}
	}
	int** arrPtr = new int* [minterms_num];
	for (int i = 0; i < minterms_num; i++)
	{
		arrPtr[i] = &charTable[minterm[i]][0];
	}
	for (int j = 0; j < 4; j++)
	{

		bool ifSame = true;
		for (int i = 0; i < minterms_num; i++)
		{
			if (arrPtr[i][j] != arrPtr[0][j])
			{
				ifSame = false;
				break;
			}
		}
		if (ifSame == true)	//need printed
		{
			if (arrPtr[0][j] == 1)
			{
				switch (j)
				{
				case 0:
					cout << 'A';
					ofile << 'A';
					temp += "A";
					break;
				case 1:
					cout << 'B';
					ofile << 'B';
					temp += "B";
					break;
				case 2:
					cout << 'C';
					ofile << 'C';
					temp += "C";
					break;
				case 3:
					cout << 'D';
					ofile << 'D';
					temp += "D";
					break;
				default:
					break;
				}
			}
			else if (arrPtr[0][j] == 0)
			{
				switch (j)
				{
				case 0:
					cout << "A'";
					ofile << "A'";
					temp += "A'";
					break;
				case 1:
					cout << "B'";
					ofile << "B'";
					temp += "B'";
					break;
				case 2:
					cout << "C'";
					ofile << "C'";
					temp += "C'";
					break;
				case 3:
					cout << "D'";
					ofile << "D'";
					temp += "D'";
					break;
				default:
					break;
				}
			}
		}
	}
	delete[]arrPtr;
	ofile.close();

	return temp;
}





int main()
{
	Kmap kmap;

	kmap.readSop();
	kmap.sopProcess(kmap.getOriginal());
	kmap.printOriginal();
	kmap.printSeperated();


	vector<vector<int>>mintermNumber;
	mintermNumber.resize(kmap.getSeperatedSize());			//其實可省

	for (int i = 0; i < kmap.getSeperatedSize(); i++)
	{
		vector<int>mintermNumberForEach;
		mintermNumber[i] = kmap.mintermNumber(kmap.getSeperated()[i], mintermNumberForEach);

		kmap.keyInmap(kmap.matrix, mintermNumber[i]);

		for (int j = 0; j < mintermNumber[i].size(); j++)
		{
			cout << mintermNumber[i][j] << " ";
		}
		cout << endl;
	}
	kmap.printTempMap();
	kmap.printMap();

	//simplify
	kmap.simplify();

	system("pause");
	return 0;
}


