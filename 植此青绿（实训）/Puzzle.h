#pragma once

#include"Matrix.h"
#include<vector>
#include<utility>
using namespace std;
class Puzzle
{
public:
	Puzzle();
	~Puzzle();
	void displayPuzzleAndSetToMatrix();//展示题目和把题目所描述的矩阵保存到成员矩阵中

	void printMatrixQuestion(vector<pair<int,int>>&);//打印选中的问题

	bool checkTheAnswer(vector<pair<int, int>>) ;//根据题目检查输入的答案是否正确

	void inputTheAnswer();//输入答案

	vector<pair<int,int>> getTheSelectedMatrixQuestion(int);//返回选择的题目

	void userSetThePuzzle();//用户自己出题

	void displayThePuzzleOfUser();//展示玩家自己出的题目

	void printMatrixToFill(int);//打印matrixToFill

	void printFinalMatrix();//打印finalMatrix

	vector<char> setRandomQuestion();//随机出题

	void modifyUserPuzzleFile(const std::string& filename, const char* newContent);//用于统计用户出题题库中的题目总数

	vector<pair<int, int>> charToPair(vector<char> v);//char改为pair<int,int>
public:
	Matrix* matrixToFill[4];
	vector<pair<int,int>>matrixQuestion1;
	vector<pair<int,int>>matrixQuestion2;
	vector<pair<int, int>>matrixQuestion3;
	vector<pair<int, int>>matrixQuestion4;
	vector<pair<int, int>>matrixQuestion5;
	vector<pair<int, int>>matrixQuestion6;
	Matrix* finalMatrix;
};

