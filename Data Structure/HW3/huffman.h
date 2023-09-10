
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include"MinHeap.h"

using namespace std;


class Huffman 
{

private:
	string encoding;
	string decoding;

	int frequence[26] = {0};

	MinHeap minheap;
	Tree* huffman_tree;

public:
	void read_input();
	void print_input_info();
	int	 get_heap_size();
	void build_min_heap();
	void build_huffman_tree();
	
};

void Huffman::read_input()
{
	ifstream  ifile;
	ifile.open("test.txt");
	if (false == ifile.is_open())
	{
		cerr << "open file error" << endl;
	}

	getline(ifile, encoding);
	getline(ifile, decoding);

	ifile.close();

	//frequence
	for (int i = 0; i < encoding.length(); i++)
	{
		frequence[(int)(encoding[i] - 'a')]++;
	}
}
void Huffman::print_input_info() 
{
	cout << "Symbol: ";
	for (int i = 0; i < 26; i++)
	{
		if (frequence[i])
		{
			cout << (char)(i + 'a')<<" ";
		}

	}
	cout << endl;

	cout << "Frequency: ";
	for (int i = 0; i < 26; i++)
	{
		if (frequence[i])
		{
			cout << frequence[i] << " ";
		}

	}
	cout << endl;

}

int Huffman::get_heap_size() 
{
	int size = 0;
	for (int i = 0; i < 26; i++)
	{
		if (frequence[i])
		{
			size++;
		}
	}
	return size;
}

void Huffman::build_min_heap() 
{

	minheap.set_capacity(get_heap_size());

	for (int i = 0; i < 26; i++)
	{
		if (frequence[i])
		{
			Tree* temp = new Tree(frequence[i], (char)(i + 'a'), NULL, NULL);
			minheap.push(temp);
		}
	}
}

void Huffman::build_huffman_tree() 
{
	for (int i = 0; i < get_heap_size()-1; i++)
	{
		Tree* first = minheap.pop();
		Tree* second = minheap.pop();
		Tree* third = new Tree((first->get_data() + second->get_data()),'0', first->get_root(), second->get_root());
		minheap.push(third);
	}

	huffman_tree = minheap.pop();

	cout << "Huffman Tree: " << endl;
	cout << "Preorfer: ";
	huffman_tree->preorder(huffman_tree->get_root());
	cout << endl;
	cout << "Inorfer: ";
	huffman_tree->inorder(huffman_tree->get_root());
	cout << endl;
	cout << "Leval: "<< huffman_tree->height(huffman_tree->get_root());
	cout << endl;

	cout << "Huffman Code: "<< endl;
	huffman_tree->tree_encoding(huffman_tree->get_root());
	huffman_tree->tree_decoding(huffman_tree->get_root(),decoding);
}


