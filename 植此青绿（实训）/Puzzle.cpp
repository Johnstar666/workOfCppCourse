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
//"O"��ʾ0��2��"^"��ʾ1��3,"*"��ʾ0
void Puzzle::displayPuzzleAndSetToMatrix()
{
	fstream f;
	//1
	char ch;
	f.open("��Ŀ1.txt", ios::out || ios::in);
	cout << "��Ŀ1���£�" << endl;
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
	f.open("��Ŀ2.txt", ios::out || ios::in);
	cout << "\n��Ŀ2���£�" << endl;
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
	f.open("��Ŀ3.txt", ios::out || ios::in);
	cout << "\n��Ŀ3���£�" << endl;
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
	f.open("��Ŀ4.txt", ios::out || ios::in);
	cout << "\n��Ŀ4���£�" << endl;
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
	f.open("��Ŀ5.txt", ios::out || ios::in);
	cout << "\n��Ŀ5���£�" << endl;
	while (f>>noskipws>>ch)
	{
		cout << ch;
		if (ch == '*')this->matrixQuestion5.push_back(make_pair(0, 0));
		else if (ch == '4')this->matrixQuestion5.push_back(make_pair(4, 4));
		else if (ch == '^')this->matrixQuestion5.push_back(make_pair(1, 3));
		else if (ch == 'O')this->matrixQuestion5.push_back(make_pair(0, 2));
	}
	f.close();
	f.open("��Ŀ6.txt", ios::out || ios::in);
	cout << "\n��Ŀ6���£�" << endl;
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
//��ӡ�Դ�����������
void Puzzle::printMatrixQuestion(vector<pair<int, int>>& m)
{
	cout << "��ѡ�е���ĿΪ��" << endl;
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
//�������Ĵ��Ƿ���ȷ
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
//�û������
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
			cout << "�������" << k + 1 << "������������������������������Ͻ�λ�úͺ;��������������к��е��±��0��ʼ����" << endl;
			cout << "���Ͻ�λ��(���������������У���" << endl;
			cin >> X1 >> Y1;
			//�ж�����ľ��������Ƿ��Ѿ�����
			cout << "�����������������С����" << endl;
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
				cout << "����������ô�С�ľ��������������������:" << endl;
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
			//�ж�����ľ����Ƿ�Խ��
			if (X1 < 0 || Y1 < 0 || X1+n-1>5 || Y1+n-1>5)
			{
				cout << "���������������ⲻ��������������" << endl;
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
	cout << "������ɴ𰸵����롣" << endl;
}
//�����û�ѡ�������
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
	cout << "������������Ŀ��������" << endl;
	int n,n0;//n0Ϊ�����δ��������Ŀǰ����Ŀ����
	cin >> n;
	while (n<=0)
	{
		cout << "������������Ч��������Ŀ����" << endl;
		cin >> n;
	}
	bool t;
	fstream f;
	string filename = "�û���������.txt";
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
		cout << "��"<<i+1<<"������Ŀ��" << endl;
		char buff;
		f <<"��"<< (n0+i + 1) << "��:\n";
		for (int j = 0; j < 36; j++)
		{
			do
			{
				t = true;
				cin >> buff;
				if (!(buff == '*' || buff == '^' || buff == 'O' || buff == '4'))
				{
					cout << "Ԫ�ط���������������������" << endl;
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
	modifyUserPuzzleFile(filename, c.c_str());//�޸��ļ���¼����Ŀ����
}
//
void Puzzle::displayThePuzzleOfUser()
{
	fstream f;
	f.open("����������Ŀ.txt", ios::in);
	string word;
	cout << "�û��Լ�������Ŀ��" << endl;
	while (getline(f, word, ' '))
	{
		cout << word;
	}
}
//��ӡmatrixToFill
void Puzzle::printMatrixToFill(int n)
{
	cout << "\n����ĵ�" << (n + 1) << "������Ϊ��" << endl;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << this->matrixToFill[n]->arr[i][j] << " ";
		}
		cout << endl;
	}
}
//��ӡfinalMatrix
void Puzzle::printFinalMatrix()
{
	cout << "\n��ǰĿ�����Ϊ��" << endl;
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
	//�������
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
	//��ӡ������ı�ʾ��Ŀ�����־���
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << resultMatrix->arr[i][j] << " ";
		}
		cout << endl;
	}
	//�����־���ת��Ϊ�ַ�����
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
				resultQuestion.push_back('O');//����ʱ��ĸOֻ��ʾ2
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
	//��ӡ��Ŀ
	cout << "���γ�������" << endl;
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

//�����û�����ļ����м�¼����Ŀ����
void Puzzle::modifyUserPuzzleFile(const std::string& filename, const char* newContent) {
	// ��ȡԭ�ļ�
	std::ifstream inFile(filename, std::ios::binary);
	if (!inFile) {
		std::cerr << "�޷����ļ�: " << filename << std::endl;
		return;
	}

	// ��ȡԭ�ļ���С
	inFile.seekg(0, std::ios::end);
	std::streampos fileSize = inFile.tellg();
	inFile.seekg(0, std::ios::beg);

	// ��ȡԭ�ļ����ݵ�������
	std::vector<char> buffer(fileSize);
	inFile.read(buffer.data(), fileSize);
	inFile.close();

	// ���������ݵĳ���
	size_t newContentSize = strlen(newContent);

	// ȷ�������ݿ��Է����ļ��ĵ�һ��λ��
	if (newContentSize > fileSize) {
		std::cerr << "�����ݹ������޷������ļ�����ʼλ��" << std::endl;
		return;
	}

	// �滻��������ʼ�Ĳ���Ϊ������
	std::copy(newContent, newContent + newContentSize, buffer.begin());

	// ��������ݱ�ԭ���̣������ļ����ಿ�ֲ���
	if (newContentSize < fileSize) {
		// ����Ҫ�������������Ϊbuffer�����ಿ���Ѿ�������ԭ�ļ���ʣ������
	}
	else { // �������ʵ���ϲ��ᴥ������Ϊ�����Ѽ�����������Ƿ����
		// ����������Ӧ���������ݵ��ڻ�����������������ǰ��ļ���߼����ⲿ���߼�����ִ�С�
	}

	std::string combinedContent(buffer.begin(), buffer.begin() + fileSize); // ȷ��combinedContent�Ĵ�С��ԭ�ļ���ͬ

	// ������ʱ�ļ�
	std::string tempFilename = filename + ".tmp";
	std::ofstream outFile(tempFilename, std::ios::binary);
	if (!outFile) {
		std::cerr << "�޷�������ʱ�ļ�: " << tempFilename << std::endl;
		return;
	}

	// ���޸ĺ������д����ʱ�ļ�
	outFile.write(combinedContent.c_str(), fileSize);
	outFile.close();

	// ɾ��ԭ�ļ�����������ʱ�ļ�Ϊԭ�ļ���
	if (remove(filename.c_str()) != 0 || rename(tempFilename.c_str(), filename.c_str()) != 0) {
		std::cerr << "�滻�ļ�ʱ����" << std::endl;
	}
	/*else {
		std::cout << "�ļ��޸ĳɹ�" << std::endl;
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
	cout << "ת�����" << endl;
	return a;
}




