
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

	// 讀文字檔
	static vector<string> read_string(fstream& iofile)
	{
		vector<string> allstream;
		char temp[1000];

		while (true)
		{
			memset(temp, 0, sizeof(temp));
			iofile.get(temp, sizeof(temp), '\n');

			if (iofile.gcount()==0)    //防呆
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

	// 先判斷內容，有相同的物件就不加入列表
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

	// 判斷沒有就加入，有就不加入
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

	// 判斷沒有就加入，有就不加入
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

	// 判斷沒有就加入，有就不加入
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


//int 的二維array
class MVector
{
private:
	// 二維容器
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
	// 清掉全部
	void Clear()
	{
		LCS_problem::deletevector(_mVector);
	}


	// 設定大小
	void build_matrix(const int len_strA, const int len_strB)
	{
		int i;
		int* row;
		// 先清掉舊的
		Clear();
		
		rowsize = len_strB;
		for (i = 0; i < len_strA; ++i)
		{
			row = new int[len_strB];					// LCS[m][n] 的 int 陣列
			memset(row, 0, sizeof(int) * len_strB); //全部先初始化為0
			_mVector.push_back(row);
		}
	}

	// 由列取行
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


	// 原點了，把值加進去
	memset(ch, 0, sizeof(ch));
	
	i = colIumnindex;
	j = rowindex;


	// 回到原點，就加回去
	if ((i == 0) || (j == 0))   //表示這是最後一個相同的字母
	{
		if (linkcount == 0)//走到完
		{ 
			LCS_problem::judge_whether_add(derection, pstr);
		return 0;
		}
	}

	// 依i,j為起點，往左，往上走
	while (true)
	{
		// 結束
		if ((i == 0) || (j == 0))
		{ 
			break;
		}

		// 看那邊大往那邊走
		if (v[i - 1][j] == v[i][j - 1])//一樣大   ==>往左上跳一格，再呼叫 LCS 進行下一個尋找
		{

			// 判斷是不是與自己相同，
			// 是的話，走到與自己不同的位置
			do
			{
				m = v[i][j];// 目前位置
				a = j;
				// 往上
				while (j > 1)
				{
					if (v[i][j - 1] != m) //與本地值相等
						break;
					j--;
				};
				// 往右
				b = i;
				while (i > 1)
				{
					if (v[i - 1][j] != m) //與本地值相等
						break;
					// 與ａ字串相同，跳
					if (strA[i - 1] == strB[j - 1])//相同
					{
						ch[0] = strA[i - 1];
						str = ch;
						str += pstr;
						LCS(derection, str, vec, strA, strB, i - 1, j - 1, linkcount - 1);
					}

					//
					i--;
				};
				
				
				//不同，直接跳(.左上都比自己小時)
				ch[0] = strA[i - 1];
				str = ch;
				str += pstr;
				LCS(derection, str, vec, strA, strB, i - 1, j - 1, linkcount - 1);
				j = a;
				i--;


				// 判斷完了
				if (i == 0)
				{ 
					return 0;
				}
				// 左值與自己不一樣
				if (v[i - 1][j] != m)
				{
					return 0;
				}
			} 
			while ((i >= 1) && (j >= 1));
		}
		else if (v[i - 1][j] < v[i][j - 1]) // 往上比較大
		{
			j--;
		}
		else //if( v[i-1][j] > v[i][j-1] )// 往左比較大的
		{
			i--;
		}


	}

	return 0;
}


// 將lcs分割輸出
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
			// 下一個不相同，
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



	//得檔
	while (true)
	{
		fstream iofile;
		char inputfile_name[100];

		memset(inputfile_name, 0, sizeof(inputfile_name));//初始化清空

		cout << "Please input the file name ：";
		cin >> inputfile_name;



		// 開檔
		iofile.open(inputfile_name);
		//防呆
		if ( iofile.is_open()== false)
		{
			cerr << "error" << endl;
			continue;
		}



		// 讀檔
		string_temp = LCS_problem::read_string(iofile);
		iofile.close();

		//判斷檔案行數， >= 2 就繼續
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


	
	// 開始跑囉 //可知道兩字串中有多少相同的字母
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

		MVector v; //2維陣列
		int longest_string;//最大路徑
		list<string> derection;//輸出位置

/*
		char strA[1024] ;
		char strB[1024] ;
		memset( strA , 0 , sizeof( strA )) ;
		memset( strB , 0 , sizeof( strB )) ;

*/


// 取二字長度當m,n建立map，
// 需第0號陣列當緩衝，所以 m,n 數為 strlen + 1

		int a = strlen(strA) + 1; // [0]不用
		int b = strlen(strB) + 1;

		int i, j, n;

		// 設定格子數
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
	//	跑 m* n 次
		for (j = 1; j < b; ++j)
		{

			//			cout << strB[j-1] << tabStr << "0" << tabStr ;
			for (i = 1; i < a; ++i)
			{
			
				if (strA[i - 1] == strB[j - 1])	// strA[i] == strB[i] ，表有相同字母
				{ 
					v[i][j] = v[i - 1][j - 1] + 1;	//   取左上角的步數+1 
				}

				else //不相同，兩者取大
				{ 
					v[i][j] = max(v[i - 1][j], v[i][j - 1]);	//   取上與左兩者取大為該格步數
				}
			
				//test
		//		cout << v[i][j] << tabStr ;
			}

			//	cout << endl ;
		}
		// 最大的步數，己累積在第m,n格( v[i-1][j-1] ;


		//lcs長度
		longest_string = v[a - 1][b - 1];
		cout  << longest_string << endl;

		//每一個lcs解
		// 找路徑
		i = a - 1;
		j = b - 1;

		n = longest_string;

		// LCS
		LCS(derection, "", v, strA, strB, i, j, n);

		//全部lcs個數
		cout  << derection.size() << endl;



		// 輸出值
		for (listStr = derection.begin(); listStr != derection.end(); listStr++)
		{
			cout  << listStr->c_str() << endl;
		}
		cout << endl;



		// 存檔
		fstream fd;

		fd.open("result_F64096114.txt", ios::out | ios::trunc);

		if (fd.is_open()==false )
		{
			// 檔案錯誤
			cout << "open file [result_F64096114.txt] error" << endl;
		}
		else
		{
			//lcs長度
			longest_string = v[a - 1][b - 1];
			fd << longest_string << endl;


			//全部lcs個數
			fd  << derection.size() << endl;


			// 輸出值
			for (listStr = derection.begin(); listStr != derection.end(); listStr++)
			{

					fd  << listStr->c_str() << endl;
				
			}

			cout << "have writen file " << endl;

			//結束
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

