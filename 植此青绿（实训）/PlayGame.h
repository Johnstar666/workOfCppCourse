#pragma once
#include"Matrix.h"
#include"Puzzle.h"
#include<vector>
#include<ctime>
#include<utility>
#include"Rank.h"
#include"TextBox.h"
using namespace std;
class PlayGame
{
public:
	PlayGame();
	~PlayGame();
	void runGame();

	void chanllengeMode();//挑战模式

	bool checkIfPuzzleIsSolvable(vector<char>&);//判断题目是否可解

	void newChanllengeMode();//可视化的挑战模式

	void menu();//菜单

	void userSetPuzzle();//玩家自行出题目

	void viewRule();//查看规则

	void viewRank();//查看排行榜

	void displayAnswer(vector<char>& );//展示题目的解
public:
	Puzzle* p;
	Rank* R;
};

