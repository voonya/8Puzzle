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
		cout << d / 60000 << "m | " << d / 1000 << "s | " << d << "ms" << endl;
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
			/*count++;
			if(count % 10000 == 0)
				cout << Node::c << endl;*/
			current->expand();
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
				
				//delete current->childs[i];
				current->childs[i] = nullptr;
			}
			return result;
		}
	}
	/*void solveRBFS() {
		Node* start = new Node(problem);
		start->fLimit = 10e8;
		RBFS(start, 10e8, 0);
	}*/
	//int RBFS(Node* current, int f_limit, int depth) {
	//	if (isWin(current->state)) {
	//		if (cfg.showSolution) {
	//			showSolution(current);
	//		}
	//		
	//	}
	//	else {
	//		current->expand();
	//		if (current->childs.size() == 0) {
	//			return 10e8;
	//		}
	//			
	//		for (int i = 0; i < current->childs.size(); i++) {
	//			current->childs[i]->dist = current->dist + h1(current->childs[i]->state);
	//			//current->childs[i]->fLimit = max(current->childs[i]->dist, current->fLimit);
	//		}
	//		sort(current->childs.begin(), current->childs.end(), [](Node* a, Node* b) {
	//			return a->fLimit < b->fLimit;
	//			});
	//		/*while (true)
	//		{
	//			
	//			if (best->fLimit > current->fLimit) {
	//				current->fLimit = best->fLimit;
	//				return nullptr;
	//			}
	//			int alt = 10e8;
	//			if (current->childs.size() > 1)
	//				alt = current->childs[1]->fLimit;
	//			Node* result = RBFS(best, min(f_limit, alt));
	//			if (result != nullptr)
	//				return result;
	//		}*/
	//		Node* best = current->childs[0];
	//		while (best->fLimit <= f_limit && best->fLimit < 10e8) {

	//			int newFLimit;
	//			if (current->childs.size() > 1) {
	//				int alternative = current->childs[1]->fLimit;
	//				newFLimit = min(f_limit, alternative);
	//			}
	//			else {
	//				newFLimit = f_limit;
	//			}
	//			int newFCost = RBFS(best, newFLimit, depth + 1);
	//			best->fLimit = newFCost;

	//			sort(current->childs.begin(), current->childs.end(), [](Node* a, Node* b) {
	//				return a->fLimit < b->fLimit;
	//				});
	//			best = current->childs[0];
	//		}
	//		return best->fLimit;
	//	}

	//}
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
	int h1(vector<vector<int>> state) {
		int counter = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (state[i][j] != goal[i][j])
					counter++;
			}
		}
		return counter;
	}
};

