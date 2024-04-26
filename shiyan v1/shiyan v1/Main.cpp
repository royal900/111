#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdlib.h>
#include "Compress.h"
using namespace std;
int main()
{
	cout << "==========Huffman文件压缩=========" << endl;
	cout << "请输入文件名:";
	char filename[256];
	cin >> filename;
	Compress(filename);

	return 0;

	
}