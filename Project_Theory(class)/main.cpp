#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "TrieTree.h"

using namespace std;

int main()
{
	ifstream input("t.inp");

	TrieTree root;
	vector<string> a;
	string tmp;
	while (getline(input, tmp))
	{
		a.push_back(tmp);
	}

	root.BuildTree(a);
	string key = "haudeptrai";
	root.Insert(key);

	cout << root.GetNumItems() << "\n";
	root.Delete(key);
	cout << root.Search(key) << "\n";

	input.close();
	return 0;
}