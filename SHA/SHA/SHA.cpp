// SHA.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "SHA_2_256.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	char text[500];
	cout << "������� �����: " << endl;
	cin.getline(text, 500);
SHA_2_256 object;
object.hash_func(text);

	system("pause");
	return 0;
}

