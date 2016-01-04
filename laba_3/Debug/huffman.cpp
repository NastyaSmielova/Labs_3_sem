#include "huffman.h"

huffman::huffman(ifstream &input)
{
	char ch;
	numberLetter = 0;
	while (input.get(ch))
	{
		//cout << ch << " ";
		if (frequency[ch] > 0) frequency[ch]++;
		else
		{
			numberLetter++;
			letters.push_back(ch);
			frequency[ch] = 1;
		}
	}

	node* temp;
	//treeHuffman.push_back(temp);
	for (int i = 0; i < numberLetter; i++)
	{
		temp = new node();
		temp->frequencyLetter = frequency[letters[i]];
		temp->letter = letters[i];
		temp->used = false;
		temp->isLeaf = true;
		tree.push_back(temp);
	}

	//.. for (unsigned int i = 0; i < tree.size() - 1; i++)
	//   tree[i]->next = tree[i+1];

	// createHeap();

	createTree();
	//int t = minimum();
	head = tree[tree.size() - 1];//= createHuffman();
	cout << head->frequencyLetter << " ";
	createCode();
}

void huffman::createCode()
{
	code(head, "");
}

void huffman::code(node* temp, string n)
{
	cout << temp->frequencyLetter << " " << n << "&& ";

	if (temp)
	{
		// cout << temp->frequencyLetter << " " << n << " ";

		if (temp->isLeaf)
		{
			cout << temp->letter << "*\n";
			codes[temp->letter] = n;
			backToChar[n] = temp->letter;
		}
		else
		{
			cout << "@";
			string q = n;
			n = n + "0";
			code(temp->left, n);
			n = q + "1";
			code(temp->right, n);
		}
	}
}


int huffman::minimum()
{
	int minim = 0;
	int pos = -1;
	for (unsigned int i = 0; i < tree.size(); i++)
	{
		if (pos == -1 && (!tree[i]->used))
		{
			pos = i;
			minim = tree[i]->frequencyLetter;
		}
		if ((tree[i]->frequencyLetter  < minim) && (!tree[i]->used))
		{
			pos = i;
			minim = tree[i]->frequencyLetter;
		}
	}
	//if (pos == -1) cout << "%%%%%%%%%%";
	tree[pos]->used = true;
	// cout <<tree.size() << " " << pos << " \n";
	return pos;
}

void huffman::createTree()
{
	int n = tree.size();
	for (int i = 0; i < n - 1; i++)
	{
		int x = minimum();
		int y = minimum();
		node* z = new node();
		// cout << x <<" " << y  <<"\n";
		z->frequencyLetter = tree[x]->frequencyLetter + tree[y]->frequencyLetter;
		z->used = false;
		z->isLeaf = false;
		z->left = tree[x];
		z->right = tree[y];
		tree.push_back(z);
	}
}


/*node huffman::getMin()
{
node temp;
if (treeHuffman.size() > 1)
{
temp = treeHuffman[1];
treeHuffman[1] = treeHuffman[treeHuffman.size() - 1];
treeHuffman.pop_back();
fixHeap(1);
return temp;
}
else return temp;
}
*/
void huffman::insert(node nodeNew)
{
	int i = treeHuffman.size();
	while (i > 0 && treeHuffman[i].frequencyLetter > nodeNew.frequencyLetter)
	{
		treeHuffman[i] = treeHuffman[(i + 1) / 2];
		i = (i + 1) / 2;
	}
	treeHuffman[i] = nodeNew;
}

/*node* huffman::createHuffman()
{
node temp;
node* x;
node* y;
for (int i = 0; i < numberLetter; i++)
{
node* z = new node;
temp = getMin();
x = new node;
x->frequencyLetter = temp.frequencyLetter;
temp = getMin();
y = new node;
y->frequencyLetter = temp.frequencyLetter;
z->left = x;
z->right = y;
z->frequencyLetter = x->frequencyLetter + y->frequencyLetter;
temp.frequencyLetter = z->frequencyLetter;
insert(temp);

}
//return
{
node * q = new node ;
temp = getMin();
q->frequencyLetter = temp.frequencyLetter;
return q;
}
}
*/
void huffman::createHeap()
{
	for (int i = (treeHuffman.size() + 1) / 2; i > 0; i--)
	{
		fixHeap(i);
	}
}

