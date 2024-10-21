#include "Puzzle.h"
#include<iostream>
#include<fstream>
#include<string>
#include<utility>
#include<cstdlib>
using namespace std;
Puzzle::Puzzle()
{
	for (int k = 0; k < 4; k++)
	{
		this->matrixToFill[k] = new Matrix;
	}
	finalMatrix = new Matrix;
}
Puzzle::~Puzzle()
{
	for (int i = 0; i < 4; i++)
	{
		delete matrixToFill[i];
	}
	delete finalMatrix;
}
//"O"表示0或2，"^"表示1或3,"*"表示0
void Puzzle::displayPuzzleAndSetToMatrix()
{
	fstream f;
	//1
	char ch;
	f.open("题目1.txt", ios::out || ios::in);
	cout << "题目1如下：" << endl;
	while (f >> noskipws >> ch)
	{
		cout << ch;
		if (ch == '*')this->matrixQuestion1.push_back(make_pair(0, 0));
		else if (ch == '4')this->matrixQuestion1.push_back(make_pair(4, 4));
		else if (ch == '^')this->matrixQuestion1.push_back(make_pair(1, 3));
		else if (ch == 'O')this->matrixQuestion1.push_back(make_pair(0, 2));
	}
	f.close();
		//2
	f.open("题目2.txt", ios::out || ios::in);
	cout << "\n题目2如下：" << endl;
	while (f >> noskipws >> ch)
	{
		cout << ch;
		if (ch == '*')this->matrixQuestion2.push_back(make_pair(0, 0));
		else if (ch == '4')this->matrixQuestion2.push_back(make_pair(4, 4));
		else if (ch == '^')this->matrixQuestion2.push_back(make_pair(1, 3));
		else if (ch == 'O')this->matrixQuestion2.push_back(make_pair(0, 2));
	}
		f.close();
	//3
	f.open("题目3.txt", ios::out || ios::in);
	cout << "\n题目3如下：" << endl;
	while (f >> noskipws >> ch)
	{
		cout << ch;
		if (ch == '*')this->matrixQuestion3.push_back(make_pair(0, 0));
		else if (ch == '4')this->matrixQuestion3.push_back(make_pair(4, 4));
		else if (ch == '^')this->matrixQuestion3.push_back(make_pair(1, 3));
		else if (ch == 'O')this->matrixQuestion3.push_back(make_pair(0, 2));
	}
	f.close();
	//4
	f.open("题目4.txt", ios::out || ios::in);
	cout << "\n题目4如下：" << endl;
	while (f >> noskipws >> ch)
	{
		cout << ch;
		if (ch == '*')this->matrixQuestion4.push_back(make_pair(0, 0));
		else if (ch == '4')this->matrixQuestion4.push_back(make_pair(4, 4));
		else if (ch == '^')this->matrixQuestion4.push_back(make_pair(1, 3));
		else if (ch == 'O')this->matrixQuestion4.push_back(make_pair(0, 2));
	}
	f.close();
	//5
	f.open("题目5.txt", ios::out || ios::in);
	cout << "\n题目5如下：" << endl;
	while (f>>noskipws>>ch)
	{
		cout << ch;
		if (ch == '*')this->matrixQuestion5.push_back(make_pair(0, 0));
		else if (ch == '4')this->matrixQuestion5.push_back(make_pair(4, 4));
		else if (ch == '^')this->matrixQuestion5.push_back(make_pair(1, 3));
		else if (ch == 'O')this->matrixQuestion5.push_back(make_pair(0, 2));
	}
	f.close();
	f.open("题目6.txt", ios::out || ios::in);
	cout << "\n题目6如下：" << endl;
	while (f >> noskipws >> ch)
	{
		cout << ch;
		if (ch == '*')this->matrixQuestion6.push_back(make_pair(0, 0));
		else if (ch == '4')this->matrixQuestion6.push_back(make_pair(4, 4));
		else if (ch == '^')this->matrixQuestion6.push_back(make_pair(1, 3));
		else if (ch == 'O')this->matrixQuestion6.push_back(make_pair(0, 2));
	}
	f.close();
}
//打印自带的六个问题
void Puzzle::printMatrixQuestion(vector<pair<int, int>>& m)
{
	cout << "您选中的题目为：" << endl;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (m[i * 6 + j].first == 0 && m[i * 6 + j].second == 0)cout << '*' << " ";
			else if (m[i * 6 + j].first == 1 && m[i * 6 + j].second == 3)cout << '^' << " ";
			else if (m[i * 6 + j].first == 0 && m[i * 6 + j].second == 2)cout << 'O' << " ";
			else if (m[i * 6 + j].first == 4 && m[i * 6 + j].second == 4)cout << '4' << " ";
		}
		cout << endl;
	}
}
//检测输入的答案是否正确
bool Puzzle::checkTheAnswer(vector<pair<int,int>>m)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
				if (finalMatrix->arr[i][j] != m[i * 6 + j].first &&
					finalMatrix->arr[i][j] != m[i * 6 + j].second)
				{
					return false;
				}
		}
	}
	return true;
}
//用户输入答案
void Puzzle::inputTheAnswer()
{
	for (int i = 0; i < 4; i++)
	{
		matrixToFill[i]->setMatrixToZero();
	}
	finalMatrix->setMatrixToZero();
	for (int k = 0; k < 4; k++)
	{
		int t = 0,t1=0;
		int X1, Y1;
		int n,a[4];
		do {
			t = 0;
			cout << "请输入第" << k + 1 << "个矩阵中种树的区域（输入区域的左上角位置和和矩阵行数，其中行和列的下标从0开始）：" << endl;
			cout << "左上角位置(先输入行再输入列）：" << endl;
			cin >> X1 >> Y1;
			//判断输入的矩阵行数是否已经存在
			cout << "请输入矩阵行数（大小）：" << endl;
			cin >> n;
			for (int i = 0; i < 4; i++)
			{
				if (n == a[i])
				{
					t1 = 1;
					break;
				}
			}
			while (t1)
			{
				t1 = 0;
				cout << "您已输入过该大小的矩阵，请重新输入矩阵行数:" << endl;
				cin >> n;
				for (int i = 0; i < 4; i++)
				{
					if (n == a[i])
					{
						t1 = 1;
						break;
					}
				}

			}
			a[k] = n;
			//判断输入的矩阵是否越界
			if (X1 < 0 || Y1 < 0 || X1+n-1>5 || Y1+n-1>5)
			{
				cout << "您输入坐标与题意不符，请重新输入" << endl;
				t = 1;
			}
		} while (t);
		

		this->matrixToFill[k]->fillMatrix(X1, Y1, X1+n-1, Y1+n-1);
		printMatrixToFill(k);
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				finalMatrix->arr[i][j] += matrixToFill[k]->arr[i][j];
			}
		}
		printFinalMatrix();
	}
	cout << "您已完成答案的输入。" << endl;
}
//返回用户选择的问题
vector<pair<int, int>> Puzzle::getTheSelectedMatrixQuestion(int n)
{
	switch (n)
	{
	case 1:
		return matrixQuestion1;
	case 2:
		return matrixQuestion2;
	case 3:
		return matrixQuestion3;
	case 4:
		return matrixQuestion4;
	case 5:
		return matrixQuestion5;
	case 6:
		return matrixQuestion6;
	default:
		break;
	}
}
//
void Puzzle::userSetThePuzzle()
{
	cout << "请设置新增题目的数量：" << endl;
	int n,n0;//n0为题库中未加入新题目前的题目数量
	cin >> n;
	while (n<=0)
	{
		cout << "请重新输入有效的新增题目数量" << endl;
		cin >> n;
	}
	bool t;
	fstream f;
	string filename = "用户输入的题库.txt";
	f.open(filename, ios::in);
	string c;
	getline(f,c);
	//cout <<c<<endl;
	n0=stoi(c);
	//cout << n0 << endl;;
	c = to_string(n0+n);
	f.close();
	f.open(filename, ios::app);

	for (int i = 0; i < n; i++)
	{
		cout << "第"<<i+1<<"道新题目：" << endl;
		char buff;
		f <<"第"<< (n0+i + 1) << "题:\n";
		for (int j = 0; j < 36; j++)
		{
			do
			{
				t = true;
				cin >> buff;
				if (!(buff == '*' || buff == '^' || buff == 'O' || buff == '4'))
				{
					cout << "元素符号输入有误，请重新输入" << endl;
					t = false;
				}
			} while (t == false);
			if(buff!=' '&&buff!='\n')f << buff<<' ';

			if ((j + 1) % 6 == 0)
			{
				f << "\n";
			}
		}
	}

	f.close();
	modifyUserPuzzleFile(filename, c.c_str());//修改文件记录的题目总数
}
//
void Puzzle::displayThePuzzleOfUser()
{
	fstream f;
	f.open("玩家输入的题目.txt", ios::in);
	string word;
	cout << "用户自己出的题目：" << endl;
	while (getline(f, word, ' '))
	{
		cout << word;
	}
}
//打印matrixToFill
void Puzzle::printMatrixToFill(int n)
{
	cout << "\n输入的第" << (n + 1) << "个矩阵为：" << endl;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << this->matrixToFill[n]->arr[i][j] << " ";
		}
		cout << endl;
	}
}
//打印finalMatrix
void Puzzle::printFinalMatrix()
{
	cout << "\n当前目标矩阵为：" << endl;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << this->finalMatrix->arr[i][j] << " ";
		}
		cout << endl;
	}
}

