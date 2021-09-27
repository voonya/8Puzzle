#pragma once
#include "Solver.h"
class Menu
{
	// встановлення проблеми з файлу
	Solver setGameMenuFile();
	// встановлення проблеми за допомогою потокового введення
	Solver setGameMenu();
	// меню встановки налаштувань
	void setConfigMenu(Solver& solver);
	// відображення стану
	void showMatr(vector<vector<int>> state);
	// відобразити рішення
	void showSolution(stack<vector<vector<int>>> s);
public:
	// стартове меню
	void start();
};

