#include "Huffman.h"
int Compress(const char* pFilename);
char Str2byte(const char* pBinStr);
int Encode(const char* pFilename, const HuffmanCode pHC, char* pBuffer, const int nSize);
struct HEAD
{
	char type[4];
	int length;
	int weight[256];
};
int WriteFile(const char* pFilename, const HEAD sHead, const char* pBuffer, const int nSzie);
int InitHead(const char* pFilename, HEAD& sHead);
