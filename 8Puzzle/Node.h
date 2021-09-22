#pragma once
#include <vector>
#include <iostream>
using namespace std;
class Node
{
public:
	int f;
	vector<vector<int>> state;
	vector<Node*> childs;
	Node* parent;
	Node(vector<vector<int>> state) : state(state), parent(nullptr), f(0){}
	Node(): parent(nullptr) {};
	void expand() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
					for (int k = i; k < 3; k++) {
						for (int l = j; l < 3; l++) {
							if ((i!=k || j!= l) && canSwap(i, j, k, l)) {
								Node* child = new Node(swapEl(i, j, k, l));
								child->parent = this;
								if (this->parent == nullptr || child->state[i][j] != this->parent->state[i][j])
									childs.push_back(child);
							}
						}
					}
			}
		}
	}
	bool canSwap(int row_1, int col_1, int row_2, int col_2) {
		if ((row_1 == row_2 && abs(col_1 - col_2) == 1 || col_1 == col_2 && abs(row_1 - row_2) == 1) && (state[row_1][col_1] == 0 || state[row_2][col_2] == 0))
			return true;
		return false;
	}
	vector<vector<int>> swapEl(int row_1, int col_1, int row_2, int col_2) {
		vector<vector<int>> copy = state;
		int buffer = copy[row_1][col_1];
		copy[row_1][col_1] = copy[row_2][col_2];
		copy[row_2][col_2] = buffer;
		return copy;
	}
	~Node(){
		for (vector<Node*>::iterator n = childs.begin(); n < childs.end(); n++) {
			delete* n;
		}
		childs.clear();
		parent = nullptr;
		delete parent;
		state.clear();
		vector<vector<int>>().swap(state);
		vector<Node*>().swap(childs);
	}
};

