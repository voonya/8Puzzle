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
	int count = 0;
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
	int count_nodes = 0;
	_CONFIG_ cfg;
public:
	Solver() {};
	Solver(vector<vector<int>> p) : problem(p) {};
	Solver(string line) {
		problem.resize(3);
		int currRow = 0;
		while (line != "") {
			for (int i = 0; i < 3; i++) {
				problem[currRow].push_back(stoi(line.substr(0, 1)));
				line.erase(0, 1);
			}
			currRow++;
		}
	}
	void solveDLS() {
		shared_ptr<Node> start(new Node(problem));
		int s1 = clock();
		shared_ptr<Node> result = recursiveDLS(start, cfg.limit, 0);
		int s2 = clock();
		int d = s2 - s1;
		cout << float(d) / 60000 << "m | " << float(d) / 1000 << "s | " << d << "ms" << endl;
		//delete start;
		//return result;

	}
	shared_ptr<Node> recursiveDLS(shared_ptr<Node> current, int limit, int depth) {
		if (isWin(current->state)) {
			cout << "win\n";
			if(cfg.showSolution)
				showSolution(current);
			return current;
		}		
		else if (depth == limit) {
			return nullptr;
		}	
		else {
			current->expand(current);
			if (current->childs.empty())
				return nullptr;
			shared_ptr<Node> result = nullptr;
			for (size_t i = 0; i < current->childs.size(); i++)
			{
				current->childs[i]->parent = current;
				result = recursiveDLS(current->childs[i], limit, depth + 1);
				if (result != nullptr) {
					return result;
				}
				current->childs[i] = nullptr;
			}
			return result;
		}
	}

	void solveRBFS() {
		shared_ptr<Node> start(new Node(problem,nullptr));
		int s1 = clock();
		RBFS(start, 10e8, 0);
		int s2 = clock();
		int d = s2 - s1;
		cout << float(d) / 60000 << "m | " << float(d) / 1000 << "s | " << d << "ms" << endl;
	}
	int RBFS(shared_ptr<Node> current, int f_limit, int depth) {
		if (isWin(current->state)) {
			if (cfg.showSolution) {
				showSolution(current);
				return -1;
			}
		}
		else {
			if(current->childs.size() == 0)
				current->expand(current);
			if (current->childs.size() == 0) {
				return 10e8;
			}
			while (true) {
				sort(current->childs.begin(), current->childs.end(), [](shared_ptr<Node> a, shared_ptr<Node> b) {
					return a->fCost < b->fCost;
					});
				shared_ptr<Node> best = current->childs[0];
				//best->parent = current;
				if (best->fCost > f_limit) {
					//best->parent->childs[0] = nullptr;
					int bestDist = best->fCost;
					for (int i = 0; i < current->childs.size(); i++) {
						current->childs[i] = nullptr;
						best = nullptr;
					}
					current->childs.clear();
					return bestDist;
				}
				int alt = 10e8;
				if (current->childs.size() > 1)
					alt = current->childs[1]->fCost;
				best->fCost = RBFS(best, min(f_limit, alt), depth + 1);
				if (best->fCost == -1)
					return -1;
			}
			//sort(current->childs.begin(), current->childs.end(), [](shared_ptr<Node> a, shared_ptr<Node> b) {
			//	return a->dist < b->dist;
			//	});
			//shared_ptr<Node> best = current->childs[0];
			////best->parent = current;
			//while (best->dist <= f_limit && best->dist < 10e8) {

			//	int newFLimit;
			//	if (current->childs.size() > 1) {
			//		int alternative = current->childs[1]->dist;
			//		newFLimit = alternative;
			//	}
			//	else {
			//		newFLimit = f_limit;
			//	}
			//	int newFCost = RBFS(best, newFLimit, depth + 1);
			//	best->dist = newFCost;
			//	
			//	sort(current->childs.begin(), current->childs.end(), [](shared_ptr<Node> a, shared_ptr<Node> b) {
			//		return a->dist < b->dist;
			//		});
			//	best = current->childs[0];
			//	//best->parent = current;
			//}
			//return best->dist;
		}

	}
	bool isWin(vector<vector<int>> state) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (state[i][j] != goal[i][j])
					return false;
			}
		}
		return true;
	}
	int getInversionsCount(vector<vector<int>> state) {
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
	bool isSolvable(vector<vector<int>> state) {
		int inversionCount = getInversionsCount(state);
		return (inversionCount % 2 == 0);
	}
	void showMatr(vector<vector<int>> state) {
		cout << "\n";
		for (int i = 0; i < 3; i++) {
			cout << "   |";
			for (int j = 0; j < 3; j++)
			{
				if (state[i][j] == 0)
					cout << " ";
				else
					cout << state[i][j];
				cout << "|";
			}
			cout << "\n   -------\n";
		}
		cout << "\n";
	}

	void showSolution(shared_ptr<Node> n) {
		shared_ptr<Node> curr = n;
		while (curr!=nullptr) {
			solution.push(curr->state);
			curr = curr->parent;
		}
		while (solution.size() > 0) {
			showMatr(solution.top());
			solution.pop();
			cout << "      |\n";
			cout << "      |\n";
			cout << "     \\ /\n";
		}
	}
	vector<vector<int>> getProblem() {
		return problem;
	}
	void setProblem(vector<vector<int>> p) {
		problem = p;
	}
	void setCfg(_CONFIG_ c) {
		cfg = c;
	}
};

