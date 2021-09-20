#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>


using namespace std;

/*
	3  4  5			0  1  2
	8  0  1  -->	3  4  5
	2  6  7			6  7  8
*/
class Node {
	vector<vector<int>> state;
public:
	Node(vector<vector<int>> s) {
		state.resize(3);
		for (int i = 0; i < 3; i++) {
			state[i].resize(3);
		}
		state = s;
	}
	Node() {
		state.resize(3);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				state[i].push_back(0);
			}
		}
	}
	vector<Node> expandNode() {
		vector<Node> exp;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (state[i][j] != 0) {
					for (int k = i; k < 3; k++) {
						for (int l = j; l < 3; l++) {
							if ((i!=k || j!= l) && state[k][l] != 0 && canSwap(state, j, i, l, k)) {
								cout << i << " " << j << " " << k << " " << l << endl;
								exp.push_back(Node(swapEl(state, j, i, l, k)));
							}
						}
					}
				}
			}
		}
		for (Node node:exp) {
			node.showMatr();
		}
		return exp;
	}
	void showMatr() {
		for (int i = 0; i < 3; i++) {
			cout << "|";
			for (int j = 0; j < 3; j++)
			{
				if (state[i][j] == 0)
					cout << " ";
				else
					cout << state[i][j];
				cout << "|";
			}
			cout << "\n------\n";
		}
		cout << endl;
	}
	bool canSwap(vector<vector<int>> matr, int x1, int y1, int x2, int y2) {
		// находятся на одной х координате
		if (x1 == x2 && abs(y1 - y2) == 1 && (matr[x1][y1] == 0 || matr[x2][y2] == 0))
			return true;
		// на одной у координате
		if (y1 == y2 && abs(x1 - x2) == 1 && (matr[x1][y1] == 0 || matr[x2][y2] == 0))
			return true;
		return false;
	}
	vector<vector<int>> swapEl(vector<vector<int>> matr, int x1, int y1, int x2, int y2) {
		vector<vector<int>> copy = matr;
		int buffer = copy[x1][y1];
		copy[x1][y1] = copy[x2][y2];
		copy[x2][y2] = buffer;
		return copy;
	}
};

bool canSwap(vector<vector<int>> matr, int x1, int y1, int x2, int y2) {
	// находятся на одной х координате
	if (x1 == x2 && abs(y1 - y2) == 1 && (matr[x1][y1] == 0 || matr[x2][y2] == 0))
		return true;
	// на одной у координате
	if (y1 == y2 && abs(x1 - x2) == 1 && (matr[x1][y1] == 0 || matr[x2][y2] == 0))
		return true;
	return false;
}

void showMatr(int matr[3][3]) {
	for (int i = 0; i < 3; i++) {
		cout << "|";
		for (int j = 0; j < 3; j++)
		{
			if (matr[i][j] == 0)
				cout << " ";
			else
				cout << matr[i][j];
			cout << "|";
		}
		cout << "\n------\n";
	}
}
vector<vector<int>> swapEl(vector<vector<int>> matr, int x1, int y1, int x2, int y2) {
	vector<vector<int>> copy = matr;
	int buffer = copy[x1][y1];
	copy[x1][y1] = copy[x2][y2];
	copy[x2][y2] = buffer;
	return copy;
}
/*void moveEl(int matr[3][3], int x, int y, int dir) {
	if (matr[x][y] == 0) {
		cout << "error move empty cell\n";
		return;
	}
	if (dir == 0 && x == 0 || dir == 1 && y == 2 || dir == 2 && x == 2 || dir == 3 && y == 0) {
		cout << "error out of field\n";
		return;
	}
	switch (dir) {
	case 0:
		swapEl(matr, x, y, x - 1, y);
		break;
	case 1:
		swapEl(matr, x, y, x, y + 1);
		break;
	case 2:
		swapEl(matr, x, y, x + 1, y);
		break;
	case 3:
		swapEl(matr, x, y, x, y - 1);
		break;

	}
}*/

bool isWin(int matr[3][3]) {
	int counter = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matr[i][j] != counter) return false;
			counter++;
		}
	}
	return true;
}


int main()
{
	
	vector<vector<int>> matr =
	{
		{1, 0, 2},
		{3, 4, 5},
		{6, 7, 8}
	};

	Node test(matr);
	test.expandNode();
	return 0;
}

