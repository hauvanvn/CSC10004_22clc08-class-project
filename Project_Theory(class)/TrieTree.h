#pragma one
#ifndef _TRIE_TREE_H_
#define _TRIE_TREE_H_

#include <vector>
#include <string>

using namespace std;

const int NUM_TRIE_NODES = 58; // 26 for (a-z) or (A-Z), 58 for (A-z)

// Node of trie tree
struct TrieNode
{
	TrieNode* pNext[NUM_TRIE_NODES];

	unsigned int isEndOfWord; // use int if duplicate and bool if not

	// Check if trie node is empty
	bool IsEmpty();
};

// Trie tree
class TrieTree
{
public:
	// Contruct
	TrieTree(); 

	// Decontruct
	~TrieTree(); 

	// Check if trie tree is empty
	bool IsEmpty();

	// Build trie tree form give array (use vector)
	void BuildTree(vector<string> st);

	// Add an data to trie tree
	void Insert(string key);

	// Check if data exist in trie tree
	bool Search(string key);

	// Number of exist Items(data) in trie tree
	int GetNumItems();

	// Delete an data in trie tree
	void Delete(string key);

	// Delete all data in trie tree
	void DeleteAll();

private:
	TrieNode* root;
};

// Create a new trie node
TrieNode* NewNode();


#endif // _TRIE_TREE_H_