vector<char> Puzzle::setRandomQuestion()
{
	Matrix* tempMatrix[4] = { NULL };
	for (int i = 0; i < 4; i++)
	{
		tempMatrix[i] = new Matrix;
	}		     
	Matrix*resultMatrix=new Matrix;
	srand(time(0));
	//随机产生
	int a1 = rand() % 6,a2=rand()%6;
	int b1 = rand() % 5, b2 = rand() % 5;
	int c1 = rand() % 4, c2 = rand() % 4;
	int d1 = rand() % 3, d2 = rand() % 3;
	tempMatrix[0]->fillMatrix(a1, a2, a1, a2);
	tempMatrix[1]->fillMatrix(b1, b2, b1 + 1, b2 + 1);
	tempMatrix[2]->fillMatrix(c1, c2, c1 + 2, c2 + 2);
	tempMatrix[3]->fillMatrix(d1, d2, d1 + 3, d2 + 3);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				resultMatrix->arr[i][j] += tempMatrix[k]->arr[i][j];
			}
		}
	}
	//打印随机出的表示题目的数字矩阵
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << resultMatrix->arr[i][j] << " ";
		}
		cout << endl;
	}
	//把数字矩阵转化为字符矩阵
	vector<char>resultQuestion;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			switch(resultMatrix->arr[i][j])
			{
			case 0:
				resultQuestion.push_back('*');
				break;
			case 1:
				resultQuestion.push_back('^');
				break;
			case 2:
				resultQuestion.push_back('O');//出题时字母O只表示2
				break;
			case 3:
				resultQuestion.push_back('^');
				break;
			case 4:
				resultQuestion.push_back('4');
				break;
			default:
				break;
			}
		}
	}
	//打印题目
	cout << "本次出题如下" << endl;
	for (int i = 0; i < 36; i++)
	{
		cout << resultQuestion[i] << " ";
		if ((i + 1) % 6 == 0)cout << endl;
	}
	for (int i = 0; i < 4; i++)
	{
		delete tempMatrix[i];
	}
	return resultQuestion;
}

