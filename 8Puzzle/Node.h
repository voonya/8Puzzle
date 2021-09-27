#pragma once
#include <vector>
#include <memory>
using namespace std;
class Node
{
	// ���� f
	int fCost;
	// ������� �� �����
	int dist;
	// ���� ��������
	int h;
	// ���� ��������� �����
	vector<vector<int>> state;
	// ��� �����
	vector<shared_ptr<Node>> childs;
	// ������ �����
	shared_ptr<Node> parent;
public:
	
	Node() : parent(nullptr), fCost(0), dist(0), h(0) {};

	Node(vector<vector<int>> state) : state(state), parent(nullptr), fCost(0), dist(0), h(0) {}

	Node(vector<vector<int>> s, shared_ptr<Node> p);
	// ������������� �����
	void expand(shared_ptr<Node> p);
	// ���������� ���� f
	int getFcost();

private:
	// �������� �� ����� ������� ������ �� �������
	bool canSwap(int row_1, int col_1, int row_2, int col_2);
	// ���� ������ ���� �������
	vector<vector<int>> swapEl(int row_1, int col_1, int row_2, int col_2);
	// ��������
	int euristicH1();
	// ����������� ������� ������	
	int getInversionsCount();

	int manhattan();

	friend class Solver;
};



