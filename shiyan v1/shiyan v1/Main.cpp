#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdlib.h>
#include "Compress.h"
using namespace std;
int main()
{
	cout << "==========Huffman�ļ�ѹ��=========" << endl;
	cout << "�������ļ���:";
	char filename[256];
	cin >> filename;
	Compress(filename);

	return 0;

	
}