//更改用户题库文件夹中记录的题目总数
void Puzzle::modifyUserPuzzleFile(const std::string& filename, const char* newContent) {
	// 读取原文件
	std::ifstream inFile(filename, std::ios::binary);
	if (!inFile) {
		std::cerr << "无法打开文件: " << filename << std::endl;
		return;
	}

	// 获取原文件大小
	inFile.seekg(0, std::ios::end);
	std::streampos fileSize = inFile.tellg();
	inFile.seekg(0, std::ios::beg);

	// 读取原文件内容到缓冲区
	std::vector<char> buffer(fileSize);
	inFile.read(buffer.data(), fileSize);
	inFile.close();

	// 计算新内容的长度
	size_t newContentSize = strlen(newContent);

	// 确保新内容可以放入文件的第一个位置
	if (newContentSize > fileSize) {
		std::cerr << "新内容过长，无法放入文件的起始位置" << std::endl;
		return;
	}

	// 替换缓冲区开始的部分为新内容
	std::copy(newContent, newContent + newContentSize, buffer.begin());

	// 如果新内容比原来短，保持文件其余部分不变
	if (newContentSize < fileSize) {
		// 不需要做额外操作，因为buffer的其余部分已经包含了原文件的剩余内容
	}
	else { // 这个条件实际上不会触发，因为我们已检查了新内容是否过长
		// 这里理论上应处理新内容等于或更长的情况，但根据前面的检查逻辑，这部分逻辑不会执行。
	}

	std::string combinedContent(buffer.begin(), buffer.begin() + fileSize); // 确保combinedContent的大小与原文件相同

	// 创建临时文件
	std::string tempFilename = filename + ".tmp";
	std::ofstream outFile(tempFilename, std::ios::binary);
	if (!outFile) {
		std::cerr << "无法创建临时文件: " << tempFilename << std::endl;
		return;
	}

	// 将修改后的内容写入临时文件
	outFile.write(combinedContent.c_str(), fileSize);
	outFile.close();

	// 删除原文件并重命名临时文件为原文件名
	if (remove(filename.c_str()) != 0 || rename(tempFilename.c_str(), filename.c_str()) != 0) {
		std::cerr << "替换文件时出错" << std::endl;
	}
	/*else {
		std::cout << "文件修改成功" << std::endl;
	}*/
}
vector<pair<int, int>> Puzzle::charToPair(vector<char> v)
{
	vector<pair<int, int>>a;
	vector<char>::iterator c;
	char ch;
	int i = 0;
	for (c=v.begin();c!=v.end();c++)
	{
		ch = *c;
		cout << ch << " ";
		if (ch == '*')a.push_back(make_pair(0, 0));
		else if (ch == '4')a.push_back(make_pair(4, 4));
		else if (ch == '^')a.push_back(make_pair(1, 3));
		else if (ch == 'O')a.push_back(make_pair(0, 2));
		i++;
		if (i % 6 == 0)cout << endl;
	}
	cout << "转换完成" << endl;
	return a;
}




