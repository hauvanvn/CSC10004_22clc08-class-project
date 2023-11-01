#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "TrieTree.h"

using namespace std;

// Read dictionary from give file
vector<string> GetDictionaryFile(string file_name)
{
	ifstream input(file_name);

	int n;
	input >> n;
	vector<string> dictionary(n);
	for (int i = 0; i < n; ++i) getline(input, dictionary[i]);

	input.close();
	return dictionary;
}

// Save dictionary to given file
void SaveDictionaryFile(string file_name, vector<string> dictionary)
{
	ofstream output(file_name);

	output << dictionary.size() << "\n";
	for (auto i : dictionary) output << i << "\n";

	output.close();
}

int main()
{
	string file_name = "dictionary.txt";
	vector<string> dictionary = GetDictionaryFile(file_name);

	TrieTree root;

	// Test whether a trie is empty
	cout << (root.IsEmpty() ? "Trie tree is empty" : "Trie tree is not empty") << "\n";

	// Build a trie from given items
	root.BuildTree(dictionary);
	cout << (root.IsEmpty() ? "Trie tree is empty" : "Trie tree is not empty") << "\n";

	// Get number of items in a tre
	cout << "Number of items in a tree: " << root.GetNumItems() << "\n";

	// Find the item in a trie. EX: "data struct"
	cout << "data struct " << (root.Search("data struct") ? "is exist in tree\n" : "is not exist in tree\n");

	// Insert a new item into the trie. EX: "data struct"
	root.Insert("DATA STRUCT");
	cout << "data struct " << (root.Search("data struct") ? "is exist in tree\n" : "is not exist in tree\n");

	// Remove an item from the trie. EX: "data struct"
	root.Delete("DATA STRUCT");
	cout << "data struct " << (root.Search("data struct") ? "is exist in tree\n" : "is not exist in tree\n");

	// Remove all elements from the trie
	root.DeleteAll();
	cout << (root.IsEmpty() ? "Trie tree is empty" : "Trie tree is not empty") << "\n";

	return 0;
}

// kjklasdjas