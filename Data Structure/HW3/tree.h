#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Stack.h"


using namespace std;

class TreeNode
{
	friend class Tree;
private:
	int data;
	char ch;
	TreeNode*leftChild; 
	TreeNode*rightChild;
	//TreeNode* parent;

public:
	TreeNode();

};

TreeNode :: TreeNode() 
{
	data = NULL;
	ch = '\0';
	leftChild = NULL;
	rightChild = NULL;
}



class Tree
{
	friend class TreeNode;
private:

	TreeNode* root;
	//TreeNode* head;

	Stack stack;
	


public:
	Tree(int data ,char ch ,TreeNode* left_child, TreeNode* right_child);

	int height(TreeNode* root);
	void preorder(TreeNode* currentnode);
	void inorder(TreeNode* currentnode);
	void tree_encoding(TreeNode* currentnode);
	void tree_decoding(TreeNode* currentnode,string decoding);

	int get_data();
	TreeNode* get_root();
};

Tree::Tree(int data, char ch,TreeNode* left_child,TreeNode* right_child)			//constructor???
{
	root = new TreeNode;
	root->data = data;
	root->ch = ch;
	root->leftChild = left_child;
	root->rightChild = right_child;
}

int Tree::height(TreeNode*root)
{
	if (!root)
	{
		return 0;
	}
	else
	{
		int left_height = height(root->leftChild);
		int right_height = height(root->rightChild);
		if (left_height >= right_height)
		{
			return left_height + 1;
		}
		else
		{
			return right_height + 1;
		}
	}
}


int Tree::get_data() 
{
	return root->data;
}
TreeNode* Tree::get_root() 
{

	return root;
}




void Tree::preorder(TreeNode* currentnode)
{	 
	if (currentnode)
	{
		cout << currentnode->data<<" ";
		preorder(currentnode->leftChild);
		preorder(currentnode->rightChild);
	}
	
}	 
	 
void Tree::inorder(TreeNode* currentnode)
{
	if (currentnode)
	{
		inorder(currentnode->leftChild) ;
		cout << currentnode->data << " ";
		inorder(currentnode->rightChild);
	}
	
}


void Tree::tree_encoding(TreeNode* currentnode)
{
	
	if (currentnode)
	{
		stack.push(0);
		tree_encoding(currentnode->leftChild);
		stack.pop();

		if (currentnode->ch != '0')
		{
			cout << currentnode->ch << ": ";
			stack.displayItems();
			cout << endl;
		}

		stack.push(1);
		tree_encoding(currentnode->rightChild);
		stack.pop();

	}

}

void Tree::tree_decoding(TreeNode*currentnode,string decoding) 
{
	cout << "Decoding Result: " << endl;

	for (int i = 0; i < decoding.size(); i++)
	{
		if (decoding[i] == '0')
			currentnode = currentnode->leftChild;
		else
			currentnode = currentnode->rightChild;

		// reached leaf node
		if (currentnode->leftChild == NULL and currentnode->rightChild == NULL)
		{
			cout << currentnode->ch;
			currentnode = root;
		}
	}
	cout << endl;
}


