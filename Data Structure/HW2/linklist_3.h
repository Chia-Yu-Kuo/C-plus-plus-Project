#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class ListNode
{
private:
	friend class LinkList;
	int data;
	ListNode*llink; 
	ListNode*rlink;

};

class LinkList
{
	friend class Listnode;
private:
	string input_size;
	string input_all;
	string input_instruction;
	string input_car_number;

	int size;
	int counter = 0;
	int car_pos;
	int car_number;

	ListNode* headnodePtr = new ListNode ;
	


public:
	void read_input();
	void input_process();

	void buy();
	void drive(int num);

	bool is_empty();
	bool is_full();
	bool find_data(int num);
	ListNode* find_pos_addr(int pos);
	int num_of_total_node();
	void initialize_headnode();
	void insert_node(int data, int pos);	//char[0]  int -48
	void delete_node(int pos);
	void print_list();
	
};




void LinkList::initialize_headnode() 
{
	headnodePtr->llink = headnodePtr;
	headnodePtr->rlink = headnodePtr;
}

void LinkList::read_input()
{
	ifstream  ifile;
	ifile.open("test.txt");
	if (false == ifile.is_open())
	{
		cerr << "open file error" << endl;
	}
	
	getline(ifile, input_size);
	size = (int)input_size[0] - 48;

	cout << "The size of garage is " << size<<endl;
	
	while (getline(ifile, input_all))
	{
		//getline(ifile, input_all);
		input_process();
		
	}
	
	ifile.close();
}



void LinkList::input_process()
{
	stringstream x(input_all);
	getline(x, input_instruction, ' ');




	if (input_instruction == "buy")
	{
		buy();
	}
	else if (input_instruction == "drive")
	{
		getline(x,input_car_number, ' ');
		car_number = (int)input_car_number[0] - 48;
		drive(car_number);
	}
	else
	{
		cout << "no instruction" << endl;
	}
	
	
}

void LinkList::buy() 
{
	if (!is_full())
	{
		insert_node(counter, 0);
	}
	else
	{
		delete_node(size - 1);
		insert_node(counter, 0);
	}
	counter++;
	print_list();
}


void LinkList::drive(int num) 
{
	if (!find_data(num))
	{
		cout << "This car is not in the garage."<<endl;
	}
	else
	{
		delete_node(car_pos);
		insert_node(num,0);
		print_list();
	}
}


bool LinkList::is_empty()
{
	return (headnodePtr->rlink)==headnodePtr ;
}

bool LinkList::is_full() 
{
	return num_of_total_node() == size;
}

bool LinkList::find_data(int num)
{
	if (!is_empty())
	{
		ListNode* refPtr = headnodePtr->rlink;
		for (int i = 0; i < num_of_total_node(); i++)
		{
			if (refPtr->data==num)
			{
				car_pos = i;
				return true;
			}
			refPtr = refPtr->rlink;
		}
		return false;
	}
}

ListNode* LinkList::find_pos_addr(int pos)
{
	if (!is_empty())
	{
		ListNode* refPtr = headnodePtr->rlink;
		for (int i = 0; i < pos; i++)
		{
			refPtr = refPtr->rlink;
		}
		return refPtr;
	}
}

int LinkList::num_of_total_node()
{
	ListNode* refPtr = headnodePtr->rlink;
	int counter = 0;
	if (!is_empty())
	{
		while (refPtr != headnodePtr)
		{
			refPtr = refPtr->rlink;
			counter++;
		}
	}
	return counter;
}

void LinkList::insert_node(int data, int pos)		//char[0]  int -48
{
	ListNode* beinserteed_Ptr= find_pos_addr(pos);

		if (is_empty())
		{
			if (pos==0)
			{
				ListNode* temp = new ListNode;
				temp->data = data;
				temp->llink = headnodePtr;
				temp->rlink = headnodePtr;
				headnodePtr->rlink = temp;
				headnodePtr->llink = temp;
				
				//cout << headnodePtr->rlink << endl << headnodePtr->llink;
			}
			else
			{
				cout << "insert wrong position !!" << endl;
			}
		}
		else
		{
			if (pos<0 || pos > num_of_total_node())
			{
				cout << "insert wrong position !!" << endl;
			}
			else if(pos== num_of_total_node())				//insert at end  ==>or beinserted_Ptr=head_node
			{
				ListNode* temp = new ListNode;
				temp->data = data;
				temp->llink=headnodePtr->llink;
				temp->rlink = headnodePtr;
				headnodePtr->llink->rlink = temp;
				headnodePtr->llink = temp;

			}
			else
			{
				ListNode* temp = new ListNode;
				temp->data = data;
				temp->rlink = beinserteed_Ptr;
				temp->llink = beinserteed_Ptr->llink;
				beinserteed_Ptr->llink->rlink = temp;
				beinserteed_Ptr->llink = temp;
			}
		}
	
}


void LinkList::delete_node(int pos)
{
	ListNode* bedeleted_Ptr = find_pos_addr(pos);
	if (is_empty())
	{
		cout << "lindlist is empty!" << endl;
	}
	else 
	{
		if (pos < 0 || pos >= num_of_total_node())
		{
			cout << "delete wrong position!" << endl;
		}
		else
		{
			bedeleted_Ptr->llink->rlink = bedeleted_Ptr->rlink;
			bedeleted_Ptr->rlink->llink = bedeleted_Ptr->llink;
		}		
	}	
}


void LinkList::print_list()
{
	if (is_empty())
	{
		cout << "list is empty " << endl;
	}
	else
	{
		ListNode* refPtr = headnodePtr->rlink;
		while (refPtr != headnodePtr)
		{
			cout << refPtr->data << " ";			
			refPtr = refPtr->rlink;
		}
		cout << endl;
	}	
}







