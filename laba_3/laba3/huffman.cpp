#pragma once
#include "huffman.h"

using namespace std;


//counts the frequency of each symbol in files
void huffman::getFrequency(ifstream* input)
{
	char letter;
	while (input->get(letter))
	{
		if (frequency[letter] > 0) frequency[letter]++;
		else
		{
			numberLetter++;
			letters.push_back(letter);
			frequency[letter] = 1;
		}
	}
	node* temp;
	for (int i = 0; i < numberLetter; i++)
	{
		temp = new node(frequency[letters[i]], letters[i],true);
		tree.push_back(temp);
	}
}

//creates threads for different files
//call function to know the frequency of each symbol
//frequency is own for these files
void huffman::makeHuffman()
{
	ifstream input1("input1.txt");
	ifstream input2("input2.txt");
	ifstream input3("input3.txt");
	ifstream input4("input4.txt");
	thread firstThread(&huffman::getFrequency, this, &input1);
	thread secondThread(&huffman::getFrequency, this, &input2);
	thread thirdhread(&huffman::getFrequency, this, &input3);
	thread fourthThread(&huffman::getFrequency, this, &input4);
	firstThread.join();
	secondThread.join();
	thirdhread.join();
	fourthThread.join();
}

//to create huffman code we have to get frequency of each symbol
//create a tree for coding each symbol
//and find the unic code of every sybmol in tree
huffman::huffman()
{
	numberLetter = 0;
	makeHuffman();
	createTree();
	head = tree[tree.size() - 1];
	createCode();
}

//this function call function to make codes to all nodes
// and this creating begins of calling function for head of the tree
void huffman::createCode()
{
	code(head, "");
}


//create codo for every node
// if we go to the left son it is '0', rigth - '1'
//tree doesn't contain cycles so we can reach the node only by one way
//so this way is our unic code for nodes and this code will replace sybmol in revrited file
//if this node is the leaf
void huffman::code(node* temp, string nodeName)
{
	if (temp)
	{
		if (temp->getLeaf())
		{
			codes[temp->getLetter()] = nodeName;
			backToChar[nodeName] = temp->getLetter();
		}
		else
		{
			string codeName = nodeName;
			nodeName = nodeName + "0";
			code(temp->getLeft(), nodeName);
			nodeName = codeName + "1";
			code(temp->getRight(), nodeName);
		}
	}
}

//find the node in tree which contains the lowest number and wasn't used before
int huffman::minimum()
{
	int minim = 0;
	int pos = -1;
	for (unsigned int i = 0; i < tree.size(); i++)
	{
		if (pos == -1 && (!tree[i]->getUsed()))
		{
			pos = i;
			minim = tree[i]->getFrequencyLetter();
		}
		if ((tree[i]->getFrequencyLetter() < minim) && (!tree[i]->getUsed()))
		{
			pos = i;
			minim = tree[i]->getFrequencyLetter();
		}
	}
	tree[pos]->setUsed(true);
	return pos;
}

//create binary heap by adding new nodes 
//which is the merge of the two lowest unused vertexes
void huffman::createTree()
{
	auto size = tree.size();
	for (decltype(size) i = 0; i < size - 1; i++)
	{
		int minFirst = minimum();
		int minSecond = minimum();
		int newFrequency = tree[minFirst]->getFrequencyLetter() + tree[minSecond]->getFrequencyLetter();
		node* merge = new node(newFrequency, tree[minFirst], tree[minSecond]);
		tree.push_back(merge);
	}
}

//add new node to the huffman's tree
void huffman::insert(node nodeNew)
{
	auto i = treeHuffman.size();
	while (i > 0 && treeHuffman[i].getFrequencyLetter() > nodeNew.getFrequencyLetter())
	{
		treeHuffman[i] = treeHuffman[(i + 1) / 2];
		i = (i + 1) / 2;
	}
	treeHuffman[i] = nodeNew;
}

//create a heap of huffman's tree
void huffman::createHeap()
{
	for (auto i = (treeHuffman.size() + 1) / 2; i > 0; i--)
	{
		fixHeap((int)i);
	}
}


// fix problem with main characteristic of binary heap
//if we have not any problem with left and right tree of the vertex
void huffman::fixHeap(int i)
{
	int left = 2 * i;
	int right = (2 * i) + 1;
	int max = -1;

	if (left <= numberLetter && treeHuffman[left].getFrequencyLetter() < treeHuffman[i].getFrequencyLetter())
		max = left;
	else max = i;
	if (right <= numberLetter && treeHuffman[right].getFrequencyLetter()< treeHuffman[max].getFrequencyLetter())
		max = right;

	if (max != i)
	{
		node temp = treeHuffman[i];
		treeHuffman[i] = treeHuffman[max];
		treeHuffman[max] = temp;
		fixHeap(max);
	}
}

//crear all veectors
huffman::~huffman()
{
	frequency.clear();
	treeHuffman.clear();
	letters.clear();
}

