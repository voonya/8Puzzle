#include "Node.h"

void Node::expand(shared_ptr<Node> p) {
	if (childs.size() != 0) {
		
		for (int i = 0; i < childs.size(); i++) {
			childs[i] = nullptr;
		}
		childs.clear();
		//cout << "Che\n";
	}
		
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = i; k < 3; k++) {
				for (int l = j; l < 3; l++) {
					if ((i != k || j != l) && canSwap(i, j, k, l)) {
						shared_ptr<Node> child((new Node(swapEl(i, j, k, l),p)));
						if (this->parent == nullptr || child->state[i][j] != this->parent->state[i][j]) {
							childs.push_back(child);
						}
					}
				}
			}
		}
	}
}
bool Node::canSwap(int row_1, int col_1, int row_2, int col_2) {
	if ((row_1 == row_2 && abs(col_1 - col_2) == 1 || col_1 == col_2 && abs(row_1 - row_2) == 1) && (state[row_1][col_1] == 0 || state[row_2][col_2] == 0))
		return true;
	return false;
}
vector<vector<int>> Node::swapEl(int row_1, int col_1, int row_2, int col_2) {
	vector<vector<int>> copy = state;
	int buffer = copy[row_1][col_1];
	copy[row_1][col_1] = copy[row_2][col_2];
	copy[row_2][col_2] = buffer;
	return copy;
}


int Node::euristicH1() {
	int counter = 0;
	int num = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (state[i][j] != num)
				counter++;
			num++;
		}
	}
	return counter;
}

int Node::getFcost()
{
	return fCost;
}

int Node::getInversionsCount() {
	vector<int> copy;
	int count = 0;
	for (int i = 0; i < state.size(); i++) {
		for (int j = 0; j < state[i].size(); j++) {
			copy.push_back(state[i][j]);
		}
	}
	for (int i = 0; i < copy.size(); i++) {
		for (int j = i + 1; j < copy.size(); j++) {
			if (copy[i] && copy[j] && copy[i] > copy[j])
				count++;
		}
	}
	return count;
}