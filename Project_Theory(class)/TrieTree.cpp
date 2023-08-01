#include "TrieTree.h"

TrieNode* NewNode()
{
	TrieNode* newNode = new TrieNode;

	// set all node child null
	for (int i = 0; i < NUM_TRIE_NODES; ++i)
		newNode->pNext[i] = nullptr;
	newNode->isEndOfWord = 0;

	return newNode;
}

bool TrieNode::IsEmpty()
{
	for (int i = 0; i < NUM_TRIE_NODES; ++i)
		if (pNext[i] != nullptr) return false;

	return true;
}

TrieTree::TrieTree()
{
	root = NewNode();
}

TrieTree::~TrieTree()
{
	DeleteAll();
}

bool TrieTree::IsEmpty()
{
	if (root == nullptr) return true;

	return root->IsEmpty();
}

void TrieTree::BuildTree(vector<string> st)
{
	for (int i = 0; i < st.size(); ++i) Insert(st[i]);

}

void TrieTree::Insert(string key)
{
	TrieNode* pNode = root;
	if (!pNode) pNode = NewNode();
	
	// create sub-branches in tree
	for (int i = 0; i < key.size(); ++i)
	{
		int index = key[i] - 'A'; // Change 'a' if trie has node (a-z)

		if (!pNode->pNext[index]) pNode->pNext[index] = NewNode();
		pNode = pNode->pNext[index];
	}

	// Set node is true
	++pNode->isEndOfWord;
}

bool TrieTree::Search(string key)
{
	if (root == nullptr) return false;
	TrieNode* pNode = root;

	for (int i = 0; i < key.size(); ++i)
	{
		int index = key[i] - 'A';

		if (!pNode->pNext[index]) return false;
		pNode = pNode->pNext[index];
	}

	return pNode && pNode->isEndOfWord;
}

int TrieTree::GetNumItems()
{
	if (root == nullptr) return 0;
	vector<TrieNode*> stack;
	stack.push_back(root);
	int res = 0;

	while (!stack.empty())
	{
		TrieNode* pNode = stack.back();
		stack.pop_back();

		res += pNode->isEndOfWord;
		for (int i = 0; i < NUM_TRIE_NODES; ++i)
			if (pNode->pNext[i]) stack.push_back(pNode->pNext[i]);
	}

	return res;
}

void TrieTree::Delete(string key)
{
	vector<TrieNode*> stack;
	if (root->IsEmpty()) return;
	stack.push_back(root);

	// Create a stack store all node has key
	for (int i = 0; i < key.size(); ++i)
	{
		TrieNode* pNode = stack.back();

		int index = key[stack.size() - 1] - 'A';
		stack.push_back(pNode->pNext[index]);
	}

	// delete node if its has key and no child
	while (!stack.empty())
	{
		TrieNode* pNode = stack.back();
		stack.pop_back();

		if (pNode->isEndOfWord) --pNode->isEndOfWord;

		if (!pNode->isEndOfWord && pNode->IsEmpty())
		{
			delete pNode;
			pNode = nullptr;
			if (stack.empty()) root = pNode;
			else stack.back()->pNext[key[stack.size() - 1] - 'A'] = pNode;
		}
	}
}

void TrieTree::DeleteAll()
{
	if (root == nullptr) return;
	vector<TrieNode*> stack;
	stack.push_back(root);

	while (!stack.empty())
	{
		TrieNode* pNode = stack.back();
		stack.pop_back();

		for (int i = 0; i < NUM_TRIE_NODES; ++i)
			if (pNode->pNext[i] != nullptr) stack.push_back(pNode->pNext[i]);

		delete pNode;
		pNode = nullptr;
	}
}