#define _CRT_SECURE_NO_WARNINGS
#define SIZE 256
#include "Huffman.h"
#include"Compress.h"
#include<iostream>
#include"test.h"
using namespace std;
char Str2byte(const char* pBinStr)
{
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;
		if (pBinStr[i] == '1')
		{
			b = b | 0x01;
		}
	}
	return b;
}
int Compress(const char* pFilename)
{
	int weight[256] = { 0 };
	//以二进制打开文件
	FILE* in = fopen(pFilename, "rb");
		if (in == NULL)
		{
			cout << "Failed to open the file" << endl;
			exit(0);
		}
		cout << "成功打开文件" << pFilename << endl;
		int ch;
		while ((ch = getc(in)) != EOF)
		{
			weight[ch]++;
		}
		fclose(in);
		HuffmanTree hfmt;
		HfmTree(hfmt, weight, SIZE);
		//TestHufTree(hfmt);
		//TestHufTreeN(511, hfmt);
		cout << "成功生成哈夫曼树" << endl;
		HuffmanCode hfmc = (HuffmanCode)malloc((SIZE + 1) * sizeof(char*));
		HuffmanCoding(hfmc, hfmt);
		//TestHufCode(511, hfmt, hfmc);
		cout << "成功完成哈夫曼编码" << endl;
		//计算编码缓冲区
		int nSize = 0;
		for (int i = 0; i < 256; i++)
		{
			nSize += weight[i] * strlen(hfmc[i+1]);
		}
		nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
		char* pBuffer = NULL;
		pBuffer = (char*)malloc(nSize * sizeof(char));
		memset(pBuffer, 0, (nSize) * sizeof(char));
		Encode(pFilename, hfmc, pBuffer, nSize);
		if (!pBuffer)
		{
			cout << "!pBuffer = " << !pBuffer << endl;
			return -1;
		}
		cout << "\n压缩完毕" << endl;
		HEAD sHead;
		InitHead(pFilename, sHead);
		cout << "原文件" << pFilename << "大小为:" << sHead.length << "Byte" << endl;
		int len_after = WriteFile(pFilename, sHead, pBuffer, nSize);
		cout << "大小为:" << len_after << "Byte \n头文件sHead大小为:" << sizeof(sHead) << "Byte" << endl;
		cout << "压缩比率：" << (double)len_after * 100/ sHead.length << "%" << endl;
		free(hfmt);
		free(hfmc);
		free(pBuffer);
		return 1;
}



int Encode(const char* pFilename, const HuffmanCode pHC, char* pBuffer, const int  nSize)
{
	FILE* in = fopen(pFilename, "rb");
	if (in == NULL)
	{
		cout << "Failed to open the file!" << endl;
		exit(0);
	}
	pBuffer = (char*)malloc(nSize * sizeof(char));
	if (!pBuffer)
	{
		cerr << "开辟缓冲区失败" << endl;
		return -1;
	}
	cout << "loading";
	int sign = 0;
	char cd[SIZE] = { 0 };
	int pos = 0;
	int ch;
	while ((ch = getc(in)) != EOF)
	{
		//if (sign % 1000 == 1)printf(".");
		sign++;
		strcat(cd, pHC[ch+1]);


		while (strlen(cd) >= 8)
		{
			pBuffer[pos++] = Str2byte(cd);
			for (int i = 0; i < SIZE - 8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}

	}
	if (strlen(cd) > 0)
	{
		pBuffer[pos++] = Str2byte(cd);
	}
	fclose(in);
	return 1;
}
int InitHead(const char* pFilename, HEAD& sHead)
{
	//初始化文件夹
	strcpy(sHead.type, "HUF");
	sHead.length = 0;//原文件长度
	for (int i=0; i < SIZE; i++)
	{
		sHead.weight[i] = 0;
	}
	FILE* in = fopen(pFilename, "rb");
	int ch;
	while ((ch = fgetc(in)) != EOF)
	{
		sHead.weight[ch]++;
		sHead.length++;
	}
	fclose(in);
	in = NULL;
	return 1;
}
int WriteFile(const char* pFilename, const HEAD sHead, const char* pBuffer, const int nSize)
{
	char filename[256] = { 0 };
	strcpy(filename, pFilename);
	strcat(filename, ".huf");
	FILE* out = fopen(filename, "wb");
	fwrite(&sHead, sizeof(char), 1, out);
	fwrite(pBuffer, sizeof(char), nSize, out);
	fclose(out);
	out = NULL;
	cout << "生成压缩文件:" << filename << endl;
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nSize;
	return len;
}