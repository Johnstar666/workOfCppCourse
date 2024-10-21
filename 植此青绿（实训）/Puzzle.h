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
	void displayPuzzleAndSetToMatrix();//չʾ��Ŀ�Ͱ���Ŀ�������ľ��󱣴浽��Ա������

	void printMatrixQuestion(vector<pair<int,int>>&);//��ӡѡ�е�����

	bool checkTheAnswer(vector<pair<int, int>>) ;//������Ŀ�������Ĵ��Ƿ���ȷ

	void inputTheAnswer();//�����

	vector<pair<int,int>> getTheSelectedMatrixQuestion(int);//����ѡ�����Ŀ

	void userSetThePuzzle();//�û��Լ�����

	void displayThePuzzleOfUser();//չʾ����Լ�������Ŀ

	void printMatrixToFill(int);//��ӡmatrixToFill

	void printFinalMatrix();//��ӡfinalMatrix

	vector<char> setRandomQuestion();//�������

	void modifyUserPuzzleFile(const std::string& filename, const char* newContent);//����ͳ���û���������е���Ŀ����

	vector<pair<int, int>> charToPair(vector<char> v);//char��Ϊpair<int,int>
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