//prints sybmbol and its code
void huffman::printCodes()
{
	for (int i = 0; i < numberLetter; i++)
	{
		cout << letters[i] << "  " << codes[letters[i]] << " \n";
	}
	cout << "\n";
}


//create few threads to write to many files in same time
//open files to write, create threades to call function revrite these files
// function ends when all threads ends their functions
void huffman::revrite()
{
	ifstream input1("input1.txt");
	ifstream input2("input2.txt");
	ifstream input3("input3.txt");
	ifstream input4("input4.txt");
	thread firstThread(&huffman::revriteFile, this, &input1,1);
	thread secondThread(&huffman::revriteFile, this, &input2,2);
	thread thirdhread(&huffman::revriteFile, this, &input3,3);
	thread fourthThread(&huffman::revriteFile, this, &input4,4);
	firstThread.join();
	secondThread.join();
	thirdhread.join();
	fourthThread.join();
}


// converte number contained in sting to the same number but in int
int huffman::converteStringToInt(string strToConverte)
{
	auto size = strToConverte.size();
	int base = 1;
	int convertedInt = 0;
	while (size > 0)
	{
		convertedInt += (strToConverte[size - 1] - '0') * base;
		base *= 10;
		size--;
	}
	strToConverte.clear();
	return convertedInt;
}


// converte binary number into hexidemical number
char huffman::converteBinToHex(int binNumber)
{
	int tenthNumber = 0;
	int base = 1;

	while (binNumber > 0)
	{
		int ost = binNumber % 10;
		tenthNumber += base * ost;
		base *= 2;
		binNumber /= 10;
	}

	char hexNumber;
	if (tenthNumber < 10) hexNumber = char(tenthNumber + int('0'));
	else hexNumber = char(tenthNumber + int('A') - 10);
	return hexNumber;
}

//converte hexidemical number into binary
string huffman::converteHexToBin(char letter)
{
	int temp;
	if (letter - '0' >= 0 && letter - '0' <= 9) temp = letter - '0';
	else temp = letter - 'A' + 10;
	string newChar = "";
	while (temp > 0)
	{
		int ostInt = temp % 2;
		temp /= 2;
		char ostChar = ostInt + '0';
		newChar = ostChar  + newChar;
	}
	while (newChar.size() < 4) newChar = '0' + newChar;
	return newChar;
}


//create name of file to outup code if this file for next input
// or output file with words after decoding files of codes
string huffman::createFileName(int numberFile,bool input)
{
	string fileName = "";
	if (!input) fileName ="output";
	else fileName = "inputNext";
	char numberOfFile = char(numberFile + int('0'));
	fileName += numberOfFile;
	fileName += ".txt";
	return fileName;
}



//creates file that equal to input but contains codes instead of sybmols
//then open created file and revrite it to original view(have sybmbols)
void huffman::revriteFile(ifstream* input,int numberFile)
{
	char letter;
	string fileName = createFileName(numberFile, false);
	ofstream output(fileName, std::ios::binary);
	numberLetter = 0;
	int numberLetters = 4;
	string wordCode = "";
	while (input->get(letter))
	{
		wordCode += codes[letter];
		while (wordCode.size() >= numberLetters)
		{
			string temp = "";
			for (int i = 0; i < numberLetters; i++) temp += wordCode[i];
			string newWordCode = "";
			for (unsigned int i = numberLetters; i < wordCode.size(); i++) newWordCode += wordCode[i];
			wordCode = newWordCode;
			int numberToWrite = converteStringToInt(temp);
			char hexNumber = converteBinToHex(numberToWrite);
			char* strToWrite = &hexNumber;
			output.write((char*)(strToWrite), sizeof(hexNumber));
		}
	}
	int haveMore = 0;
	if (wordCode.size() > 0)
	{
		while (wordCode.size() < numberLetters)
		{
			wordCode = '0' + wordCode;
			haveMore++;
		}
		int numberToWrite = converteStringToInt(wordCode);
		char hexNumber = converteBinToHex(numberToWrite);
		char* strToWrite = &hexNumber;
		output.write((char*)(strToWrite), sizeof(hexNumber));
	}
	output.close();

	ifstream inputToRewrite(fileName);
	string fileNameForInputNext = createFileName(numberFile,true);
	ofstream outputRewrited(fileNameForInputNext);
	string strToWrite = "";
	while (inputToRewrite.get(letter))
	{
		strToWrite += converteHexToBin(letter);
		string curr = "";
		unsigned int size = strToWrite.size() - haveMore;
		for (unsigned int i = 0; i < size; i++)
		{
			curr += strToWrite[i];
			if (backToChar.find(curr) != backToChar.end())
			{
				outputRewrited << backToChar[curr];
				curr = "";
			}
		}
		for (int i = size; i < size + haveMore; i++) curr += strToWrite[i];
		strToWrite = curr;
	}
	inputToRewrite.close();
	outputRewrited.close();
}

