#include "TrieTree.h"

TrieNode* NewNode()
{
	TrieNode* newNode = new TrieNode;

	// set all node child null
	for (int i = 0; i < NUM_TRIE_NODES; ++i)
		newNode->pNext[i] = nullptr;
	newNode->isEndOfWord = false;

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
	// Lowercase string
	for (auto& i : key) i = tolower(i);

	TrieNode* pNode = root;
	if (!pNode) pNode = NewNode();

	// create sub-branches in tree
	for (int i = 0; i < key.size(); ++i)
	{
		int index = getTrieIndex(key[i]);

		if (!pNode->pNext[index]) pNode->pNext[index] = NewNode();
		pNode = pNode->pNext[index];
	}

	// Set node is true
	pNode->isEndOfWord = true;
}

bool TrieTree::Search(string key)
{
	if (root == nullptr) return false;

	// Lowercase string
	for (auto& i : key) i = tolower(i);

	TrieNode* pNode = root;

	for (int i = 0; i < key.size(); ++i)
	{
		int index = getTrieIndex(key[i]);

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
	if (root->IsEmpty()) return;

	// Lowercase string
	for (auto& i : key) i = tolower(i);

	vector<TrieNode*> stack;
	stack.push_back(root);

	// Create a stack store all node has key
	for (int i = 0; i < key.size(); ++i)
	{
		TrieNode* pNode = stack.back();

		int index = getTrieIndex(key[stack.size() - 1]);
		stack.push_back(pNode->pNext[index]);
	}

	// delete node if its has key and no child
	while (!stack.empty())
	{
		TrieNode* pNode = stack.back();
		stack.pop_back();

		if (pNode->isEndOfWord) pNode->isEndOfWord = false;

		if (!pNode->isEndOfWord && pNode->IsEmpty())
		{
			delete pNode;
			pNode = nullptr;
			if (stack.empty()) root = pNode;
			else stack.back()->pNext[getTrieIndex(key[stack.size() - 1])] = pNode;
		}
	}
}

void TrieTree::DeleteAll()
{
	if (root == nullptr || root->IsEmpty()) return;
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

	root = nullptr;
}

vector<string> TrieTree::Suggest(string key)
{
	// Lowercase string
	for (auto& i : key) i = tolower(i);

	vector<string> res;
	vector<pair<TrieNode*, string>> stack;
	if (root == nullptr) return res;
	stack.push_back({ root, key });

	// pre find key location
	for (int i = 0; i < key.size(); ++i)
	{
		int index = getTrieIndex(key[i]);

		if (!stack.back().first->pNext[index]) return res;
		stack.back().first = stack.back().first->pNext[index];
	}

	while (!stack.empty())
	{
		TrieNode* pNode = stack.back().first;
		string keySuggest = stack.back().second;
		stack.pop_back();

		if (pNode->isEndOfWord) res.push_back(keySuggest);

		for (int i = 0; i < NUM_TRIE_NODES; ++i)
			if (pNode->pNext[i] != nullptr) 
				stack.push_back({ pNode->pNext[i], keySuggest + IndexToChar(i)});
	}

	return res;
}

int getTrieIndex(int n)
{
	if (97 <= n && n <= 122) return n - 'a';
	if (32 <= n && n <= 47) return n - ' ' + 26;
	if (58 <= n && n <= 64) return n - ':' + 26 + 16;
	if (91 <= n && n <= 96) return n - '[' + 26 + 16 + 7;
	if (123 <= n && n <= 126) return n - '{' + 26 + 16 + 7 + 6;
	return -1;
}

char IndexToChar(int n)
{
	if (n < 26) return n + 'a';
	if (n < 42) return n - 26 + ' ';
	if (n < 49) return n - 26 - 16 + ':';
	if (n < 55) return n - 26 - 16 - 7 + '[';
	if (n < 59) return n - 26 - 16 - 7 - 6 + '{';
	return 0;
}