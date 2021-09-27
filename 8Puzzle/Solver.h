#pragma once
#include "Node.h"
#include "Reader.h"
#include <iostream>
#include <stack>
#include <ctime>
#include <algorithm>

class Solver
{
	// цільовий стан
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
	// проблема яку необхідно розв'язати
	vector<vector<int>> problem;
	// стек станів які призвели до розв'язання
	stack<vector<vector<int>>> solution;
	// кількість вузлів у пам'яті
	int countNodes = 0;
	// кількість створених вузлів
	int countNodesAtAll = 0;
	// кількість глухих кутів
	int deadEnds = 0;
	// кількість ітерацій алгоритму
	int iterationsCount = 0;
	// час початку роботи алгоритму
	int startTime;
	// налаштування 
	_CONFIG_ cfg;

private:
	// вирішення проблеми лімітованим пошуком вглиб
	void solveDLS();
	// рекурсивна функція лімітованого пошуку вглиб
	shared_ptr<Node> recursiveDLS(shared_ptr<Node> current, int limit, int depth);
	// вирішення проблеми рекурсивним пошуком за першим найкращим співпадінням
	void solveRBFS();
	// рекурсивна функція пошуку за першим найкращим співпадінням
	int RBFS(shared_ptr<Node> current, int f_limit, int depth);
	// перевірка чи є стан цільовим
	bool isWin(vector<vector<int>> state);
	// перевірка стану на коректність
	bool checkState();
public:
	Solver() {};

	Solver(vector<vector<int>> p) : problem(p) {};
	
	Solver(string line);
	// загальна функція вирішення проблеми
	stack<vector<vector<int>>> solve();

	//bool isSolvable(vector<vector<int>> state);
	// створення стеку станів які призвели до розв'язку
	void makeSolution(shared_ptr<Node> n);
	// встановлення проблеми
	void setProblem(vector<vector<int>> p);
	// встановлення налаштування
	void setCfg(_CONFIG_ c);
	// повернути проблему
	vector<vector<int>> getProblem() {
		return problem;
	}
};

