#pragma once
#include "Solver.h"
class Menu
{
	// ������������ �������� � �����
	Solver setGameMenuFile();
	// ������������ �������� �� ��������� ���������� ��������
	Solver setGameMenu();
	// ���� ��������� �����������
	void setConfigMenu(Solver& solver);
	// ����������� �����
	void showMatr(vector<vector<int>> state);
	// ���������� ������
	void showSolution(stack<vector<vector<int>>> s);
public:
	// �������� ����
	void start();
};

