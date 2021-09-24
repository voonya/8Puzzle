#include "Solver.h"

Solver::Solver(string line) {
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
stack<vector<vector<int>>> Solver::solve()
{
	if (cfg.typeSearch == "LDFS") {
		solveDLS();
	}
	else if(cfg.typeSearch == "RBFS"){
		solveRBFS();
	}
	
	return solution;
}
void Solver::solveDLS() {
	shared_ptr<Node> start(new Node(problem,nullptr));
	int s1 = clock();
	recursiveDLS(start, cfg.limit, 0);
	int s2 = clock();
	int d = s2 - s1;
	cout << " " << float(d) / 60000 << "m | " << float(d) / 1000 << "s | " << d << "ms" << endl;
	
}
shared_ptr<Node> Solver::recursiveDLS(shared_ptr<Node> current, int limit, int depth) {
	if (isWin(current->state)) {
		makeSolution(current);
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

void Solver::solveRBFS() {
	shared_ptr<Node> start(new Node(problem, nullptr));
	int s1 = clock();
	RBFS(start, 10e8, 0);
	int s2 = clock();
	int d = s2 - s1;
	cout << " " << float(d) / 60000 << "m | " << float(d) / 1000 << "s | " << d << "ms" << endl;
	makeSolution(start);
}
int Solver::RBFS(shared_ptr<Node> current, int f_limit, int depth) {
	if (isWin(current->state)) {
		if (cfg.showSolution) {
			makeSolution(current);
			return -1;
		}
	}
	else {
		if (current->childs.size() == 0)
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
	}

}
bool Solver::isWin(vector<vector<int>> state) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (state[i][j] != goal[i][j])
				return false;
		}
	}
	return true;
}

//bool Solver::isSolvable(vector<vector<int>> state) {
//	int inversionCount = getInversionsCount(state);
//	return (inversionCount % 2 == 0);
//}


void Solver::makeSolution(shared_ptr<Node> n) {
	shared_ptr<Node> curr = n;
	while (curr != nullptr) {
		solution.push(curr->state);
		curr = curr->parent;
	}
}
void Solver::setProblem(vector<vector<int>> p) {
	problem = p;
}
void Solver::setCfg(_CONFIG_ c) {
	cfg = c;
}