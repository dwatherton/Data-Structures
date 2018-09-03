#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

struct Node {
	char character;
	Node* left;
	Node* right;
};

Node* loadTree(string fileName);
void insertNode(Node* &root, char character, string code);
int menu(int choice);
void morseToEnglish(Node* root);
void englishToMorse(Node* root);
Node* search(Node* currNode, char key, vector<char> &characters);

int main()
{
	int choice = 0;

	// Create the binary tree
	Node* root = loadTree("morsecode.txt");

	do {
		system("cls");
		choice = menu(choice);

		switch(choice)
		{
			case 1:
			{
				morseToEnglish(root);
				break;
			}
			case 2:
			{
				englishToMorse(root);
				break;
			}
			case 3:
			{
				system("exit");
				break;
			}
			default:
			{
				cout << endl << "Please enter a number 1 - 3..." << endl << endl;
				system("pause");
				break;
			}
		}
	} while(choice != 3);

	cout << endl << "Thank you for using the Morse Code Translation program!" << endl << endl;
	system("pause");
	return 0;
}

Node* loadTree(string fileName)
{
	char character;
	string code;
	fstream fin;
	Node* root;
	// Create the empty node that root will point to
	Node* empty = new Node;
	empty->character = ' ';
	empty->left = nullptr;
	empty->right = nullptr;
	// Set root pointer to the empty node
	root = empty;

	fin.open(fileName);
	if (!fin.is_open() && !fin.eof())
	{
		cout << "ERROR! No morse code file! Exiting program" << endl;
		return nullptr;
	}
	
	while (!fin.eof())
	{
		fin >> character >> code;
		// Insert a node for each line of the file
		insertNode(root, character, code);
	}
	return root;
}

void insertNode(Node* &root, char character, string code)
{
	Node* node = new Node;
	node->character = character;
	node->left = nullptr;
	node->right = nullptr;

	// Check the "head case"
	if (root == nullptr)
	{
		root = node;
	}
	else
	{
		Node* currNode = root;
		while (currNode != nullptr)
		{
			// Loop through the code string
			for (int i = 0; i < code.size(); i++)
			{
				if (code[i] == '*')
				{
					if (currNode->left == nullptr)
					{
						// If left is empty, add the node
						currNode->left = node;
						return;
					}
					else
					{
						currNode = currNode->left;
					}
				}
				else if (code[i] == '-')
				{
					if (currNode->right == nullptr)
					{
						// If right is empty, add the node
						currNode->right = node;
						return;
					}
					else
					{
						currNode = currNode->right;
					}
				}
				else
				{
					cout << "ERROR, invalid character in the morse code string! Did not insert the node." << endl;
					return;
				}
			}
		}
	}
}

int menu(int choice)
{
	cout << "\t\t    Welcome to the morse code translation program!" << endl << endl;
	cout << "\t\t\t  1. Translate Morse Code to English" << endl;
	cout << "\t\t\t  2. Translate English to Morse Code" << endl;
	cout << "\t\t\t  3. Quit" << endl << endl;
	cout << "Enter your choice here => ";
	cin >> choice;
	cin.ignore();
	return choice;
}

void morseToEnglish(Node* root)
{
	string morseCode;
	vector<char> characters;
	bool invalid = false;
	Node* currNode = root;

	cout << endl << "Please seperate Morse Code letters with a single space and seperate words with a double space!" << endl << endl;
	cout << "Enter the Morse Code to be translated into English here => ";
	getline(cin, morseCode);

	// Loop through the string of morse code
	for (int i = 0; i < morseCode.size(); i++)
	{
		if (morseCode[i] == '*')
		{
			if (currNode->left == nullptr)
			{
				// Can't go left, Invalid
				invalid = true;
			}
			else
			{
				currNode = currNode->left;
			}
		}
		else if (morseCode[i] == '-')
		{
			if (currNode->right == nullptr)
			{
				// Can't go right, Invalid
				invalid = true;
			}
			else
			{
				currNode = currNode->right;
			}
		}
		else if (morseCode[i] == ' ')
		{
			// Save the letter (end of morse code letter)
			characters.push_back(currNode->character);
			// Restart at the root
			currNode = root;
			if (morseCode[i + 1] == ' ' && currNode->character != ' ')
			{
				// Add a space to translation (2 spaces in row)
				characters.push_back(' ');
			}
		}
		else
		{
			// Not a '*', '-', or ' ', Invalid
			invalid = true;
		}
	}

	if (invalid)
	{
		cout << endl << "ERROR! Some of the morse code you entered is invalid!";
	}
	else
	{
		// Save last character
		characters.push_back(currNode->character);

		cout << endl << "The translation is: ";
		for (int j = 0; j < characters.size(); j++)
		{
			cout << characters.at(j);
		}
	}

	cout << endl << endl;
	system("pause");
	return;
}

void englishToMorse(Node* root)
{
	string english;
	bool invalid = false;
	Node* found;
	vector<char> translated;

	cout << endl << "Please note, Morse Code letters will be single space seperated and words will be double space seperated!" << endl << endl;
	cout << "Enter the English (in capital letters) to be translated into Morse Code here => ";
	getline(cin, english);

	// Loop through the string of english
	for (int i = 0; i < english.size(); i++)
	{
		vector<char> characters;
		found = search(root, english.at(i), characters);

		if (characters.size() > 1)
		{
			// Reverse vector if 2 or more characters
			reverse(characters.begin() + 1, characters.end());
		}

		characters.push_back(' ');
		if (found != nullptr)
		{
			for (int i = 1; i < characters.size(); i++)
			{
				// Store characters path in translated vector
				translated.push_back(characters.at(i));
			}
		}
		else
		{
			invalid = true;
		}
	}

	if (invalid)
	{
		cout << endl << "ERROR! Some of the characters you entered are invalid!";
	}
	else
	{
		cout << endl << "The translation is: ";
		for (int j = 0; j < translated.size(); j++)
		{
			cout << translated.at(j);
		}
	}

	cout << endl << endl;
	system("pause");
	return;
}

Node* search(Node* node, char key, vector<char> &characters)
{
	Node* currNode = node;
	while (currNode != nullptr)
	{
		if (currNode->character == key)
		{
			characters.push_back('*');
			return currNode;
		}
		// Recurse LEFT
		currNode = search(currNode->left, key, characters);
	}
	currNode = node;
	while (currNode != nullptr)
	{
		if (currNode->character == key)
		{
			characters.push_back('-');
			return currNode;
		}
		// Recurse RIGHT
		currNode = search(currNode->right, key, characters);
	}
	return currNode;
}