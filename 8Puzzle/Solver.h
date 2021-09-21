#pragma once
#include "Node.h"
#include "Reader.h"
#include <iostream>
#include <stack>
#include <ctime>
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
	Node* solveDLS() {
		Node* start = new Node(problem);
		int s1 = clock();
		Node* result = recursiveDLS(start, cfg.limit, 0);
		int s2 = clock();
		int d = s2 - s1;
		cout << d / 60000 << "m | " << d / 1000 << "s | " << d << "ms" << endl;
		return result;

	}
	Node* recursiveDLS(Node* current, int limit, int depth) {
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
			current->expand();
			if (current->childs.size() == 0)
				return nullptr;
			Node* result = nullptr;
			for (Node* child : current->childs) {
				count_nodes++;
				child->parent = current;
				result = recursiveDLS(child, limit, depth + 1);
				if (result != nullptr) {
					return result;
				}
				count_nodes--;
				delete child;
			}
			return result;
		}
	}
	Node* solveRBFS() {
		Node* start = new Node(problem);
		return RBFS(start, 10e8);
	}
	Node* RBFS(Node* current, int f_limit) {
		if (isWin(current->state)) {
			if (cfg.showSolution)
				showSolution(current);
			return current;
		}
		else {
			current->expand();
			if (current->childs.size() == 0)
				return nullptr;
			for (Node* child : current->childs) {

			}
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

	void showSolution(Node* n) {
		Node* curr = n;
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

