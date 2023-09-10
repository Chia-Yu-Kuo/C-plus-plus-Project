#include <iostream>
#include <string>


using namespace std;

class ListNode
{
private:
	friend class LinkList;
	friend class BigNum;
	int data;
	ListNode*llink; 
	ListNode*rlink;

};

class LinkList
{
	friend class Listnode;
	friend class BigNum;

	int size ;
	int sign ;    //		=0+ / =1 -
private:

	ListNode* headnodePtr = new ListNode ;
	

public:
	LinkList();
	ListNode* current_point_to ;
	int getsize();


	bool is_empty();
	ListNode* find_pos_addr(int pos);
	int num_of_total_node();
	void initialize_headnode();
	void insert_node(int data, int pos);	//char[0]  int -48
	void delete_node(int pos);
	void print_list();
	
};

LinkList::LinkList() 
{
	size = 0;
	sign = 0;
}

int LinkList:: getsize() 
{
	return size;
}

void LinkList::initialize_headnode() 
{
	headnodePtr->llink = headnodePtr;
	headnodePtr->rlink = headnodePtr;
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
		if (sign == 1)
		{
			cout << "-";
		}

		//trivasal
		ListNode* refPtr = headnodePtr->rlink;
		while (refPtr != headnodePtr)
		{
			if (refPtr->data==0)
			{
				refPtr = refPtr->rlink;
			}
			else
			{
				break;
			}
		}

		//print
		
		while (refPtr != headnodePtr)
		{
			cout << refPtr->data;
			refPtr = refPtr->rlink;		
		}
		cout << endl;
	}	
}







