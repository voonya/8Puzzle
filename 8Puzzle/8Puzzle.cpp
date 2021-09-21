#include "Menu.h"




void out(vector<vector<int>> m) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

vector<vector<int>> ran() {
	vector<vector<int>> result(3, vector<int>(3));
	string nums = "012345678";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int pos = rand() % nums.length();
			result[i][j] = stoi(nums.substr(pos, 1));
			nums.erase(pos, 1);
		}
	}
	return result;
}


int main()
{
	/*Menu menu;
	menu.start();*/
	srand(time(NULL));
	Solver solver;
	solver.setCfg({ 50,"",1 });
	//solver.setProblem({ {8,2,1},{3,6,7},{4,5,0} });
	//solver.setProblem({ { 1,0,8 }, { 5,6,3 }, { 4,2,7 } });
	//cout << solver.isSolvable({ { 1,0,8 }, { 5,6,3 }, { 4,2,7 } });
	//cout << solver.isSolvable({ { 1,0,8 }, { 5,6,3 }, { 4,2,7 } });
	//solver.setProblem({ {3,0,2},{4,1,5},{6,7,8} });
	//solver.solveDLS();
	for (int i = 0; i < 10; i++) {
		vector<vector<int>> m = ran();
		out(m);
		cout << endl << solver.isSolvable(m) << endl;
		if (solver.isSolvable(m)) {
			solver.setProblem(m);
			solver.solveDLS();
		}
		
	}
	return 0;
}

