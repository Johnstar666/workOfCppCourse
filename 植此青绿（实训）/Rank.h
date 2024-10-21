#pragma once
#include"Puzzle.h"
#include<vector>
using namespace std;
class Rank 
{
public:
	Rank();
	~Rank() {};
	void sortTheCorrectNum();//从大到小排序

	void sortTheTime();//从小到大排序

	void sortTheComprehensiveData();//综合排序

	void displayTimeRankOfCM();//挑战模式作答用时排行

	void displayCorrectNumRankOfCM();//挑战模式作答正确率排行

	void displayComprehensiveRankOfCM();//挑战模式作答正确题目数量和作答用时排行

public:
	vector<double>correctNumRecordForCM;
	vector<double>timeRecordForCM;
	vector<pair<double, double>>comprehensiveRankRecordForCM;
};

