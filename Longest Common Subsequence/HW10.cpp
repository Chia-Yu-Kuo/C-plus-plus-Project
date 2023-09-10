
#include <iostream>
#include <string>
#include <list>
#include <tchar.h>
#include <iterator>
#include <vector>
#include <fstream>



using namespace std;


class LCS_problem
{
public:

	// Ū��r��
	static vector<string> read_string(fstream& iofile)
	{
		vector<string> allstream;
		char temp[1000];

		while (true)
		{
			memset(temp, 0, sizeof(temp));
			iofile.get(temp, sizeof(temp), '\n');

			if (iofile.gcount()==0)    //���b
			{
				break;
			}
			iofile.ignore(1, '\n');

			allstream.push_back(temp);

		}
		return allstream;
	}

	/*

	static vector<string> Split(const char* inStr, const char inKey)
	{
		char buffer[1000];
		const char* s;
		const char* e;
		int len;
		vector<string> ret;
		s = inStr;
		while (0 != s[0])
		{
			e = strchr(s, inKey);
			if (e == NULL)
			{
				len = strlen(s);
				e = s + len;
			}
			else
			{
				len = e - s;
				++e;
			}

			memcpy(buffer, s, len);
			buffer[len] = 0;
			ret.push_back(buffer);
			s = e;
		}
		// 
		return ret;
	}
	*/


	// delete 
	template<class T>
	static void deletevector(vector<T>& inVector)
	{
		int i, n;
		n = inVector.size();
		for (i = 0; i < n; ++i)
		{
			delete inVector[i];
		}
		inVector.clear();
	}

	// ���P�_���e�A���ۦP������N���[�J�C��
//	template<class T>
	static void whether_add(list<string>& inList, const string& inObj)
	{
		list<string>::const_iterator i;

		for (i = inList.begin(); i != inList.end(); i++)
		{
			if ((*i) == inObj)
			{
				return;
			}
		}
		inList.push_back(inObj);
	}

	// �P�_�S���N�[�J�A���N���[�J
//	template<class T>
	static void whether_add(list<string>& outToList, vector<string>& inSrcVector)
	{
		int i, n;
		n = inSrcVector.size();
		for (i = 0; i < n; ++i)
		{

			whether_add(outToList, inSrcVector[i]);
		}
	}

	// �P�_�S���N�[�J�A���N���[�J
	static void judge_whether_add(list<string>& inList, const string& inObj)
	{
		list<string>::iterator i;

		for (i = inList.begin(); i != inList.end(); i++)
		{
			if (strcmp(inObj.c_str(), i->c_str())==0)
			{
				return;
			}
		}
		inList.push_back(inObj);
	}

	// �P�_�S���N�[�J�A���N���[�J
//	template<class T>
	static void whether_add(vector<string>& inVector, const string& inObj)
	{
		int i, n;
		n = inVector.size();
		for (i = 0; i < n; ++i)
		{
			if (inVector[i] == inObj)
			{ 
				return;
			}
		}
		inVector.push_back(inObj);
	}

};


//int ���G��array
class MVector
{
private:
	// �G���e��
	vector<int*> _mVector;
	// Row Size ;
	int rowsize;


public:
	MVector()
	{
		rowsize = 0;
	}

	~MVector()
	{
		Clear();
	}


public:
	int ColSize() const { return _mVector.size(); }
	int RowSize() const { return rowsize; }


public:
	// �M������
	void Clear()
	{
		LCS_problem::deletevector(_mVector);
	}


	// �]�w�j�p
	void build_matrix(const int len_strA, const int len_strB)
	{
		int i;
		int* row;
		// ���M���ª�
		Clear();
		
		rowsize = len_strB;
		for (i = 0; i < len_strA; ++i)
		{
			row = new int[len_strB];					// LCS[m][n] �� int �}�C
			memset(row, 0, sizeof(int) * len_strB); //��������l�Ƭ�0
			_mVector.push_back(row);
		}
	}

	// �ѦC����
	int* operator[] (const int inIndex)
	{
		return _mVector[inIndex];
	}
	const int* operator[] (const int inIndex) const
	{
		return _mVector[inIndex];
	}

};