void huffman::fixHeap(int i)
{
	//if (i == 0) cout << "!!!!!!11\n";
	int left = 2 * i;
	int right = (2 * i) + 1;
	int max = -1;

	if (left <= numberLetter && treeHuffman[left].frequencyLetter < treeHuffman[i].frequencyLetter)
	{
		max = left;
	}
	else max = i;
	if (right <= numberLetter && treeHuffman[right].frequencyLetter < treeHuffman[max].frequencyLetter)
	{
		max = right;
	}
	//cout << treeHuffman[i].frequencyLetter << "  " << treeHuffman[max].frequencyLetter << " ; ";
	if (max != i)
	{
		node temp = treeHuffman[i];
		treeHuffman[i] = treeHuffman[max];
		treeHuffman[max] = temp;
		fixHeap(max);
	}
}


huffman::~huffman()
{
	frequency.clear();
	treeHuffman.clear();
	letters.clear();
}

void huffman::printTree(node* temp)
{
	if (temp)
	{
		printTree(temp->left);//cout << 0;
		cout << temp->letter << ";";
		printTree(temp->right);//cout << 1;
	}
}


void huffman::print()
{
	cout << numberLetter << " <- size\n";
	for (int i = 0; i < numberLetter; i++)
	{
		cout << letters[i] << " -> ";
		cout << frequency[letters[i]] << "\n";
	}
	cout << "\n";
	for (int i = 0; i < numberLetter; i++)
	{
		cout << letters[i] << "  " << codes[letters[i]] << " \n";
	}

	cout << "!!!!";
	//printTree(head);

}
void huffman::revrite()
{
	ifstream input("input.txt");
	char ch;
	ofstream output("output.txt", std::ios::binary);
	//ofstream output("output.bin", std::ios::out | std::ios::binary | std::ios::app);
	numberLetter = 0;
	string n = "";
	cout << "_______________________________________________________\n";
	while (input.get(ch))
	{
		//cout << ch;
		n += codes[ch];
		while (n.size() >= 4)
		{
			// cout << n << "   ";
			string temp = "";
			for (int i = 0; i < 4; i++) temp += n[i];
			string newN = "";
			for (unsigned int i = 4; i < n.size(); i++) newN += n[i];
			n = newN;

			// cout << temp  << "<-temp ->new " << n << " ";
			// int r;cin>>r;
			int size = temp.size();
			int p = 0;
			int s = 1;
			while (size > 0)
			{
				p += (temp[size - 1] - '0') * s;
				s *= 10;
				size--;
			}
			temp.clear();
			int q = 0;
			int i = 1;

			while (p > 0)
			{
				int r = p % 10;
				q += i*r;
				i *= 2;
				p /= 10;
			}


			char st;
			if (q < 10) st = char(q + int('0'));
			else st = char(q + int('A') - 10);
			char* st2 = &st;

			output.write((char*)(st2), sizeof(st));

		}

	}
	if (n.size() > 0)
	{

		int size = n.size();
		int p = 0;
		while (size > 0)
		{
			p *= 10;
			p += n[size - 1] - '0';
			size--;
		}
		int q = 0;
		int i = 1;
		while (p > 0)
		{
			int r = p % 10;
			q += i*r;
			i *= 2;
			p /= 10;
		}
		char st;
		if (q < 10) st = char(q + int('0'));
		else st = char(q + int('A') - 10);
		char* st2 = &st;

		output.write((char*)(st2), sizeof(st));
	}

	output.close();

	ifstream input2("output.txt");
	ofstream output2("inputNext.txt");

	string q = "";
	while (input2.get(ch))
	{
		int temp;
		if (ch - '0' >= 0 && ch - '0' <= 9) temp = ch - '0';
		else
		{
			temp = ch - 'A' + 10;
		}
		string newChar = "";
		while (temp > 0)
		{
			int r = temp % 2;
			temp /= 2;
			char rr = r + '0';
			newChar = rr + newChar;
		}
		while (newChar.size() < 4) newChar = '0' + newChar;
		q += newChar;
		//cout << q << " ";
		string curr = "";
		for (unsigned int i = 0; i < q.size(); i++)
		{
			curr += q[i];
			if (backToChar.find(curr) != backToChar.end())
			{
				//cout << curr;
				output2 << backToChar[curr];
				curr = "";
			}
		}
		q = curr;
	}

	/* while (size >=0)
	{
	q += memblock[size - 1];
	size = size - 1;
	if(backToChar.find(q) !=  backToChar.end())
	{
	output2 << backToChar[q];
	q = "";
	}
	//else q = ch - '0';
	}
	*/
}

