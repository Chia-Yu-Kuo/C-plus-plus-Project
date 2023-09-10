
#include <iostream>
#include <tchar.h>
#include <cstdio>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>



using namespace std;


class connect_four
{
private:
	
	vector< vector< char> > container;
	vector< int > count;
	vector<int> temp;
	

	int row, column;  // 棋盤大小
	 

public:
	// 建立棋盤
	connect_four(int m, int n)
	{
		//	int i ;
		int u, v;

		row = m;
		column = n;
		for (u = 0; u < m; ++u)
		{
			vector< char> vec;
			for (v = 0; v < n; ++v)
			{
				vec.push_back(' ');
			}
			container.push_back(vec);
		}
		// 目前數量
		for (u = 0; u < m; ++u)
		{
			count.push_back(0);
		}
		// 暫存用
		for (u = 0; u < m; ++u)
		{ 
			temp.push_back(0);
		}
		//
	
	}

private:
	//學長carry


	// 畫棋盤
	void build_table()
	{
		char c;
		int u, v;

		cout << endl << endl;


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

		// 畫代碼
		cout << "\t     ";
		for (u = 0; u < row; ++u)
		{ 
			cout << (char)('1' + u) << "     ";
		}
		cout << endl;

		cout << endl << endl;

	}
private:
	// 放子
	bool pusf_chess(char c, char uid)
	{
		//	int v ;
		vector< char>& buffer = container[c];

		if (count[c] >= column)
		{
			return false;
		}
		buffer[count[c]] = uid;
		count[c] ++;
		return true;
	}
	bool buf_pop(char c)
	{
		//	int v ;
		if (count[c] <= 0)
		{ 
			return false;
		}
		vector< char>& buf = container[c];
		count[c] --;
		buf[count[c]] = ' ';

		return true;
	}
	// 判斷是否離開
	bool whether_quit(char c)
	{
		return ((c == 'Q') || (c == 'q'));
	}
	// 玩家輸入
	bool play_keyin(char current_player)
	{
		char c;
		char n;
		//
		while (1)
		{
			// 畫地圖
			build_table();


			cout << "請" << current_player << "P輸入要放的位置(1~7)：";
			while (true)
			{
				cin >> c;
				// 繼續
				if (whether_quit(c))
				{
					return false;
				}
				// 判斷
				n = c - '1';
				if ((n >= 0) && (n < row))
				{
					// 放位置
					if (false == pusf_chess(n, current_player))
					{
						cout << "這裡不能放"<<endl;
					}
					else
					{
						break;
					}
				}
				else
				{
					cout << "這裡不能放"<<endl;
				}
			}
			// 離開
			break;
		}
		return true;
	}

	// 是否在格子裡
	bool whether_in_table(int u, int v)
	{
		if (u >= 0)if (u < row)
		{
			if (v >= 0)if (v < column)
			{
				return true;
			}
		}
		return false;
	}
	// 判斷該位置是否贏
	char is_win(int u, int v, int mu, int mv, int win_cc)
	{
		int k;
		int c;
		c = container[u][v];
		if (c == ' ')
		{ 
			return 0;
		}
		// 判斷是否相同
		for (k = 1; k < win_cc; ++k)
		{
			u += mu;
			v += mv;
			// 在格子外，不用判斷了
			if ( whether_in_table(u, v) == false )
			{ 
				return 0;
			}
			if (c != container[u][v])
			{
				return 0;
			}
		}
		return c;
	}

	// 是否贏
	char is_win(int win_cc)
	{
		// 只抓四個方塊
		int mx[] = { 1 , 1 , 0 , -1 };
		int my[] = { 0 , 1 , 1 ,  1 };
		int k;
		int u, v;
		char c;

		// 以左下點開始算，判斷誰贏
		for (v = 0; v < column; ++v)
		{ 
			for (u = 0; u < row; ++u)
			{
				for (k = 0; k < 4; ++k)
				{
					c = is_win(u, v, mx[k], my[k], win_cc);
					if (c != 0)
					{ 
						return  c;
					}
				}
			}
		}
		return 0;
	}


	// 取目前最高的位置
	int get_map_top(int u)
	{
		if ((u >= 0) && (u < row)) // 左右
		{ 
			if (count[u] < column) //該 u 的數
				{
					return count[u];
				}
		}
		return -1;
	}

	
	// is tie
	bool is_tie()
	{
		int i;
		for (i = 0; i < row; ++i)
		{ 
			if (count[i] < column)
			{
				return false;
			}
		}
		return true;
	}
	
public:
	// 開始玩
	bool run()
	{
		char win;
		char uid;
		//	char c ;
		int p;
		//
		uid = '1';
		while (true)
		{
			// 畫地圖
			if (is_tie())
			{
				build_table();
				cout << "平手" << endl;
				system("pause");
				return false;
			}

			else
			{

				if (false == play_keyin(uid))
				{ 
					return false;
				}
			}
			// 判斷是否贏
			win = is_win(4);
			// 有人贏了，結束
			if (win != 0)
			{
				break;
			}
			// 換下一位選手
			uid = (uid == '1') ? '2' : '1';


		}
		// 有人贏了
		build_table();

		cout << uid << "P win" << endl;
		system("pause");
		return true;

		return true;
	}

	// 輸入對戰模式
	bool init_mode()
	{
		char ch[256];
		// 請輸入 PK 對像
		while (true)
		{
			memset(ch, 0, sizeof(ch));


			cout << "請輸入 P 開始2P / Q 離開: ";
			cin >> ch;

			switch (ch[0])
			{
			case 'P':
			case 'p':
				return true;
				break;
			case 'Q':
			case 'q':
				return false;
			default:
				cout << "error" << endl;
				break;
			}
		}
	}

};

int main()
{


	// 建地圖
	connect_four map(7, 6);


	if (map.init_mode() == false  )
	{ 
		return 0;
	}

	map.run();

	return 0;
}
