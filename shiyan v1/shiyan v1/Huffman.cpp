#define _CRT_SECURE_NO_WARNINGS
#include "Huffman.h"
#include<iostream>
using namespace std;
int Select(HuffmanTree pHT, int nSize)
{
	int minValue = 0x7FFFFFFF;//��Сֵ
	int min = 0;//Ԫ�ط���
	//�ҵ���СȨֵ��Ԫ�ط���
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
	//��ջ�ǵݹ����Huffman������Huffman����
	char cd[256] = { '\0' };//��¼����·��
	int cdlen = 0;//��¼���ʳ���
	for (int i = 1; i < 512; i++)
	{
		pHT[i].weight = 0;//����Huffman����Ϊ�ڵ��״̬��־
	}
	int p = 511;//���ڵ�
	while (p != 0)
	{
		if (pHT[p].weight == 0)//����
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
		else if (pHT[p].weight == 1)//����
		{
			pHT[p].weight = 2;
			if (pHT[p].rchild != 0)//�Һ���ΪҶ�ӽڵ�
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
		cerr << "�ڴ����ʧ��!" << endl;
		return -1;
	}
	//��ʼ����
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
		int s1 = Select(pHT, i - 1);//�ҳ�ǰi-1������С��Ԫ��
		pHT[s1].parent = i;
		int s2 = Select(pHT, i - 1);
		pHT[s2].parent = i;
		pHT[i].weight = pHT[s1].weight + pHT[s2].weight;
		pHT[i].lchild = s1;
		pHT[i].rchild = s2;
	}
	return 0;
}