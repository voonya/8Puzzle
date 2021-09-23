#pragma once
#include <vector>
#include <iostream>
using namespace std;
class Node
{
public:
	int fLimit;
	int dist;
	vector<vector<int>> state;
	vector<shared_ptr<Node>> childs;
	shared_ptr<Node> parent;
	Node(vector<vector<int>> state) : state(state), parent(nullptr), fLimit(0), dist(0) {}
	Node(): parent(nullptr),fLimit(0), dist(0) {};
	Node(vector<vector<int>> state, shared_ptr<Node> parent): state(state), parent(parent),fLimit(0), dist(0) {};
	void expand() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
					for (int k = i; k < 3; k++) {
						for (int l = j; l < 3; l++) {
							if ((i!=k || j!= l) && canSwap(i, j, k, l)) {
								shared_ptr<Node> child(new Node(swapEl(i, j, k, l)));
								if (this->parent == nullptr || child->state[i][j] != this->parent->state[i][j]) {
									childs.push_back(child);
								}
									
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
	/*~Node(){
		c--;
		for (vector<shared_ptr<Node>>::iterator n = childs.begin(); n < childs.end(); n++) {
			delete n;
		}
		childs.clear();
		parent = nullptr;
		delete parent;
		state.swap(vector<vector<int>>());
	}*/
};