//		LCS(derection, "", v, strA, strB, i, j, n);
int LCS(list<string>& derection, const string& pstr, const MVector& vec, const char* strA, const char* strB, const int colIumnindex, const int rowindex, const int linkcount)
{
	const MVector& v = vec;
	int i, j;
	int a, b, m;
	char ch[8];
	string str;


	// ���I�F�A��ȥ[�i�h
	memset(ch, 0, sizeof(ch));
	
	i = colIumnindex;
	j = rowindex;


	// �^����I�A�N�[�^�h
	if ((i == 0) || (j == 0))   //��ܳo�O�̫�@�ӬۦP���r��
	{
		if (linkcount == 0)//���짹
		{ 
			LCS_problem::judge_whether_add(derection, pstr);
		return 0;
		}
	}

	// ��i,j���_�I�A�����A���W��
	while (true)
	{
		// ����
		if ((i == 0) || (j == 0))
		{ 
			break;
		}

		// �ݨ���j�����䨫
		if (v[i - 1][j] == v[i][j - 1])//�@�ˤj   ==>�����W���@��A�A�I�s LCS �i��U�@�ӴM��
		{

			// �P�_�O���O�P�ۤv�ۦP�A
			// �O���ܡA����P�ۤv���P����m
			do
			{
				m = v[i][j];// �ثe��m
				a = j;
				// ���W
				while (j > 1)
				{
					if (v[i][j - 1] != m) //�P���a�Ȭ۵�
						break;
					j--;
				};
				// ���k
				b = i;
				while (i > 1)
				{
					if (v[i - 1][j] != m) //�P���a�Ȭ۵�
						break;
					// �P��r��ۦP�A��
					if (strA[i - 1] == strB[j - 1])//�ۦP
					{
						ch[0] = strA[i - 1];
						str = ch;
						str += pstr;
						LCS(derection, str, vec, strA, strB, i - 1, j - 1, linkcount - 1);
					}

					//
					i--;
				};
				
				
				//���P�A������(.���W����ۤv�p��)
				ch[0] = strA[i - 1];
				str = ch;
				str += pstr;
				LCS(derection, str, vec, strA, strB, i - 1, j - 1, linkcount - 1);
				j = a;
				i--;


				// �P�_���F
				if (i == 0)
				{ 
					return 0;
				}
				// ���ȻP�ۤv���@��
				if (v[i - 1][j] != m)
				{
					return 0;
				}
			} 
			while ((i >= 1) && (j >= 1));
		}
		else if (v[i - 1][j] < v[i][j - 1]) // ���W����j
		{
			j--;
		}
		else //if( v[i-1][j] > v[i][j-1] )// ��������j��
		{
			i--;
		}


	}

	return 0;
}


// �Nlcs���ο�X
void output_spilt_lcs(const char* inSrc, const char* inLCS)
{
	int i, n, k;
	i = 0; n = 0;
	k = 0;

	cout << inLCS << ": ";
	while (inSrc[i] != 0)
	{

		if (inSrc[i] == inLCS[n])
		{
			// �U�@�Ӥ��ۦP�A
			if (inSrc[i + 1] != inLCS[n + 1])
			{
				cout << ' ';
			}
			++n;
		}
		cout << inSrc[i];

		++i;
	}
	cout << endl;

}






