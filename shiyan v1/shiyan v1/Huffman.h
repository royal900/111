//Huffman 树节点
#ifndef HUFFMAN_H
#define HUFFMAN_H
struct HTNode
{
	int weight;//权值
	int parent;//父节点
	int lchild;//左孩子
	int rchild;//右孩子

};
typedef HTNode* HuffmanTree;//动态分配数组储存Huffman树
typedef char** HuffmanCode;
int Select(HuffmanTree pHT, int nSize);
int HuffmanCoding(HuffmanCode& pHc, HuffmanTree& pHT);
int HfmTree(HuffmanTree& pHT, int* w, int n);
#endif

