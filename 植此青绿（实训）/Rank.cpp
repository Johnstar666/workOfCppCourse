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

	f1.open("用时排行榜.dat", ios::in|ios::binary);
	f2.open("正确题数排行榜.dat", ios::in|ios::binary);
	f3.open("总排行榜.dat", ios::in | ios::binary);
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
	int i = 1;//用于导入文件"总排行榜"时记录数据为正确率还是用时
	double first, second;//first为正确率，second为作答用时
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
//降序条件
bool cmp1(double x, double y)
{
	return x > y;
}
//升序条件
bool cmp2(double x, double y)
{
	return x < y;
}
//对正确率排序
void Rank::sortTheCorrectNum()
{
	sort(correctNumRecordForCM.begin(), correctNumRecordForCM.end(), cmp1);
}
//对作答用时排序
void Rank::sortTheTime()
{
	sort(timeRecordForCM.begin(), timeRecordForCM.end(), cmp2);
}
//作答用时排行榜
void Rank::displayTimeRankOfCM()
{
	sortTheTime();
	outtextxy(30,100,"以下为玩家在挑战模式中作答用时排行榜（前六名，不包括正确率为零的作答用时）：");
	vector<double>::iterator ite;
	int i = 1;
	outtextxy(400, 150, "排名");
	outtextxy(460,150,"作答用时(秒)");
	for (ite = timeRecordForCM.begin();i<=6;i++)
	{
		rankDisplayDoubleAt(i, 400, 200 + (i - 1) * 50);
		if (ite != timeRecordForCM.end())
		{
			displayKeyDoubleAt(ite, 460, 200+ (i - 1) * 50,2);
			ite++;
		}
	}
	outtextxy(750,100,"其中最快用时为");
	displayKeyDoubleAt(timeRecordForCM.begin(),881,100,2);
	outtextxy(950, 100, "秒");
	
}
//正确率排行榜
void Rank::displayCorrectNumRankOfCM()
{
	sortTheCorrectNum();
	outtextxy(100, 100, "以下为玩家在挑战模式中作答正确题数排行榜（前六名）：");
	vector<double>::iterator ite;
	int i = 1;
	outtextxy(400, 150, "排名");
	outtextxy(460, 150, "正确题数");
	for (ite = correctNumRecordForCM.begin();i <= 6;i++)
	{
		rankDisplayDoubleAt(i, 400, 200 + (i - 1) * 50);
		if (ite != correctNumRecordForCM.end())
		{
			displayKeyDoubleAt(ite, 460, 200 + (i - 1) * 50, 2);
			ite++;
		}
	}
	outtextxy(700, 100, "其中正确题数最多为");
	displayKeyDoubleAt(correctNumRecordForCM.begin(), 880, 100, 2);
	outtextxy(900, 100, "题");
}
//总排行榜
void Rank::displayComprehensiveRankOfCM()
{
	sortTheComprehensiveData();
	outtextxy(100,50,"以下为玩家在挑战模式中总排行榜（前六名）：");
	vector<pair<double, double>>::iterator ite;
	int i = 1;
	outtextxy(380, 100, "排名");
	outtextxy(440, 100, "正确题数");
	outtextxy(540, 100, "作答用时(秒)");
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
	outtextxy(630, 50, "其中作答情况最好的为");
	displayFirst(comprehensiveRankRecordForCM.begin(), 820, 50, 2);
	outtextxy(840, 50, "题");
	displaySecond(comprehensiveRankRecordForCM.begin(),860,50,2);
	outtextxy(940, 50, "秒");
}
//综合数据排序条件
bool cmp3(const pair<double, double>& c1, const pair<double, double>& c2)
{
	if (c1.first != c2.first)
	{
		return c1.first > c2.first;
	}
	return c1.second < c2.second;
}
//对综合数据（正确率和用时）进行排序
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
		oss << std::fixed << std::setprecision(decimalPlaces) << it->first; // 控制小数位数
		std::string str = oss.str();
		str.erase(str.find_last_not_of('0') + 1, std::string::npos); // 移除末尾的0
		if (str.back() == '.') {
			str.pop_back(); // 如果小数点是最后一个字符，移除它
		}
		outtextxy(x, y, str.c_str()); // 在指定位置显示格式化后的数字
}
void displaySecond(std::vector<std::pair<double, double>>::iterator it, int x, int y, int decimalPlaces = 2) {
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(decimalPlaces) << it->second; // 控制小数位数
	std::string str = oss.str();
	str.erase(str.find_last_not_of('0') + 1, std::string::npos); // 移除末尾的0
	if (str.back() == '.') {
		str.pop_back(); // 如果小数点是最后一个字符，移除它
	}
	outtextxy(x, y, str.c_str()); // 在指定位置显示格式化后的数字
}


