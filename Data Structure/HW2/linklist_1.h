#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class ListNode
{
private:
	friend class LinkList;
	char data;
	ListNode*llink; 
	ListNode*rlink;

};

class LinkList
{
	friend class Listnode;
private:
	string input_all;
	string input_instruction;
	string input_search_word;
	string input_char; //insert delete Numof 共用
	string input_pos; //insert delete共用


	ListNode* headnodePtr = new ListNode ;
	


public:
	LinkList();
	void read_input();
	void input_process();

	bool is_empty();
	ListNode* find_pos_addr(int pos);
	int num_of_total_node();
	
	void initialize_headnode();
	void insert_node(char data, int pos);	//char[0]  int -48
	void delete_node(int pos);
	void delete_data(char data);
	void search_word(string word);
	void  num_of_occur(char data);
	void max_num_of_occur();
	void print_list();
	
};

LinkList::LinkList()			//constructor???
{

}

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




	if (input_instruction == "InsertNode")
	{
		getline(x, input_char, ' ');
		getline(x, input_pos, ' ');

		
		
		insert_node(input_char[0], ((int)input_pos[0] - 48));	
		
		//print_list();
		//cout << endl;
	}
	else if (input_instruction == "DeleteNode")
	{
		getline(x, input_pos, ' ');

		delete_node(((int)input_pos[0] - 48));
		//print_list();
		//cout << endl;
	}
	else if (input_instruction == "DeleteData")
	{
		getline(x, input_char, ' ');

		delete_data(input_char[0]);
		//print_list();
		//cout << endl;
	}
	else if (input_instruction == "SearchWord")
	{
		getline(x, input_search_word, ' ');
		
		search_word(input_search_word);
		//print_list();
		//cout << endl;
	}
	else if (input_instruction == "NumOfOccur")
	{
		getline(x, input_char, ' ');

		num_of_occur(input_char[0]);
		//print_list();
	}
	else if (input_instruction == "MaxNumOfOccur")
	{
		max_num_of_occur();

		//print_list();
	}
	else if (input_instruction == "PrintList")
	{
		print_list();
	}
	
	else
	{
		cout << "no instruction" << endl;
	}
	
	
}

bool LinkList::is_empty()
{
	return (headnodePtr->rlink)==headnodePtr ;
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

void LinkList::insert_node(char data, int pos)		//char[0]  int -48
{
	ListNode* beinserteed_Ptr= find_pos_addr(pos);
	if (data<32 || data>126)
	{
		cout << "insert wrong data !!" << endl;
	}
	else
	{
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

void LinkList::delete_data(char data)
{
	if (is_empty())
	{
		cout << "lindlist is empty!" << endl;
	}
	else
	{
		if (data < 32 || data>126)
		{
			cout << "delete wrong data !!" << endl;
		}
		else
		{
			ListNode* refPtr = headnodePtr->rlink;
			int pos = 0;
			while (refPtr != headnodePtr)
			{
				if (refPtr->data==data)		//pos不能++(因被刪了)
				{
					refPtr = refPtr->rlink;
					delete_node(pos);
				}
				else
				{
					refPtr = refPtr->rlink;
					pos++;
				}
				
			}
		}
	}

}


void LinkList::search_word(string word)
{
	int begin_pos = 0;
	for (int i = 0; i < word.length(); i++)			//word for
	{
		ListNode* refPtr = find_pos_addr(begin_pos);
		while (refPtr != headnodePtr)
		{
			if (refPtr->data == word[i])
			{
				//cout << begin_pos<<" ";
				break;
			}
			refPtr = refPtr->rlink;
			begin_pos++;
		}
	}

	if (begin_pos< num_of_total_node())
	{
		cout << "Found!!" << endl;
	}
	else
	{
		cout << "Not Found!!" << endl;
	}
	
}


void  LinkList::num_of_occur(char data)
{
	ListNode* refPtr = headnodePtr->rlink;
	int counter = 0;
	while (refPtr != headnodePtr)
	{
		if (refPtr->data == data)
		{
			counter++;
		}
		refPtr = refPtr->rlink;
	}
	
	cout << counter << endl;
}

void LinkList::max_num_of_occur()
{
	int counter[127] = {0};
	int max=0;
	ListNode* refPtr = headnodePtr->rlink;

	while (refPtr != headnodePtr)
	{
		counter[(int)refPtr->data]++;
		refPtr = refPtr->rlink;
	}
	for (int i = 32; i < 127; i++)
	{
		if (counter[i]>max) 
		{
			max = counter[i];
		}
	}
	for (int i = 32; i < 127; i++)
	{
		if (counter[i]==max)
		{
			cout << (char)i << " ";
		}
	}
	cout << endl;
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







