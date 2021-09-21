#pragma once
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

using namespace std;
struct _CONFIG_ {
	int limit;
	string typeSearch;
	bool showSolution;
	_CONFIG_(): limit(0), typeSearch(""), showSolution(0) {};
	_CONFIG_(int l, string t, bool sS) : limit(l), typeSearch(t), showSolution(sS) {}
};

class Reader
{
public:
	Reader(){}
	vector<vector<int>> readInitialState(string filename) {
		string path = filesystem::current_path().string() + "/states/" + filename;
		ifstream inF(path);
		if (inF.is_open()) {
			vector<vector<int>> state(3);
			int currRow = 0;
			while (!inF.eof()) {
				string buffer;
				getline(inF, buffer);
				while (buffer != "") {
					state[currRow].push_back(stoi(buffer.substr(0,1)));
					buffer.erase(0, 1);
				}
				currRow++;
			}
			return state;
		}
		else {
			exit(0);
		}
		inF.close();
	}
	_CONFIG_ setConfig(string filename) {
		string path = filesystem::current_path().string() + "/" + filename;
		ifstream inF(path);
		_CONFIG_ cfg;
		if (inF.is_open()) {
			vector<vector<int>> state(3);
			while (!inF.eof()) {
				string buffer;
				getline(inF, buffer);
				if (buffer.find("limit") != string::npos) {
					cfg.limit = stoi(buffer.substr(buffer.find("=")+1));
				}
				else if (buffer.find("type") != string::npos) {
					cfg.typeSearch = buffer.substr(buffer.find("=")+1);
				}
				else if (buffer.find("show_solution") != string::npos) {
					cfg.showSolution = stoi(buffer.substr(buffer.find("=")+1));
				}
			}
			return cfg;
		}
		else {
			exit(0);
		}
	}
};

