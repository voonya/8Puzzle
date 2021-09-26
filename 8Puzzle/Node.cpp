#include "Node.h"
Node::Node(vector<vector<int>> s, shared_ptr<Node> p) {
	state = s;
	parent = p;
	if (parent != nullptr) {
		dist = parent->dist + 1;
		h = euristicH1();
		//h = manhattan();
		fCost = max(dist + h, parent->fCost);
	}
	else {
		dist = 0;
		h = euristicH1();
		//h = manhattan();
		fCost = dist + h;
	}
};
void Node::expand(shared_ptr<Node> p) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = i; k < 3; k++) {
				for (int l = j; l < 3; l++) {
					if ((i != k || j != l) && canSwap(i, j, k, l)) {
						vector<vector<int>> child = swapEl(i, j, k, l);
						if (this->parent == nullptr || child[i][j] != this->parent->state[i][j]) {
							childs.push_back(shared_ptr<Node>(new Node(child,p)));	
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

int Node::manhattan(){

	vector<vector<int>> goal = {
		{0,1,2},
		{3,4,5},
		{6,7,8}
	};
	int dist = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (state[i][j] != 0)
			{
				for (int k = 0; k < 3; k++)
				{
					for (int l = 0; l < 3; l++)
					{
						if (state[i][j] == goal[k][l])
							dist += abs(i - k) + abs(j - l);
					}
				}
			}
		}
	}

	return dist;
}