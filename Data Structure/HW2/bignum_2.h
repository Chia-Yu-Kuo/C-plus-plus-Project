#include <iostream>
#include <string>
#include <fstream>
#include"linklist_2.h"


using namespace std;

class BigNum 
{
	friend class LinkList;
	friend class Listnode;
private:
	LinkList linklist1;
	LinkList linklist2;
	LinkList ans;
	
	string num1;
	string num2;
	string op;

	int sum;
	int cout=0;
public:
	void read_input();
	void set_list();
	void add();
	void sub();
	void print_ans();
	bool is_abs_list1_big();
	void swap(LinkList& list1, LinkList& list2);

};

void BigNum:: read_input()
{
	ifstream  ifile;
	ifile.open("test.txt");
	if (false == ifile.is_open())
	{
		cerr << "open file error" << endl;
	}

	getline(ifile, num1);
	getline(ifile, op);
	getline(ifile, num2);

	ifile.close();

	/// ///////////// set list

	if (num1.at(0) == '-')
	{
		linklist1.sign = 1;
		for (int i = 1; i < num1.length(); i++)
		{
			linklist1.insert_node((num1[i] - '0'), i-1);
			linklist1.size++;
		}
	}
	else 
	{
		for (int i = 0; i < num1.length(); i++)
		{
			linklist1.insert_node((num1[i] - '0'), i);
			linklist1.size++;
		}
	}
	//linklist1.print_list();

	/// <summary>
	/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////����cout???????????????????????????????????????????
	/// </summary>

	if (num2.at(0) == '-')
	{
		linklist2.sign = 1;
		for (int i = 1; i < num2.length(); i++)
		{
			linklist2.insert_node((num2[i] - '0'), i - 1);
			linklist2.size++;
		}
	}
	else
	{
		for (int i = 0; i < num2.length(); i++)
		{
			linklist2.insert_node((num2[i] - '0'), i);
			linklist2.size++;
		}
	}
	//linklist2.print_list();

	if (linklist1.sign == 0 && linklist2.sign == 0)
	{
		if (op == "+")
		{
			add();
		}
		else if (op == "-")
		{
			if (!is_abs_list1_big())
			{
				swap(linklist1, linklist2);
				ans.sign = 1;
			}
			sub();
		}
	}
	else if (linklist1.sign == 0 && linklist2.sign == 1)
	{
		if (op == "+")			////  ??? ans +-
		{
			if (!is_abs_list1_big())
			{
				swap(linklist1, linklist2);
				ans.sign = 1;
			}
			sub();
		}
		else if (op == "-")
		{
			add();
		}
	}
	else if (linklist1.sign == 1 && linklist2.sign == 0)				///////////////// ????????
	{
		if (op == "+")
		{
			if (!is_abs_list1_big())
			{
				swap(linklist1, linklist2);
				ans.sign = 0;
			}
			else
			{
				ans.sign = 1;
			}
			sub();
		}
		else if (op == "-")
		{
			add();
			ans.sign = 1;

		}
	}
	else if (linklist1.sign == 1 && linklist2.sign == 1)
	{
		if (op == "+")
		{
			add();
			ans.sign = 1;
		}
		else if (op == "-")
		{
			if (!is_abs_list1_big())
			{
				swap(linklist1, linklist2);
				ans.sign = 0;
			}
			else
			{
				ans.sign = 1;
			}
			sub();
		}
	}
}

void BigNum::swap(LinkList& list1, LinkList& list2)
{
	LinkList temp;
	temp = list1;
	list1 = list2;
	list2 = temp;
}

void BigNum::set_list() 
{
	linklist1.initialize_headnode();
	linklist2.initialize_headnode();
	ans.initialize_headnode();
}

void BigNum::add() 
{
	linklist1.current_point_to = linklist1.headnodePtr->llink;
	linklist2.current_point_to = linklist2.headnodePtr->llink;


	while ((linklist1.current_point_to != linklist1.headnodePtr) || (linklist2.current_point_to != linklist2.headnodePtr))
	{	
		if (linklist1.current_point_to != linklist1.headnodePtr && linklist2.current_point_to == linklist2.headnodePtr)			//list1����
		{
			sum = (linklist1.current_point_to->data  + cout) % 10;
			cout = (linklist1.current_point_to->data  + cout) / 10;

			linklist1.current_point_to = linklist1.current_point_to->llink;
		}
		else if (linklist1.current_point_to == linklist1.headnodePtr && linklist2.current_point_to != linklist2.headnodePtr)		//list2����
		{
			sum = (linklist2.current_point_to->data + cout) % 10;
			cout = (linklist2.current_point_to->data + cout) / 10;

			linklist2.current_point_to = linklist2.current_point_to->llink;
		}
		else if (linklist1.current_point_to != linklist1.headnodePtr && linklist2.current_point_to != linklist2.headnodePtr)
		{
			sum = (linklist1.current_point_to->data + linklist2.current_point_to->data + cout) % 10;
			cout = (linklist1.current_point_to->data + linklist2.current_point_to->data + cout) / 10;

			linklist1.current_point_to = linklist1.current_point_to->llink;
			linklist2.current_point_to = linklist2.current_point_to->llink;
		}

		ans.insert_node(sum, 0);

		
		
	}
	if (cout!=0)
	{
		ans.insert_node(cout,0);
	}

}

void BigNum::sub()
{
	linklist1.current_point_to = linklist1.headnodePtr->llink;
	linklist2.current_point_to = linklist2.headnodePtr->llink;
	while ((linklist1.current_point_to != linklist1.headnodePtr) || (linklist2.current_point_to != linklist2.headnodePtr))
	{
		if (linklist1.current_point_to != linklist1.headnodePtr && linklist2.current_point_to != linklist2.headnodePtr)
		{
			if ( (linklist1.current_point_to->data +cout )>= linklist2.current_point_to->data)
			{
				sum = (linklist1.current_point_to->data + cout) - (linklist2.current_point_to->data);
				cout = 0;
			}
			else
			{
				sum = (linklist1.current_point_to->data + cout + 10) - (linklist2.current_point_to->data);
				cout = -1;
			}
			linklist1.current_point_to = linklist1.current_point_to->llink;
			linklist2.current_point_to = linklist2.current_point_to->llink;
		}
		else if (linklist1.current_point_to != linklist1.headnodePtr && linklist2.current_point_to == linklist2.headnodePtr)
		{
			if (linklist1.current_point_to->data >=1)
			{
				sum = linklist1.current_point_to->data + cout;
				cout = 0;
			}
			else
			{
				if (cout !=0)
				{
					sum = linklist1.current_point_to->data + 10 + cout;
					cout = -1;
				}
				else
				{
					sum = linklist1.current_point_to->data;
				}
			}
			linklist1.current_point_to = linklist1.current_point_to->llink;
		}
		ans.insert_node(sum, 0);
	}

}

bool BigNum::is_abs_list1_big() 
{
	if (linklist1.size > linklist2.size)
	{
		return true;
	}
	else if (linklist1.size = linklist2.size)
	{
		ListNode* refPtr1 = linklist1.headnodePtr->rlink;
		ListNode* refPtr2 = linklist2.headnodePtr->rlink;

		while (refPtr1 != linklist1.headnodePtr)
		{
			if (refPtr1->data > refPtr2->data)
			{
				return true;
			}
			else if (refPtr1->data < refPtr2->data)
			{
				return false;
			}
			refPtr1 = refPtr1->rlink;
		}
		return true; //equal
	}
	else
	{
		return false;
	}
}



void BigNum::print_ans()				///////////////////////////    0000000001 ???
{
	ans.print_list();
}