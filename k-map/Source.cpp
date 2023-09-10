#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<cstring>


using namespace std;

string readSop()
{
	ifstream  ifile;
	ifile.open("input.txt");
	if (false == ifile.is_open())
	{
		cerr << "open file error" << endl;
	}
	string original;
	getline(ifile, original);

	ifile.close();

	return original;

}

////////////////////////////////////////切字串
vector<string>split(string original, string need_remove)
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

vector<string> sopProcess(string original)
{
	vector<string>seprated = split(original, "+");

	for (int i = 0; i < seprated.size(); i++)
	{
		cout << seprated[i] << endl;
	}
	return seprated;
}

int main()
{


	sopProcess(readSop());

	return 0;
}


