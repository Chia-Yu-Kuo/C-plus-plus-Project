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

////////////////////////////////////////���r��
vector<string>split(string original, string need_remove)
{
	vector<string>result;
	int current = 0; //�̪�� 0 ����m�}�l��
	int next = 0;
	while (next != -1)
	{
		next = original.find_first_of(need_remove, current); //�M��qcurrent�}�l�A�X�{splitSep���Ĥ@�Ӧ�m(�䤣��h�^��-1)
		if (next != current)
		{
			string tmp = original.substr(current, next - current);
			if (!tmp.empty())  //�����Ŧr��(�Y���g���ܡA���ڳ��O���βŷ|��)
			{
				result.push_back(tmp);
			}
		}
		current = next + 1; //�U���� next + 1 ����m�}�l��_�C
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


