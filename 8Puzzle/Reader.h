#pragma once
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

using namespace std;

struct _CONFIG_ {
	int limit;
	string typeSearch;
	bool showSolution;
	_CONFIG_() : limit(0), typeSearch(""), showSolution(0) {};
	_CONFIG_(int l, string t, bool sS) : limit(l), typeSearch(t), showSolution(sS) {}
};

class Reader
{
public:
	Reader() {};
	vector<vector<int>> readInitialState(string filename);
	_CONFIG_ setConfig(string filename);

};

