#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Global variables.
int charCounts[256] = {0};
int charCode[256] = {0};

// Declearations



// Classes
class treeNode
{
	public:
		string chStr;
		int prob;
		treeNode* next;
		treeNode* left;
		treeNode* right;
		string code;
		// Constructors
		treeNode();
		treeNode(string, int);
};

treeNode :: treeNode()
{
	chStr = "dummy";
	prob = 0;
	next = NULL;
	left = NULL;
	right = NULL;
	code = "";
}

treeNode :: treeNode(string c, int p)
{
	chStr = c;
	prob = p;
	next = NULL;
	left = NULL;
	right = NULL;
	code = "";
}


class linkedList
{
	public:
		treeNode* listHead;

		// Constructor
		linkedList();

		treeNode* findSpot(treeNode *);
		void insertOneNode(treeNode *, treeNode *);
		string printList();
};

linkedList :: linkedList()
{
	listHead = new treeNode();
}

treeNode* linkedList :: findSpot(treeNode *newNode)
{
	treeNode* spot = this->listHead;
	while(spot->next != NULL)
	{
		if(spot->next != NULL and spot->next->prob < newNode->prob)
			spot = spot->next;
		else
			return spot;
	}
	return spot;
}

void linkedList :: insertOneNode(treeNode *spot, treeNode *newNode)
{
	newNode->next = spot->next;
	spot->next = newNode;
}

string linkedList :: printList()
{
	string line = "listHead --> ";
	treeNode* ptr = this->listHead;
	while(ptr->next != NULL)
	{
		line += "(\"";
		line += ptr->chStr;
		line += "\", ";
		line += std::to_string(ptr->prob);
		line += ", \"";
		line += ptr->next->chStr;
		line += "\") -- > ";
		ptr = ptr->next;
	}
	line += "(\"";
	line += ptr->chStr;
	line += "\", ";
	line += std::to_string(ptr->prob);
	line += ", NULL) --> NULL\n";

	return line;
}


class HuffmanBinaryTree
{
	public:
		treeNode* Root;
		HuffmanBinaryTree();
		HuffmanBinaryTree(treeNode *);
		
		linkedList constructHuffmanLList(string);
		void constructHuffmanBinTree(linkedList *, string);

		// Pre, Post, In-order methods should be here
		// if it's necessary
};

HuffmanBinaryTree :: HuffmanBinaryTree()
{
	Root = new treeNode();
}

HuffmanBinaryTree :: HuffmanBinaryTree(treeNode *listHead)
{
	Root = listHead;
}

linkedList HuffmanBinaryTree :: constructHuffmanLList(string output_file_name)
{
	linkedList L;

	for(int i = 0; i < 256; i++)
	{
		if(charCounts[i] > 0)
		{
			treeNode* temp = new treeNode((char)i, charCounts[i]);
			L.insertOneNode(L.findSpot(temp), temp);
		}
	}

	// Root -> listHead
	this->Root = L.listHead;

	print_append(L.printList(), output_file_name);

	return L;
}

void HuffmanBinaryTree :: constructHuffmanBinTree(linkedList *L, string output_file_name)
{
	
}







// Functions
void printAry(string Output_File_Name)
{
	ofstream outFile(Output_File_Name);
	for(int i = 0; i < 256; i++)
	{
		if(charCounts[i] > 0)
		{
			if(i == 10)
				outFile << "LF" << "\t" << charCounts[i] << endl;
			else if(i == 13)
				outFile << "CR" << "\t" << charCounts[i] << endl;
			else
				outFile << (char)i << "\t" << charCounts[i] << endl;
		}
	}

	outFile.close();
	return;
}

void computeCount(string Input_File_Name)
{
	// Initializing
	char charIn;
	int index = 0;

	// Scanning characters from input file, characters one by one.
	ifstream inFile;
	inFile.open(Input_File_Name);
	// Counting characters
	while(inFile >> noskipws >> charIn)
	{
		index = (int)charIn;
		charCounts[index]++;
	}

	inFile.close();
	return;
}

bool isLeaf(treeNode *node)
{
	if(node->left == NULL and node->right == NULL)
		return true;
	else
		return false;
}

void print_append(string content, string file_name)
{
	ofstream outFile(file_name, fstream::app);
	outFile << content;
	outFile.close();
}


// argv[1]: An English text file to compute char-prob pairs.
// argv[2]: An English text file for encoding
// argv[3]:	A text file contains the Huffman <char, code> pairs
// argv[4]: A text file contains the encoded result.
// argv[5]: A text file contains the decoded result.
// argv[6]: for all the debugging outputs.

int main(int argc, char** argv)
{
	computeCount(argv[1]);
	printAry(argv[6]);

	
	return 0;
}
