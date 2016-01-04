#ifndef HUFFMAN
#define HUFFMAN

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <thread>

using namespace std;

class node
{
private:
	int frequencyLetter;
	char letter;
	node* left;
	node* right;
	bool isLeaf;
	bool used;
public:
	bool getLeaf() { return isLeaf; }
	bool getUsed() { return used; }
	int getFrequencyLetter() { return frequencyLetter; }
	char getLetter() { return letter; }
	node* getLeft() { return left; }
	node* getRight() { return right; }
	void setUsed(bool use) { used = use;}
	node() { frequencyLetter = 0;; left = 0; right = 0; used = false; }
	node(int fr,node* setLeft, node* setRigth) { frequencyLetter = fr;  left = setLeft; right = setRigth; used = false; isLeaf = false; }
	~node() {}
	node(int fr, char st, bool leaf) { frequencyLetter = fr; letter = st; left = 0; right = 0; used = false; isLeaf = leaf; }
};

class huffman
{
private:
	vector <node> treeHuffman;
	vector <node*> tree;
	node* head;
	int numberLetter;
	map <char, int> frequency;
	map <char, string> codes;
	map <string, char> backToChar;
	vector <char> letters;
	friend class node;
public:
	huffman();
	~huffman();
	void revrite();
private:
	void printCodes();
	void createHeap();
	void fixHeap(int i);
	void createCode();
	void getFrequency(ifstream*);
	void revriteFile(ifstream*,int);
	void code(node*, string);
	void makeHuffman();
	int minimum();
	void insert(node);
	void printTree(node*);
	void createTree();
	int converteStringToInt(string);
	char converteBinToHex(int);
	string converteHexToBin(char);
	string createFileName(int,bool);
};


#endif // HUFFMAN

