#pragma once
#include "my_Big_Num.h"
class SHA_1
{
unsigned int h[5];
unsigned int w[80];
	int len;// длина сообщения
	
	void set_w(char*);
	void addition_w();
	void main_part_of_hash();
public:
	SHA_1();
	my_Big_Num hash_func(char* M);
	~SHA_1();
};

