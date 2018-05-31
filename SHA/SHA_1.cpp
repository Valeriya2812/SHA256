#include "stdafx.h"
#include "SHA_1.h"
#include <iostream>

using namespace std;


SHA_1::SHA_1()
{
}


SHA_1::~SHA_1()
{
}

my_Big_Num SHA_1::hash_func(char* M)
{
	unsigned char p[1000], p1[1000];
	my_Big_Num result;
	int i=1, j=0, jj=0, count=0, ii=0;
	char* mess_64 = new char;
 len=strlen(M);
 for (ii = 0; ii < 20; ii++)
	 p[ii] = 0;
	if (len <= 64)
	{
		set_w(M);
		main_part_of_hash();
	
		for (ii = 0; ii < 5; ii++)
		{
			p[jj] =h[ii]>>24;
			p[jj + 1] = h[ii]>>16;
			p[jj + 2] = h[ii] >> 8;
			p[jj + 3] = h[ii];
			jj += 4;
		}
		p[20] = 0;
		result.char_to_my_Big_Num(p);
		
	}
	else
	{
		while (i < len)
		{
			mess_64[j] = M[i - 1];
			if (i % 64 == 0)
			{
				set_w(mess_64);
				j = -1;
				main_part_of_hash();
				for (ii = 0; ii < 5; ii++)
				{
					p[jj] = h[ii] >> 24;
					p[jj + 1] = h[ii] >> 16;
					p[jj + 2] = h[ii] >> 8;
					p[jj + 3] = h[ii];
					jj += 4;
				}
			}
			j++;
			i++;
		}
		if (i < 64)
		{

			set_w(M);
			main_part_of_hash();
			for (ii = 0; ii < 5; ii++)
			{
				p[jj] = h[ii] >> 24;
				p[jj + 1] = h[ii] >> 16;
				p[jj + 2] = h[ii] >> 8;
				p[jj + 3] = h[ii];
				jj += 4;
			}
			

		}
	
	}
	return result;
}


void  SHA_1::set_w(char* mess){
	int i, j=0;
	int len_mess = strlen(mess);
	unsigned char w1[64];

	for (i = 0; i <64; i++)
		w1[i] = NULL;
	for (i = 0; i < len_mess; i++)
		w1[i] = mess[i];
	
	i = len_mess;
	w1[i] = 0x80;
	w[15] = 0x18;

	for (i = 0; i < 64; i += 4)
	{
		w[j] = 0;
		w[j]+= w1[i + 3];
		w[j] += (w1[i + 2] << 8);
		w[j]+=(w1[i + 1] << 16) + (w1[i] << 24);
		j++;
	}
	
	w[15] = 0x18;
	for (i = 0; i < 16; i++)
		cout << hex << w[i] << " ";
	cout << endl;

}


void  SHA_1::addition_w()
{
	int i;
	for (i = 16; i < 80; i++)
		w[i] = ((w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]) << 1) | ((w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]) >> 31);
};



void SHA_1::main_part_of_hash(){
	addition_w();
	unsigned int a, b, c, d, e, i, f, k, temp;
	a=h[0] = 0x67452301;
	b=h[1] = 0xEFCDAB89;
	c=h[2] = 0x98BADCFE;
	d=h[3] = 0x10325476;
	e=h[4] = 0xC3D2E1F0;


	for (i = 0; i < 80; i++)
	{
		if ((i >= 0) && (i <= 19))
		{
			f = (b&c) | ((~b)&d);
			k = 0x5A827999;
		}
		else if ((i >= 20) && (i <= 39))
		{
			f = b^c^d;
			k = 0x6ED9EBA1;
		}
		else if ((i >= 40) && (i <= 59))
		{
			f = (b&c) | (b&d) | (c&d);
			k = 0x8F1BBCDC;
		}
		else if ((i >= 60) && (i <= 79))
		{
			f = b^c^d;
			k = 0xCA62C1D6;
		}

		temp = ((a << 5) | (a >> 27)) + f + e + k + w[i];
		e = d;
		d = c;
		c = (b << 30) | (b >> 2);
		b = a;
		a = temp;
	}
	h[0] = h[0] + a;
	h[1] = h[1] + b;
	h[2] = h[2] + c;
	h[3] = h[3] + d;
	h[4] = h[4] + e;

	for (i = 0; i < 5; i++)
		cout <<hex<< h[i] << " ";
	cout << endl;

}