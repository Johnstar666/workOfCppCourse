#pragma once
#include"Puzzle.h"
#include<vector>
using namespace std;
class Rank 
{
public:
	Rank();
	~Rank() {};
	void sortTheCorrectNum();//�Ӵ�С����

	void sortTheTime();//��С��������

	void sortTheComprehensiveData();//�ۺ�����

	void displayTimeRankOfCM();//��սģʽ������ʱ����

	void displayCorrectNumRankOfCM();//��սģʽ������ȷ������

	void displayComprehensiveRankOfCM();//��սģʽ������ȷ��Ŀ������������ʱ����

public:
	vector<double>correctNumRecordForCM;
	vector<double>timeRecordForCM;
	vector<pair<double, double>>comprehensiveRankRecordForCM;
};

