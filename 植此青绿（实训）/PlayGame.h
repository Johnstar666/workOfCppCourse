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

	void chanllengeMode();//��սģʽ

	bool checkIfPuzzleIsSolvable(vector<char>&);//�ж���Ŀ�Ƿ�ɽ�

	void newChanllengeMode();//���ӻ�����սģʽ

	void menu();//�˵�

	void userSetPuzzle();//������г���Ŀ

	void viewRule();//�鿴����

	void viewRank();//�鿴���а�

	void displayAnswer(vector<char>& );//չʾ��Ŀ�Ľ�
public:
	Puzzle* p;
	Rank* R;
};

