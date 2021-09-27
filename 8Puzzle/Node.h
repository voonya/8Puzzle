#pragma once
#include <vector>
#include <memory>
using namespace std;
class Node
{
	// ц≥на f
	int fCost;
	// в≥дстань до вузла
	int dist;
	// ц≥на евр≥стики
	int h;
	// стан поточного вузла
	vector<vector<int>> state;
	// д≥ти вузла
	vector<shared_ptr<Node>> childs;
	// батько вузла
	shared_ptr<Node> parent;
public:
	
	Node() : parent(nullptr), fCost(0), dist(0), h(0) {};

	Node(vector<vector<int>> state) : state(state), parent(nullptr), fCost(0), dist(0), h(0) {}

	Node(vector<vector<int>> s, shared_ptr<Node> p);
	// розгортуванн€ вузла
	void expand(shared_ptr<Node> p);
	// поверненн€ ц≥ни f
	int getFcost();

private:
	// перев≥рка чи можна пом≥н€ти м≥сц€ми дв≥ кл≥тинки
	bool canSwap(int row_1, int col_1, int row_2, int col_2);
	// зм≥на м≥сц€ми двох кл≥тинок
	vector<vector<int>> swapEl(int row_1, int col_1, int row_2, int col_2);
	// евр≥стика
	int euristicH1();
	// п≥драхуванн€ к≥лькост≥ ≥нверс≥	
	int getInversionsCount();

	int manhattan();

	friend class Solver;
};



