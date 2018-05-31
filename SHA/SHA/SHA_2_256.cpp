#include "stdafx.h"
#include "SHA_2_256.h"
#include <iostream>

using namespace std;
unsigned int rotr(unsigned int x, int n)
{
	return (x >> n) | (x << (32 - n));
}
SHA_2_256::SHA_2_256()
{

}


SHA_2_256::~SHA_2_256()
{
}

void  SHA_2_256::set_w(char* w1){
	int i, j = 0, k = 0x080;
	int aaa;
	int len_mess = strlen(w1);
			i = len_mess;
	if (i<63)
		w1[i] = unsigned char(k);


	for (i = 0; i < 64; i += 4)
	{
		w[j] = 0;
		w[j] += (int)w1[i + 3] & 0x000000ff;
		w[j] += (((int)w1[i + 2] & 0x000000ff) << 8);
		w[j] += (((int)w1[i + 1] & 0x000000ff) << 16) + (((int)w1[i] & 0x000000ff) << 24);
		j++;
	}
	if (w[15] == NULL)
		w[15] = len_mess * 8;//считаем количество бит в сообщении
	for (i = 0; i < 16; i++)
		cout << hex << w[i] << " ";
	cout << endl;
	cout << endl;
	cout << endl;


}
void SHA_2_256::addition_w()
{//Сгенерировать дополнительные 48 слов:
	unsigned int s0, s1;
	int i;
	for (int i = 16; i < 64; i++)
	{
		s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3),
			s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}

};
void SHA_2_256::main_part_of_hash(){
	addition_w();
	unsigned int a, b, c, d, e, f, g, h, i, S0, S1,t1, t2, Ma, Ch;
	a = H[0] = 0x6A09E667;
	b = H[1] = 0xBB67AE85;
	c = H[2] = 0x3C6EF372;
	d = H[3] = 0xA54FF53A;
	e = H[4] = 0x510E527F;
	f = H[5] = 0x9B05688C;
	g = H[6] = 0x1F83D9AB;
	h = H[7] = 0x5BE0CD19;
	for (int i = 0; i < 64; i++)
	{
		S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22),
		Ma = (a & b) ^ (a & c) ^ (b & c),
		t2 = S0 + Ma,
		S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25),
		Ch = (e & f) ^ ((~e) & g),
		t1 = h + S1 + Ch + K[i] + w[i];
		
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}
	H[0] = H[0] + a;
	H[1] = H[1] + b;
	H[2] = H[2] + c;
	H[3] = H[3] + d;
	H[4] = H[4] + e;
	H[5] = H[5] + f;
	H[6] = H[6] + g;
	H[7] = H[7] + h;

	for (i = 0; i < 8; i++)
		cout << hex <<H[i] << " ";
	cout << endl;

}
void  SHA_2_256::hash_func(char* M){
	int len = strlen(M);
	int i = 0, j;
	char word[64];
	for (j = 0; j < 64; j++)
		word[j] = NULL;
	while (len - i>64)
	{
		for (j = 0; j < 64; j++)
		{
			word[j] = M[i];
			i++;
		}
		set_w(word);
		main_part_of_hash();
	}
	int n = i;
	if (len - 1 == 0)
		word[1] = NULL;
	else{
		for (j = 0; j < len - i; j++)
		{
			word[j] = M[n];
			n++;
		}
	}

	set_w(word);
	main_part_of_hash();
}