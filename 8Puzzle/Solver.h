#pragma once
#include "Node.h"
#include "Reader.h"
#include <iostream>
#include <stack>
#include <ctime>
#include <memory>
#include <stdlib.h>
#include <algorithm>

class Solver
{
	vector<vector<int>> goal = {
		{0,1,2},
		{3,4,5},
		{6,7,8}
	};
	/*vector<vector<int>> goal = {
		{1,2,3},
		{4,5,6},
		{7,8,0}
	};*/
	vector<vector<int>> problem;
	stack<vector<vector<int>>> solution;
	int countNodes = 0;
	int countNodesAtAll = 0;
	int startTime;
	_CONFIG_ cfg;

private:
	void solveDLS();

	shared_ptr<Node> recursiveDLS(shared_ptr<Node> current, int limit, int depth);

	void solveRBFS();

	int RBFS(shared_ptr<Node> current, int f_limit, int depth);

	bool isWin(vector<vector<int>> state);
public:
	Solver() {};

	Solver(vector<vector<int>> p) : problem(p) {};
	
	Solver(string line);

	stack<vector<vector<int>>> solve();

	//bool isSolvable(vector<vector<int>> state);

	void makeSolution(shared_ptr<Node> n);

	void setProblem(vector<vector<int>> p);

	void setCfg(_CONFIG_ c);

	vector<vector<int>> getProblem() {
		return problem;
	}
};

