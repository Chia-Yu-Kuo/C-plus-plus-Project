
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
	

	int row, column;  // �ѽL�j�p
	 

public:
	// �إߴѽL
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
		// �ثe�ƶq
		for (u = 0; u < m; ++u)
		{
			count.push_back(0);
		}
		// �Ȧs��
		for (u = 0; u < m; ++u)
		{ 
			temp.push_back(0);
		}
		//
	
	}

private:
	//�Ǫ�carry


	// �e�ѽL
	void build_table()
	{
		char c;
		int u, v;

		cout << endl << endl;


		cout << "    \t   |    |     |     |     |     |     |     |   " << endl;

		// �e
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
			// �Ť@��
			cout << "    \t   |    |     |     |     |     |     |     |   " << endl;
		}

		// �e�N�X
		cout << "\t     ";
		for (u = 0; u < row; ++u)
		{ 
			cout << (char)('1' + u) << "     ";
		}
		cout << endl;

		cout << endl << endl;

	}
private:
	// ��l
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
	// �P�_�O�_���}
	bool whether_quit(char c)
	{
		return ((c == 'Q') || (c == 'q'));
	}
	// ���a��J
	bool play_keyin(char current_player)
	{
		char c;
		char n;
		//
		while (1)
		{
			// �e�a��
			build_table();


			cout << "��" << current_player << "P��J�n�񪺦�m(1~7)�G";
			while (true)
			{
				cin >> c;
				// �~��
				if (whether_quit(c))
				{
					return false;
				}
				// �P�_
				n = c - '1';
				if ((n >= 0) && (n < row))
				{
					// ���m
					if (false == pusf_chess(n, current_player))
					{
						cout << "�o�̤����"<<endl;
					}
					else
					{
						break;
					}
				}
				else
				{
					cout << "�o�̤����"<<endl;
				}
			}
			// ���}
			break;
		}
		return true;
	}

	// �O�_�b��l��
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
	// �P�_�Ӧ�m�O�_Ĺ
	char is_win(int u, int v, int mu, int mv, int win_cc)
	{
		int k;
		int c;
		c = container[u][v];
		if (c == ' ')
		{ 
			return 0;
		}
		// �P�_�O�_�ۦP
		for (k = 1; k < win_cc; ++k)
		{
			u += mu;
			v += mv;
			// �b��l�~�A���ΧP�_�F
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

	// �O�_Ĺ
	char is_win(int win_cc)
	{
		// �u��|�Ӥ��
		int mx[] = { 1 , 1 , 0 , -1 };
		int my[] = { 0 , 1 , 1 ,  1 };
		int k;
		int u, v;
		char c;

		// �H���U�I�}�l��A�P�_��Ĺ
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


	// ���ثe�̰�����m
	int get_map_top(int u)
	{
		if ((u >= 0) && (u < row)) // ���k
		{ 
			if (count[u] < column) //�� u ����
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
	// �}�l��
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
			// �e�a��
			if (is_tie())
			{
				build_table();
				cout << "����" << endl;
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
			// �P�_�O�_Ĺ
			win = is_win(4);
			// ���HĹ�F�A����
			if (win != 0)
			{
				break;
			}
			// ���U�@����
			uid = (uid == '1') ? '2' : '1';


		}
		// ���HĹ�F
		build_table();

		cout << uid << "P win" << endl;
		system("pause");
		return true;

		return true;
	}

	// ��J��ԼҦ�
	bool init_mode()
	{
		char ch[256];
		// �п�J PK �ﹳ
		while (true)
		{
			memset(ch, 0, sizeof(ch));


			cout << "�п�J P �}�l2P / Q ���}: ";
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


	// �ئa��
	connect_four map(7, 6);


	if (map.init_mode() == false  )
	{ 
		return 0;
	}

	map.run();

	return 0;
}
