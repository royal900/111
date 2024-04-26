#define _CRT_SECURE_NO_WARNINGS
#include "Huffman.h"
#include<iostream>
using namespace std;
int Select(HuffmanTree pHT, int nSize)
{
	int minValue = 0x7FFFFFFF;//最小值
	int min = 0;//元素符号
	//找到最小权值的元素符号
	for (int i = 1; i <= nSize; i++)
	{
		if (pHT[i].parent == 0 && pHT[i].weight<minValue)
		{
			minValue = pHT[i].weight;
			min = i;
		}
	}
	return min;
}




int HuffmanCoding(HuffmanCode& pHC, HuffmanTree& pHT)
{
	//无栈非递归遍历Huffman树，求Huffman编码
	char cd[256] = { '\0' };//记录访问路径
	int cdlen = 0;//记录访问长度
	for (int i = 1; i < 512; i++)
	{
		pHT[i].weight = 0;//遍历Huffman树作为节点的状态标志
	}
	int p = 511;//根节点
	while (p != 0)
	{
		if (pHT[p].weight == 0)//向左
		{
			pHT[p].weight = 1;
			if (pHT[p].lchild != 0)
			{
				p = pHT[p].lchild;
				cd[cdlen++] = '0';
			}
			else if (pHT[p].rchild == 0)
			{
				pHC[p] = (char*)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy(pHC[p], cd);
			}

		}
		else if (pHT[p].weight == 1)//向右
		{
			pHT[p].weight = 2;
			if (pHT[p].rchild != 0)//右孩子为叶子节点
			{
				p = pHT[p].rchild;
				cd[cdlen++] = '1';
			}
		}
		else
		{
			pHT[p].weight = 0;
			p = pHT[p].parent;
			--cdlen;
		}
	}
	return 1;
}





int HfmTree(HuffmanTree& pHT, int* w, int n)
{
	int m = 2 * n - 1;
	pHT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	if (!pHT)
	{
		cerr << "内存分配失败!" << endl;
		return -1;
	}
	//初始化树
	HuffmanTree p = pHT + 1;
	for (int i = 0; i < m; i++)
	{
		p->weight = (i < n) ? w[i] : 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
		p++;
	}
	for (int i = n + 1; i <= m; i++)
	{
		int s1 = Select(pHT, i - 1);//找出前i-1个中最小的元素
		pHT[s1].parent = i;
		int s2 = Select(pHT, i - 1);
		pHT[s2].parent = i;
		pHT[i].weight = pHT[s1].weight + pHT[s2].weight;
		pHT[i].lchild = s1;
		pHT[i].rchild = s2;
	}
	return 0;
}