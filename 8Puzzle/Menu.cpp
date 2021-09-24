#include "Menu.h"

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
