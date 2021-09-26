#include "Menu.h"
void Menu::start() {
	cout << " Hello! This program helps to solve 8puzzle quiz!\n";
	cout << " You can set game from file (1), or through menu (2).\n What is your choice? (1/2)\n ";
	string answer; getline(cin, answer);
	Solver solver;
	if (answer == "1") {
		solver = setGameMenuFile();
	}
	else if (answer == "2") {
		solver = setGameMenu();
	}
	else {
		cout << " Incorrect answer. Let`s try again.\n";
		exit(1);
	}
	showSolution(solver.solve());
	system("pause");
}
Solver Menu::setGameMenuFile() {
	system("cls");
	cout << " Enter the file name with extension (f.e. test.txt): ";
	string answer;
	getline(cin, answer);
	system("cls");
	cout << " Your game:\n";
	Reader reader;
	Solver solver(reader.readInitialState(answer));
	showMatr(solver.getProblem());
	setConfigMenu(solver);
	return solver;
}
Solver Menu::setGameMenu() {
	system("cls");
	cout << " Enter the game state (f.e. 123045678): ";
	string answer;
	getline(cin, answer);
	Solver solver(answer);
	system("cls");
	cout << " Your game:\n";
	showMatr(solver.getProblem());
	setConfigMenu(solver);
	return solver;
}

void Menu::setConfigMenu(Solver& solver) {
	string answer;
	Reader reader;
	cout << " You can set config from file (1), or through menu (2).\n What is your choice? (1/2)\n ";
	getline(cin, answer);
	_CONFIG_ cfg;
	if (answer == "1") {
		system("cls");
		cout << " Enter the file name with extension (f.e. test.txt): ";
		getline(cin, answer);
		cfg = reader.setConfig(answer);
	}
	else if (answer == "2") {
		system("cls");

		cout << " Enter the limit for search: ";
		getline(cin, answer);
		cfg.limit = stoi(answer);
		cout << " Enter the type of algo (LDFS, RBFS): ";
		getline(cin, answer);
		cfg.typeSearch = answer;
		cout << " Enter if you want to be showed the step-by-step solution (1-yes,0-no): ";
		getline(cin, answer);
		cfg.showSolution = stoi(answer);
	}
	else {
		cout << " Incorrect answer. Let`s try again.\n";
		exit(1);
	}
	solver.setCfg(cfg);
}
void Menu::showMatr(vector<vector<int>> state) {
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

void Menu::showSolution(stack<vector<vector<int>>> solution)
{
	while (solution.size() > 0) {
		showMatr(solution.top());
		solution.pop();
		cout << "      |\n";
		cout << "      |\n";
		cout << "     \\ /\n";
	}
}
