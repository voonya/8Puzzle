#pragma once
#include <vector>
#include <iostream>
using namespace std;
class Node
{
public:
	int fCost;
	int dist;
	int h;
	vector<vector<int>> state;
	vector<shared_ptr<Node>> childs;
	shared_ptr<Node> parent;

	Node() : parent(nullptr), fCost(0), dist(0), h(0) {};

	Node(vector<vector<int>> state) : state(state), parent(nullptr), fCost(0), dist(0), h(0) {}

	

	Node(vector<vector<int>> s, shared_ptr<Node> p) {
		state = s;
		parent = p;
		if (parent != nullptr) {
			dist = parent->dist + 1;
			h = euristicH1();
		}
		else {
			dist = 0;
			h = euristicH1();
		}
		fCost = dist + h;
	};
	void calcFcost() {
		if (parent != nullptr) {
			dist = parent->dist + 1;
			h = euristicH1();
		}
		else {
			dist = 0;
			h = euristicH1();
		}
	}
	void expand(shared_ptr<Node> p);

	bool canSwap(int row_1, int col_1, int row_2, int col_2);

	vector<vector<int>> swapEl(int row_1, int col_1, int row_2, int col_2);

	int euristicH1();

	int getFcost();

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



