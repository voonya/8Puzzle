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

//загальна фунцкія вирішення гри
stack<vector<vector<int>>> Solver::solve()
{
	startTime = clock();
	if (cfg.typeSearch == "LDFS") {
		solveDLS();
	}
	else if(cfg.typeSearch == "RBFS"){
		solveRBFS();
	}
	cout << "\n Iterations: " << count << endl;
	return solution;
}

void Solver::solveDLS() {
	shared_ptr<Node> start(new Node(problem,nullptr));
	int s1 = clock();
	if (cfg.limit < 200)
		recursiveDLS(start, cfg.limit, 0);
	else
		recursiveDLS(start, 200, 0);
	int s2 = clock();
	int d = s2 - s1;
	cout << " " << float(d) / 60000 << "m | " << float(d) / 1000 << "s | " << d << endl;
	
}
shared_ptr<Node> Solver::recursiveDLS(shared_ptr<Node> current, int limit, int depth) {
	if (((int(clock()) - startTime) / 1000 / 60) >= 30 || countNodes >= 420000) {
		cout << "Error. Can't solve it";
		exit(1);
	}
	if (isWin(current->state)) {
		makeSolution(current);
		return current;
	}
	else if (depth == limit) {
		return nullptr;
	}
	else {
		current->expand(current);
		countNodes += current->childs.size();
		countNodesAtAll += current->childs.size();
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
			countNodes--;
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
}
int Solver::RBFS(shared_ptr<Node> current, int f_limit, int depth) {
	if (((int(clock()) - startTime) / 1000 / 60) >= 30 || countNodes >= 420000) {
		cout << "Error. Can't solve it";
		exit(1);
	}
		
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
		countNodes += current->childs.size();
		countNodesAtAll += current->childs.size();
		while (true) {
			sort(current->childs.begin(), current->childs.end(), [](shared_ptr<Node> a, shared_ptr<Node> b) {
				return a->fCost < b->fCost;
				});
			shared_ptr<Node> best = current->childs[0];
			if (best->fCost > f_limit) {
				int bestDist = best->fCost;
				// якщо необхідно зберігти пам'ять, але постраждає продуктивність
				countNodes -= current->childs.size();
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