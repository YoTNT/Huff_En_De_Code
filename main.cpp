#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Global variables.
int charCounts[256] = {0};
string charCode[256] = {""};

// Declearations
void print_append(string, string);


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

// Constructing an ordered linked list without concatenation
linkedList HuffmanBinaryTree :: constructHuffmanLList(string output_file_name)
{
	linkedList L;

	for(int i = 0; i < 256; i++)
	{
		if(charCounts[i] > 0)
		{
			string s(1, (char)i);
			// Adding code if needs new lines as a character
			treeNode* temp = new treeNode(s, charCounts[i]);
			L.insertOneNode(L.findSpot(temp), temp);
		}
	}

	// Root -> listHead
	this->Root = L.listHead;

	print_append("\n", output_file_name);
	print_append(L.printList(), output_file_name);

	return L;
}

void HuffmanBinaryTree :: constructHuffmanBinTree(linkedList *L, string output_file_name)
{
	string new_chStr;
	int new_prob = 0;

	while(L->listHead->next->next != NULL)
	{
		// Concatenating characters
		new_chStr = L->listHead->next->chStr;
		new_chStr += L->listHead->next->next->chStr;

		// Summing probabilities up
		new_prob = L->listHead->next->prob;
		new_prob += L->listHead->next->next->prob;

		// Creating new node
		treeNode* new_node = new treeNode(new_chStr, new_prob);

		// Pointing the new node's left and right to its original nodes
		new_node->left = L->listHead->next;
		new_node->right = L->listHead->next->next;

		// Inserting new node
		L->insertOneNode(L->findSpot(new_node), new_node);

		// Shifting the linked list head to the next one
		L->listHead->next = L->listHead->next->next->next;

		// Printing out the current linked list to the ouput file
		print_append("\n", output_file_name);
		print_append(L->printList(), output_file_name);
	}

	// Renewing the Root
	this->Root = L->listHead->next;
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
				continue;
//				outFile << "LF" << "\t" << charCounts[i] << endl;
			else if(i == 13)
				continue;
//				outFile << "CR" << "\t" << charCounts[i] << endl;
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
		if(index != 10 and index != 13)
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

// Outputting Huffman code to charCode[]
void getCode(treeNode *T, string code, string output_file_name)
{
	if(isLeaf(T))
	{
		T->code = code;
		// Writing code to charCode[]
		char indexChar = (char)T->chStr.at(0);
		charCode[(int)indexChar] = code;
		// Writing <char code> pair to output file
		string line = T->chStr + "\t" + T->code + "\n";
		print_append(line, output_file_name);
	}
	else
	{
		// Go to its both left and right child if it has
		if(T->left != NULL)
		{
			string newCode_left = code + "0";
			getCode(T->left, newCode_left, output_file_name);
		}
		if(T->right != NULL)
		{
			string newCode_right = code + "1";
			getCode(T->right, newCode_right, output_file_name);
		}
	}
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

	HuffmanBinaryTree T;
	linkedList temp = T.constructHuffmanLList(argv[6]);
	T.constructHuffmanBinTree(&temp, argv[6]);

	// Cleaning up everything in <char code> file first
	ofstream char_code(argv[3], ifstream::trunc);
	char_code.close();
	string fakeCode;
	getCode(T.Root, fakeCode, argv[3]);

	// Encoding file


	return 0;
}
