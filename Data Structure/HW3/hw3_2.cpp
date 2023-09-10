#include <iostream>
#include "huffman.h"

using namespace std;

int main()
{
	Huffman huffman;

	huffman.read_input();
	huffman.print_input_info();
	huffman.build_min_heap();
	huffman.build_huffman_tree();

	system("pause");
	return 0;
}








