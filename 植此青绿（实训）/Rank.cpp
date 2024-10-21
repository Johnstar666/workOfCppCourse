#include "Rank.h"
#include<iomanip>
#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>
#include<vector>
#include<graphics.h>
#include<sstream>
#include<cctype>
using namespace std;
void rankDisplayDoubleAt(double,int,int);
void displayKeyDoubleAt(vector<double>::iterator,int,int,int);
void displayFirst(vector<pair<double,double>>::iterator,int,int,int);
void displaySecond(vector<pair<double, double>>::iterator, int, int, int);
Rank::Rank()
{
	fstream f1;
	fstream f2;
	fstream f3;

	f1.open("��ʱ���а�.dat", ios::in|ios::binary);
	f2.open("��ȷ�������а�.dat", ios::in|ios::binary);
	f3.open("�����а�.dat", ios::in | ios::binary);
	string line;
	double data;
	while (f1>>data)
	{
		timeRecordForCM.push_back(data);
	}
	while (f2 >> data)
	{
		correctNumRecordForCM.push_back(data);
	}
	this->sortTheCorrectNum();
	this->sortTheTime();
	int i = 1;//���ڵ����ļ�"�����а�"ʱ��¼����Ϊ��ȷ�ʻ�����ʱ
	double first, second;//firstΪ��ȷ�ʣ�secondΪ������ʱ
	while (f3 >> data)
	{
		if (i % 2 != 0)
		{
			first = data;
		}
		else if (i % 2 == 0)
		{
			second = data;
			this->comprehensiveRankRecordForCM.push_back(make_pair(first, second));
		}
		i++;
	}
	this->sortTheComprehensiveData();
	f1.close();
	f2.close();
	f3.close();
}
//��������
bool cmp1(double x, double y)
{
	return x > y;
}
//��������
bool cmp2(double x, double y)
{
	return x < y;
}
//����ȷ������
void Rank::sortTheCorrectNum()
{
	sort(correctNumRecordForCM.begin(), correctNumRecordForCM.end(), cmp1);
}
//��������ʱ����
void Rank::sortTheTime()
{
	sort(timeRecordForCM.begin(), timeRecordForCM.end(), cmp2);
}
//������ʱ���а�
void Rank::displayTimeRankOfCM()
{
	sortTheTime();
	outtextxy(30,100,"����Ϊ�������սģʽ��������ʱ���а�ǰ��������������ȷ��Ϊ���������ʱ����");
	vector<double>::iterator ite;
	int i = 1;
	outtextxy(400, 150, "����");
	outtextxy(460,150,"������ʱ(��)");
	for (ite = timeRecordForCM.begin();i<=6;i++)
	{
		rankDisplayDoubleAt(i, 400, 200 + (i - 1) * 50);
		if (ite != timeRecordForCM.end())
		{
			displayKeyDoubleAt(ite, 460, 200+ (i - 1) * 50,2);
			ite++;
		}
	}
	outtextxy(750,100,"���������ʱΪ");
	displayKeyDoubleAt(timeRecordForCM.begin(),881,100,2);
	outtextxy(950, 100, "��");
	
}
//��ȷ�����а�
void Rank::displayCorrectNumRankOfCM()
{
	sortTheCorrectNum();
	outtextxy(100, 100, "����Ϊ�������սģʽ��������ȷ�������а�ǰ��������");
	vector<double>::iterator ite;
	int i = 1;
	outtextxy(400, 150, "����");
	outtextxy(460, 150, "��ȷ����");
	for (ite = correctNumRecordForCM.begin();i <= 6;i++)
	{
		rankDisplayDoubleAt(i, 400, 200 + (i - 1) * 50);
		if (ite != correctNumRecordForCM.end())
		{
			displayKeyDoubleAt(ite, 460, 200 + (i - 1) * 50, 2);
			ite++;
		}
	}
	outtextxy(700, 100, "������ȷ�������Ϊ");
	displayKeyDoubleAt(correctNumRecordForCM.begin(), 880, 100, 2);
	outtextxy(900, 100, "��");
}
//�����а�
void Rank::displayComprehensiveRankOfCM()
{
	sortTheComprehensiveData();
	outtextxy(100,50,"����Ϊ�������սģʽ�������а�ǰ��������");
	vector<pair<double, double>>::iterator ite;
	int i = 1;
	outtextxy(380, 100, "����");
	outtextxy(440, 100, "��ȷ����");
	outtextxy(540, 100, "������ʱ(��)");
	for (ite = comprehensiveRankRecordForCM.begin(); i <= 6; i++)
	{
		rankDisplayDoubleAt(i, 380, 150 + (i - 1) * 50);
		if (ite != comprehensiveRankRecordForCM.end())
		{
			displayFirst(ite,440, 150 + (i - 1) * 50,2);
			displaySecond(ite,540, 150 + (i - 1) * 50,2);
			ite++;
		}
	}
	outtextxy(630, 50, "�������������õ�Ϊ");
	displayFirst(comprehensiveRankRecordForCM.begin(), 820, 50, 2);
	outtextxy(840, 50, "��");
	displaySecond(comprehensiveRankRecordForCM.begin(),860,50,2);
	outtextxy(940, 50, "��");
}
//�ۺ�������������
bool cmp3(const pair<double, double>& c1, const pair<double, double>& c2)
{
	if (c1.first != c2.first)
	{
		return c1.first > c2.first;
	}
	return c1.second < c2.second;
}
//���ۺ����ݣ���ȷ�ʺ���ʱ����������
void Rank::sortTheComprehensiveData()
{
	sort(comprehensiveRankRecordForCM.begin(),comprehensiveRankRecordForCM.end(),cmp3);
}
void rankDisplayDoubleAt(double value, int x, int y) {
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(std::numeric_limits<double>::max_digits10) << value;
	std::string str = oss.str();
	str.erase(str.find_last_not_of('0') + 1, std::string::npos);
	if (str.back() == '.') {
		str.pop_back(); // Remove trailing dot if it exists
	}
	//settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // Set text style as needed
	outtextxy(x, y, str.c_str()); // Display the formatted string at given coordinates
}
void displayKeyDoubleAt(std::vector<double>::iterator valueIter, int x, int y, int decimalPlaces = 2) {
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(decimalPlaces) << *valueIter; // Access and format the double using the iterator
	std::string str = oss.str();
	str.erase(str.find_last_not_of('0') + 1, std::string::npos); // Remove trailing zeros
	if (str.back() == '.') {
		str.pop_back(); // Remove trailing dot if no decimals left after removing zeros
	}
	outtextxy(x, y, str.c_str()); // Display the formatted string at given coordinates
}
void displayFirst(std::vector<std::pair<double, double>>::iterator it, int x, int y, int decimalPlaces = 2) {
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(decimalPlaces) << it->first; // ����С��λ��
		std::string str = oss.str();
		str.erase(str.find_last_not_of('0') + 1, std::string::npos); // �Ƴ�ĩβ��0
		if (str.back() == '.') {
			str.pop_back(); // ���С���������һ���ַ����Ƴ���
		}
		outtextxy(x, y, str.c_str()); // ��ָ��λ����ʾ��ʽ���������
}
void displaySecond(std::vector<std::pair<double, double>>::iterator it, int x, int y, int decimalPlaces = 2) {
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(decimalPlaces) << it->second; // ����С��λ��
	std::string str = oss.str();
	str.erase(str.find_last_not_of('0') + 1, std::string::npos); // �Ƴ�ĩβ��0
	if (str.back() == '.') {
		str.pop_back(); // ���С���������һ���ַ����Ƴ���
	}
	outtextxy(x, y, str.c_str()); // ��ָ��λ����ʾ��ʽ���������
}