int main()
{

	vector<string> string_temp;



	//�o��
	while (true)
	{
		fstream iofile;
		char inputfile_name[100];

		memset(inputfile_name, 0, sizeof(inputfile_name));//��l�ƲM��

		cout << "Please input the file name �G";
		cin >> inputfile_name;



		// �}��
		iofile.open(inputfile_name);
		//���b
		if ( iofile.is_open()== false)
		{
			cerr << "error" << endl;
			continue;
		}



		// Ū��
		string_temp = LCS_problem::read_string(iofile);
		iofile.close();

		//�P�_�ɮצ�ơA >= 2 �N�~��
		if (string_temp.size() >= 2)
		{
			break;
		}

	}


	/*
		for (i = inList.begin(); i != inList.end(); i++)
		{
			if ( strcmp(inObj.c_str(), i->c_str())==0)
			{
				cout << inList<<endl;
				cout << inObj
			}
		}
	
	
	*/



	/*
	
	for (i = 0; i < n; ++i)
		{
			if (inVector[i] == inObj)
			{ 
				cout << invector ;

			}
		}

	*/


	
	// �}�l�]�o //�i���D��r�ꤤ���h�֬ۦP���r��
//	while( true )
	{

	//	const char *tabStr = "  " ;
	//	const char *strA = "orientation" ;
	//	const char *strB = "contribute" ;
	//	const char *strA = "XMJYAUZ" ;
	//	const char *strB = "MZJAWXU" ;
	//	const char *strA = "happy" ;
	//	const char *strB = "apple" ;


		const char* strA = string_temp[0].c_str();
		const char* strB = string_temp[1].c_str();

		list<string>::const_iterator listStr;

		MVector v; //2���}�C
		int longest_string;//�̤j���|
		list<string> derection;//��X��m

/*
		char strA[1024] ;
		char strB[1024] ;
		memset( strA , 0 , sizeof( strA )) ;
		memset( strB , 0 , sizeof( strB )) ;

*/


// ���G�r���׷�m,n�إ�map�A
// �ݲ�0���}�C��w�ġA�ҥH m,n �Ƭ� strlen + 1

		int a = strlen(strA) + 1; // [0]����
		int b = strlen(strB) + 1;

		int i, j, n;

		// �]�w��l��
		v.build_matrix(a, b);

		/*
		cout << "strA:" << strA << endl;
		cout << "strB:" << strB << endl;
		*/
		/*		
		cout << tabStr << tabStr << tabStr ;
		for( i = 1 ; i < a ; ++i )
			cout << strA[i-1] << tabStr ;
		cout << endl ;
		cout << tabStr << " " ;
		for( j = 0 ; j < a ; ++j )
			cout << "0" << tabStr ;
		cout << endl ;
*/
	//	�] m* n ��
		for (j = 1; j < b; ++j)
		{

			//			cout << strB[j-1] << tabStr << "0" << tabStr ;
			for (i = 1; i < a; ++i)
			{
			
				if (strA[i - 1] == strB[j - 1])	// strA[i] == strB[i] �A���ۦP�r��
				{ 
					v[i][j] = v[i - 1][j - 1] + 1;	//   �����W�����B��+1 
				}

				else //���ۦP�A��̨��j
				{ 
					v[i][j] = max(v[i - 1][j], v[i][j - 1]);	//   ���W�P����̨��j���Ӯ�B��
				}
			
				//test
		//		cout << v[i][j] << tabStr ;
			}

			//	cout << endl ;
		}
		// �̤j���B�ơA�v�ֿn�b��m,n��( v[i-1][j-1] ;


		//lcs����
		longest_string = v[a - 1][b - 1];
		cout  << longest_string << endl;

		//�C�@��lcs��
		// ����|
		i = a - 1;
		j = b - 1;

		n = longest_string;

		// LCS
		LCS(derection, "", v, strA, strB, i, j, n);

		//����lcs�Ӽ�
		cout  << derection.size() << endl;



		// ��X��
		for (listStr = derection.begin(); listStr != derection.end(); listStr++)
		{
			cout  << listStr->c_str() << endl;
		}
		cout << endl;



		// �s��
		fstream fd;

		fd.open("result_F64096114.txt", ios::out | ios::trunc);

		if (fd.is_open()==false )
		{
			// �ɮ׿��~
			cout << "open file [result_F64096114.txt] error" << endl;
		}
		else
		{
			//lcs����
			longest_string = v[a - 1][b - 1];
			fd << longest_string << endl;


			//����lcs�Ӽ�
			fd  << derection.size() << endl;


			// ��X��
			for (listStr = derection.begin(); listStr != derection.end(); listStr++)
			{

					fd  << listStr->c_str() << endl;
				
			}

			cout << "have writen file " << endl;

			//����
			fd.close();
		}

		/*
		for( listStr = derection.begin() ; listStr != derection.end() ; listStr++ )
		{
			output_spilt_lcs( strA , listStr->c_str());
			output_spilt_lcs( strB , listStr->c_str());
			cout << endl ;
		}
		*/
	}

	return 0;
}

