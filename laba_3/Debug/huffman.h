#ifndef HUFFMAN
#define HUFFMAN

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <omp.h>


using namespace std;

class node
{
public:
	int frequencyLetter;
	char letter;
	node* left;
	node* right;
	bool isLeaf;
	bool used;
	node() { frequencyLetter = 0;; left = 0; right = 0; used = false; }
	~node() {}
	node(int fr, char st) { frequencyLetter = fr; letter = st; left = 0; right = 0; used = false; }
};

class huffman
{

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
	huffman(ifstream &);
	~huffman();
	void print();
	void revrite();
private:
	void createHeap();
	void fixHeap(int i);
	void createCode();
	void code(node*, string);
	// void createHuffman();
	//int getMin();
	int minimum();
	void insert(node);
	void printTree(node*);
	void createTree();
};


#endif // HUFFMAN

