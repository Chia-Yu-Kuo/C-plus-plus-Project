#include <iostream>
#include <string>
#include"bignum_2.h"

using namespace std;




int main() 
{
	BigNum bignum;

	bignum.set_list();
	bignum.read_input();


	
	bignum.print_ans();


	system("pause");
	return 0;
}