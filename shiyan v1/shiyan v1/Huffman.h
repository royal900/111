//Huffman ���ڵ�
#ifndef HUFFMAN_H
#define HUFFMAN_H
struct HTNode
{
	int weight;//Ȩֵ
	int parent;//���ڵ�
	int lchild;//����
	int rchild;//�Һ���

};
typedef HTNode* HuffmanTree;//��̬�������鴢��Huffman��
typedef char** HuffmanCode;
int Select(HuffmanTree pHT, int nSize);
int HuffmanCoding(HuffmanCode& pHc, HuffmanTree& pHT);
int HfmTree(HuffmanTree& pHT, int* w, int n);
#endif

