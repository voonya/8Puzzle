#pragma once
#include "Node.h"
#include "Reader.h"
#include <iostream>
#include <stack>
class Solver
{
	vector<vector<int>> goal = {
		{0,1,2},
		{3,4,5},
		{6,7,8}
	};
	vector<vector<int>> problem;
	stack<vector<vector<int>>> solution;
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
		Node* result = recursiveDLS(start, cfg.limit, 0);
		return result;

	}
	Node* recursiveDLS(Node* current, int limit, int depth) {
		//cout << solution.size() << endl;
		if (isWin(current->state)) {
			if(cfg.showSolution)
				showSolution(current);
			return current;
		}		
		else if (depth == limit) {
			return nullptr;
		}	
		else {
			current->expand();
			Node* result = nullptr;
			//cout << endl << current->childs.size() << endl;
			//cout << endl; showMatr(current->state);
			for (Node* child : current->childs) {
				//showMatr(child->state); cout <<  endl;
				child->parent = current;
				result = recursiveDLS(child, limit, depth + 1);
				if (result != nullptr) {
					
					return result;
				}
			}
			return result;
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
	void setCfg(_CONFIG_ c) {
		cfg = c;
	}
};

