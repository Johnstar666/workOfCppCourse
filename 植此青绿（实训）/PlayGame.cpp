#include "PlayGame.h"
#include<utility>
#include<ctime>
#include<vector>
#include<fstream>
#include<iostream>
#include<graphics.h>
#include"Button.h"
#include<cctype>
#include<algorithm>
#include<sstream>
#include <iomanip>
#include<easyx.h>
#include <conio.h>
using namespace std;
//����������num�������Ļ�� outtextxy(x,y,to_string(num).c_str())
//��ʾ������
void displayDoubleAt(double, int, int);
//���ӻ���ص�ȫ�ֱ���
#define W 150
#define H 40

Button* btn1 = new Button((994 - W) / 2.0, 100, W, H, "�鿴����");
Button* btn2 = new Button((994 - W) / 2.0, 150, W, H, "��սģʽ");
Button* btn3 = new Button((994 - W) / 2.0, 200, W, H, "����ģʽ");
Button* btn4 = new Button((994 - W) / 2.0, 250, W, H, "���а�");
Button* btn5 = new Button((994 - W) / 2.0, 300, W, H, "�˳���Ϸ");
Button* btn6 = new Button(844, 686, W, H, "�������ز˵�");
Button* btn7 = new Button((994 - W) / 2.0, 100, W, H, "������ʱ���а�");
Button* btn8 = new Button((994 - W) / 2.0, 150, W, H, "��ȷ�������а�");
Button* btn9 = new Button((994 - W) / 2.0, 200, W, H, "�����а�");
Button* btn10 = new Button(794, 0, 200, H, "����������һ���˵�");	
Button* btn11 = new Button((994 - W) / 2.0, 250, W, H, "��ʼ��ս");	
Button* finishAns = new Button(50, 500, W, H, "�������");
Button* btnNext = new Button(50, 600, W, H, "��һ��");
Button* btn12 = new Button(450, 250, W, H, "����");
Button* btnRandomPuzzle = new Button((994 - W) / 2.0, 100, W, H, "�������");
Button* btnUserSetPuzzle = new Button((994 - W) / 2.0, 150, W, H, "��������");
Button* btnAnswer = new Button((994 - W) / 2.0, 250, W, H, "�������");
Button* btnBack = new Button(50, 600, W, H, "����");
Button* btnC = new Button(50, 600, W, H, "���ɽ���");
HWND hnd;

/// ///////////////
vector<TextBox*>textBoxes;//�洢������ı���
vector<Button*>buttonsForAnsweringQuestions;
//�����ı���
void drawAllTextBoxes(vector<TextBox*>&textBoxes) {
	for (TextBox* box : textBoxes) {
		box->draw();
	}
}
void drawAllTextBoxes(vector<Button*>& btns) {
	for (Button* box : btns) {
		box->show();
	}
}
// ����������¼�������Ƿ������ı������ý���
void onMouseClick(int x, int y, vector<TextBox*>& textBoxes) {
	for (TextBox* box : textBoxes) {
		if (box->checkClick(x, y)) {
			for (TextBox* otherBox : textBoxes) {
				if (otherBox != box) {
					otherBox->setSelect(false);
				}
			}
			box->setSelect(true);
			break;
		}
		
	}
}
///////////////////
PlayGame::PlayGame()
{
	this->p = new Puzzle;
	this->R = new Rank;
	
}
PlayGame::~PlayGame()
{
	delete this->p;
	delete this->R;
	delete btn1, btn2, btn3, btn4, btn5, btn6, btn7, 
		btn8, btn9,btn10,btn11,btn12,btnBack,btnC;
	delete finishAns;
	delete btnNext;
}
void PlayGame::menu()
{
	IMAGE img;
	/*Button* btn1;
	Button* btn2;
	Button* btn3;
	Button* btn4;
	Button* btn5;*/
	loadimage(&img, "./res./��ʼ����.jpg");
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);//�������屳��
	setfillcolor(CYAN);//�������ɫ��������ǳ��ɫ
	setlinecolor(BLACK); //���õ�ǰ��������ɫΪ��ɫ
	//cleardevice();//��ʾ������ɫ
	//չʾ��ť
	btn1->show();
	btn2->show();
	btn3->show();
	btn4->show();
	btn5->show();
}
void PlayGame::runGame()
{
	//������һЩ��������
	initgraph(994, 726,NOCLOSE);//��������
	HWND hnd = GetHWnd();
	settextstyle(40,0,"����");//��������
	setbkcolor(WHITE);//���ñ�����ɫ
	settextcolor(BLACK);
	menu();
	ExMessage msg;
	bool on = 1;
	double i = 1.5;
	while (on)
	{
		msg = getmessage();
		if (btn1->state(msg))		// �鿴����
		{
			viewRule();
			menu();
		}
		if (btn2->state(msg))		// ��սģʽ
		{
			this->newChanllengeMode();
			menu();
		}
		if (btn3->state(msg))		// ����ģʽ
		{
			userSetPuzzle();
			menu();
		}
		if (btn4->state(msg))		//���а�
		{
			viewRank();
			menu();
		}
		if (btn5->state(msg))		// �˳���Ϸ
		{
			exit(0);
		}
	}
	getchar();
}
//���ӻ��ĳ���ģʽ
void PlayGame::userSetPuzzle()
{
	cleardevice();//����
	IMAGE img;
	loadimage(&img, "./res./��ʼ����.jpg");
	putimage(0, 0, &img);
	ExMessage msg;
	vector<pair<int, int>>randomPuzzle;
	btn6->show();//�������ز˵�
	bool t = true,t1=true;//ѭ������
	IMAGE img0, img2, img3, img4, imgBlank, imgWin, imgLose, imgPlant;
	int x1=-1, x2=-1, x3=-1, x4=-1, y1=-1, y2=-1, y3=-1, y4=-1;//�������������
	bool judge = true;//�ж������Ƿ����
	//��������������Ŀ
	string line0;
	string line1;
	string line2;
	string line3;
	string line4;
	string line5;
	string filename = "�û���������.txt";
	fstream f;
	int nm=0;//�ļ�����Ŀ����
	int n = 0;//ѡ�����Ŀ���
	string c;//��ȡ�ļ�����Ŀ����
	/////////////
	loadimage(&img0, "./res./0.jpg", 35, 35);
	loadimage(&img2, "./res./0or2.jpg", 35, 35);
	loadimage(&img3, "./res./1or3.jpg", 35, 35);
	loadimage(&img4, "./res./4.jpg", 35, 35);
	loadimage(&imgBlank, "./res./�ո�.jpg", 35, 35);
	loadimage(&imgWin, "./res./ʤ��.jpg", 254, 83);//putimage(370, 50, &imgWin);
	loadimage(&imgLose, "./res./ʧ��.jpg");//putimage(370, 50, &imgLose);
	loadimage(&imgPlant, "./res./����.jpg", 35, 35);
	putimage(0, 0, &img);
	BeginBatchDraw();
	while (t)
	{
		cleardevice();//����
		putimage(0, 0, &img);
		msg = getmessage();/////
		btnRandomPuzzle->show();
		btnAnswer->show();
		btnUserSetPuzzle->show();
		btn6->show();//�������ز˵�
		//�������
		if (btnRandomPuzzle->state(msg))
		{
			randomPuzzle = this->p->charToPair(p->setRandomQuestion());
			t1 = true;
			while (t1)
			{
				x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
				cleardevice();//����
				putimage(0, 0, &img);
				btn10->show();
				btn12->show();
				//���ӻ�չʾ�������
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						if (randomPuzzle[i*6+j].first == 0 && randomPuzzle[i * 6 + j].second == 0)
						{
							putimage(100 + j * 35, 50 + i * 35, &img0);
						}
						else if (randomPuzzle[i * 6 + j].first == 0 && randomPuzzle[i * 6 + j].second == 2)
						{
							putimage(100 + j * 35, 50 + i * 35, &img2);
						}
						else if (randomPuzzle[i * 6 + j].first == 1 && randomPuzzle[i * 6 + j].second == 3)
						{
							putimage(100 + j * 35, 50 + i * 35, &img3);
						}
						else if (randomPuzzle[i * 6 + j].first == 4 && randomPuzzle[i * 6 + j].second == 4)
						{
							putimage(100 + j * 35, 50 + i * 35, &img4);
						}
					}
				}
				//�˳�
				msg = getmessage();
				if (btn10->state(msg))t1 =false;
				else if (btn12->state(msg))
				{
					cleardevice();
					putimage(0, 0, &img);
					//���ӻ�չʾ�������
					for (int i = 0; i < 6; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							putimage(450 + j * 35, 50 + i * 35, &imgBlank);
							putimage(450 + j * 35, 300 + i * 35, &imgBlank);
							putimage(700 + j * 35, 300 + i * 35, &imgBlank);
							putimage(700 + j * 35, 50 + i * 35, &imgBlank);
							if (randomPuzzle[i * 6 + j].first == 0 && randomPuzzle[i * 6 + j].second == 0)
							{
								putimage(100 + j * 35, 50 + i * 35, &img0);
							}
							else if (randomPuzzle[i * 6 + j].first == 0 && randomPuzzle[i * 6 + j].second == 2)
							{
								putimage(100 + j * 35, 50 + i * 35, &img2);
							}
							else if (randomPuzzle[i * 6 + j].first == 1 && randomPuzzle[i * 6 + j].second == 3)
							{
								putimage(100 + j * 35, 50 + i * 35, &img3);
							}
							else if (randomPuzzle[i * 6 + j].first == 4 && randomPuzzle[i * 6 + j].second == 4)
							{
								putimage(100 + j * 35, 50 + i * 35, &img4);
							}
						}
					}
					setfillcolor(CYAN);
					fillroundrect(450, 260, 550, 290, 1, 1);
					fillroundrect(450, 510, 550, 540, 1, 1);
					fillroundrect(700, 260, 800, 290, 1, 1);
					fillroundrect(700, 510, 800, 540, 1, 1);
					outtextxy(450, 260, "1��1");
					outtextxy(450, 510, "3��3");
					outtextxy(700, 260, "2��2");
					outtextxy(700, 510, "4��4");
					TextBox* tbx1 = new TextBox(420, 50, 30, 30, 1);
					TextBox* tbx2 = new TextBox(670, 50, 30, 30, 1);
					TextBox* tbx3 = new TextBox(420, 300, 30, 30, 1);
					TextBox* tbx4 = new TextBox(670, 300, 30, 30, 1);
					TextBox* tby1 = new TextBox(420, 100, 30, 30, 1);
					TextBox* tby2 = new TextBox(670, 100, 30, 30, 1);
					TextBox* tby3 = new TextBox(420, 350, 30, 30, 1);
					TextBox* tby4 = new TextBox(670, 350, 30, 30, 1);
					finishAns->show();//��������𡱰�ť

					textBoxes.push_back(tbx1); textBoxes.push_back(tbx2);
					textBoxes.push_back(tbx3); textBoxes.push_back(tbx4);
					textBoxes.push_back(tby1); textBoxes.push_back(tby2);
					textBoxes.push_back(tby3); textBoxes.push_back(tby4);
					drawAllTextBoxes(textBoxes);
					judge = false;//�ж������Ƿ���Ϲ���
					//�ж��Ƿ���
					while (true)
					{
						// ��ȡ����������¼�
						msg = getmessage();
						if (msg.message == WM_LBUTTONDOWN)
						{
							onMouseClick(msg.x, msg.y, textBoxes);
						}
						// ��ȡ�������������
						if (_kbhit())
						{
							wchar_t ch = _getch();
							for (TextBox* box : textBoxes)
							{
								if (box->getSelect())
								{
									box->keyInput(ch);
									box->updateCursor(); // ���¹��״̬
									break;
								}
							}
						}
						if (tbx1->getText() != "") { x1 = stoi(tbx1->getText()); };
						if (tbx2->getText() != "") { x2 = stoi(tbx2->getText()); };
						if (tbx3->getText() != "") { x3 = stoi(tbx3->getText()); };
						if (tbx4->getText() != "") { x4 = stoi(tbx4->getText()); };
						if (tby1->getText() != "") { y1 = stoi(tby1->getText()); };
						if (tby2->getText() != "") { y2 = stoi(tby2->getText()); };
						if (tby3->getText() != "") { y3 = stoi(tby3->getText()); };
						if (tby4->getText() != "") { y4 = stoi(tby4->getText()); };

						{
							if ((0 <= x1) && (x1 < 6) && (0 <= x2) && (x2 < 5) && (0 <= x3) && (x3 < 4) && (0 <= x4) && (x4 < 3) &&
								(0 <= y1) && (y1 < 6) && (0 <= y2) && (y2 < 5) && (0 <= y3) && (y3 < 4) && (0 <= y4) && (y4 < 3))
							{
								judge = true;
								cout << "judge=true" << endl;
							}
							else
							{
								judge = false;
							}
						}
						drawAllTextBoxes(textBoxes);
						FlushBatchDraw();
						//�������
						if (finishAns->state(msg))
						{
							if (judge == true)break;
							if (judge == false)MessageBox(hnd, "���𲻷��Ϲ���", "��ʾ", MB_OK | MB_ICONWARNING);
						}
					}

					btnBack->show();//չʾ���ؼ�
					//�����������õľ���
					for (int i = 0; i < 4; i++)
					{
						this->p->matrixToFill[i]->setMatrixToZero();
					}
					this->p->finalMatrix->setMatrixToZero();
					//��������������
					this->p->matrixToFill[0]->fillMatrix(x1, y1, x1, y1);
					this->p->matrixToFill[1]->fillMatrix(x2, y2, x2 + 1, y2 + 1);
					this->p->matrixToFill[2]->fillMatrix(x3, y3, x3 + 2, y3 + 2);
					this->p->matrixToFill[3]->fillMatrix(x4, y4, x4 + 3, y4 + 3);
					//�õ����վ���
					for (int i = 0; i < 6; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							for (int k = 0; k < 4; k++)
							{
								this->p->finalMatrix->arr[i][j] += this->p->matrixToFill[k]->arr[i][j];
							}
						}
					}
					//���ӻ�չʾ��������ľ���
					for (int i = 0; i < 6; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							if (this->p->matrixToFill[0]->arr[i][j] == 1)putimage(450 + j * 35, 50 + i * 35, &imgPlant);//1*1
							if (this->p->matrixToFill[1]->arr[i][j] == 1)putimage(700 + j * 35, 50 + i * 35, &imgPlant);//2*2
							if (this->p->matrixToFill[2]->arr[i][j] == 1)putimage(450 + j * 35, 300 + i * 35, &imgPlant);//3*3
							if (this->p->matrixToFill[3]->arr[i][j] == 1)putimage(700 + j * 35, 300 + i * 35, &imgPlant);//4*4
						}
					}

					if (this->p->checkTheAnswer(randomPuzzle))
					{
						putimage(480, 650, &imgWin);//��ʾ�ش���ȷ
					}
					else
					{
						putimage(480, 650, &imgLose);//��ʾ�ش����
					}
					FlushBatchDraw();
					//�˳�����
					while (true)
					{
						msg = getmessage();
						if (btnBack->state(msg))break;
						FlushBatchDraw();
					}
					//////////////
					vector<TextBox*>().swap(textBoxes);
					delete tbx1, tbx2, tbx3, tbx4, tby1, tby2, tby3, tby4;
					//�����������õľ���
					for (int i = 0; i < 4; i++)
					{
						this->p->matrixToFill[i]->setMatrixToZero();
					}
					this->p->finalMatrix->setMatrixToZero();
					
				}
				FlushBatchDraw();
			}
			
		}
		//��������
		if (btnUserSetPuzzle->state(msg))
		{
			cleardevice();
			putimage(0, 0, &img);
			TextBox* tb0 = new TextBox(450, 250, W, H, 6);
			TextBox* tb1 = new TextBox(450, 300, W, H, 6);
			TextBox* tb2 = new TextBox(450, 350, W, H, 6);
			TextBox* tb3 = new TextBox(450, 400, W, H, 6);
			TextBox* tb4 = new TextBox(450, 450, W, H, 6);
			TextBox* tb5 = new TextBox(450, 500, W, H, 6);
			vector<TextBox*>textBoxes;
			textBoxes.push_back(tb0); textBoxes.push_back(tb1);
			textBoxes.push_back(tb2); textBoxes.push_back(tb3);
			textBoxes.push_back(tb4); textBoxes.push_back(tb5);
			//���������
			drawAllTextBoxes(textBoxes);
			finishAns->show();
			btn10->show();
			//�ж��Ƿ���
			while (true)
			{
				// ��ȡ����������¼�
				msg = getmessage();
				if (msg.message == WM_LBUTTONDOWN)
				{
					onMouseClick(msg.x, msg.y, textBoxes);
				}
				// ��ȡ�������������
				if (_kbhit())
				{
					wchar_t ch = _getch();
					for (TextBox* box : textBoxes)
					{
						if (box->getSelect())
						{
							box->keyInput(ch);
							box->updateCursor(); // ���¹��״̬
							break;
						}
					}
				}
				drawAllTextBoxes(textBoxes);
				FlushBatchDraw();
				judge = true;//ѭ���˳�����
				//�������
				if (finishAns->state(msg))
				{
					//��������Ƿ����Ҫ��
					for (TextBox* tb : textBoxes)
					{
						if (tb->getText().length() == 6)
						{
							for (int i = 0; i < tb->getText().length(); i++)
							{
								if (((char)tb->getText()[i] != '*') && (char)(tb->getText()[i] != '^') &&
									((char)tb->getText()[i] != '4') && ((char)tb->getText()[i] != 'O'))
								{
									judge = false;
									break;
								}
							}
							if (judge == false)break;
						}
						else
						{
							judge = false;
							break;
						}
					}
					//�ж��Ƿ����
					if(judge==true)break;
					else
					{
						MessageBox(hnd, "���ⲻ���Ϲ�������������", "��ʾ", MB_OK | MB_ICONWARNING);
					}
				}
				if (btn10->state(msg))
				{
					judge = false;
					break;
				}
			}
			if (judge == true)
			{
				line0 = tb0->getText();
				line1 = tb1->getText();
				line2 = tb2->getText();
				line3 = tb3->getText();
				line4 = tb4->getText();
				line5 = tb5->getText();
				//��ȡ�ļ�����Ŀ����
				f.open(filename, ios::in);//���ļ�
				getline(f,c);
				n = stoi(c);//Ŀǰ��Ŀ����
				c = to_string(n+1);//�������Ŀ������һ
				f.close();//�ر��ļ�
				while (true)
				{
					btnC->show();
					msg = getmessage();
					if (btnC->state(msg))break;
					FlushBatchDraw();
				}
				//����������Ŀ�Ƿ��н�
				vector<char>v;
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						switch (i)
						{
						case 0:
							v.push_back((char)line0[j]);
							break;
						case 1:
							v.push_back((char)line1[j]);
							break;
						case 2:
							v.push_back((char)line2[j]);
							break;
						case 3:
							v.push_back((char)line3[j]);
							break;
						case 4:
							v.push_back((char)line4[j]);
							break;
						case 5:
							v.push_back((char)line5[j]);
							break;
						default:
							break;
						}
					}
				}
				if (this->checkIfPuzzleIsSolvable(v))
				{
					//����н������Ŀ¼�뵽�����
					cleardevice();
					putimage(0, 0, &img);
					setfillcolor(CYAN);
					fillroundrect(400, 0, 460, 30, 1, 1);
					outtextxy(400, 0, "�н�");

					f.open(filename, ios::app);
					f << "��" << (n + 1) << "�⣺\n";
					f << line0 << "\n";
					f << line1 << "\n";
					f << line2 << "\n";
					f << line3 << "\n";
					f << line4 << "\n";
					f << line5 << "\n";
					f.close();
					//�޸��ļ��м�¼����Ŀ����
					this->p->modifyUserPuzzleFile(filename, c.c_str());
					this->displayAnswer(v);
					FlushBatchDraw();
				}
				else
				{
					cleardevice();
					putimage(0, 0, &img);
					setfillcolor(CYAN);
					fillroundrect(400, 0, 460, 30, 1, 1);
					outtextxy(400, 0, "�޽�");
					FlushBatchDraw();
				}
				//���ؼ�
				while (true)
				{
					btn10->show();
					msg = getmessage();
					if (btn10->state(msg))break;
					FlushBatchDraw();
				}
				//�ͷ��ڴ�
				vector<TextBox*>().swap(textBoxes);
				delete tb0, tb1, tb2, tb3, tb4, tb5;
			}
		}
		
		//����
		if (btnAnswer->state(msg))
		{
			cleardevice();
			putimage(0, 0, &img);
			setfillcolor(CYAN);
			fillroundrect(440, 0, 710, 30, 1, 1);
			outtextxy(440, 0, "���Ŀǰ��");
			outtextxy(650, 0, "����");
			string c;
			fstream f;
			f.open(filename, ios::in);
			getline(f,c);
			f.close();
			outtextxy(590, 0, c.c_str());
			nm = stoi(c);//Ŀǰ��Ŀ����
			TextBox* textbox1 = new TextBox(450, 300, 120, 30, 3);//�����ı�������ֻ������һλ����
			Button* btnOK = new Button(0, 0, W, H, "ȷ���������");
			t = true;
			//�������ѡ����Ŀ
			while (t)
			{
				textbox1->draw();
				btnOK->show();
				btn10->show();
				msg = getmessage();
				int mouseX = msg.x;
				int mouseY = msg.y;
				switch (msg.message)
				{
				case WM_LBUTTONDOWN:
					textbox1->checkClick(mouseX, mouseY);
					break;
				case WM_CHAR:
					textbox1->keyInput(msg.ch);
					break;
				}
				if (textbox1->getSelect())
				{
					textbox1->updateCursor();
				}
				
				textbox1->draw();//�����ı���
				btnOK->show();//ȷ��������밴��
				//���ȷ����ͬʱ�ж������Ƿ����Ҫ��
				if (btnOK->state(msg))
				{
					bool temp=true;
					for (int i = 0; i < textbox1->getText().length(); i++)
					{
						if ((int)textbox1->getText()[i] < 48 || (int)textbox1->getText()[i]>57)
						{
							temp = false;
							break;
						}
					}
					if (temp == true)
					{
						n = stoi(textbox1->getText());//�ַ�����ת��Ϊ��������
						if (n >= 0)
						{
							//��������Ƿ���ϣ��������������Ŀ�����ı��
							if (n <= nm)
							{
								t = true;//�����������������ѭ��
								break;
							}
						}
					}
				}
				if (btn10->state(msg))
				{
					t = false;
					break;
				}
				FlushBatchDraw();
			}//�����ѭ��
			if (t == true)
			{
				cleardevice();
				putimage(0, 0, &img);
				f.open(filename, ios::in);
				vector<char>v2;
				int i = 0;
				string line;
				//
				while (getline(f, line))
				{
					++i;
					if (i >= (7 * n + 2))break;//��ȡ�������
					if (i > (7 * n - 5) && i < (7 * n + 2))
					{
						for (char ch : line)
						{
							if (ch != '\n')
							{
								v2.push_back(ch);//��ȡ��Ŀ
							}
						}
					}
				}
				f.close();//�ر��ļ���
				vector<pair<int, int>>tempM;
				tempM = this->p->charToPair(v2);
				//���ӻ�չʾ�������
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						putimage(450 + j * 35, 50 + i * 35, &imgBlank);
						putimage(450 + j * 35, 300 + i * 35, &imgBlank);
						putimage(700 + j * 35, 300 + i * 35, &imgBlank);
						putimage(700 + j * 35, 50 + i * 35, &imgBlank);
						if (tempM[i * 6 + j].first == 0 && tempM[i * 6 + j].second == 0)
						{
							putimage(100 + j * 35, 50 + i * 35, &img0);
						}
						else if (tempM[i * 6 + j].first == 0 && tempM[i * 6 + j].second == 2)
						{
							putimage(100 + j * 35, 50 + i * 35, &img2);
						}
						else if (tempM[i * 6 + j].first == 1 && tempM[i * 6 + j].second == 3)
						{
							putimage(100 + j * 35, 50 + i * 35, &img3);
						}
						else if (tempM[i * 6 + j].first == 4 && tempM[i * 6 + j].second == 4)
						{
							putimage(100 + j * 35, 50 + i * 35, &img4);
						}
					}
				}
				setfillcolor(CYAN);
				fillroundrect(450, 260, 550, 290, 1, 1);
				fillroundrect(450, 510, 550, 540, 1, 1);
				fillroundrect(700, 260, 800, 290, 1, 1);
				fillroundrect(700, 510, 800, 540, 1, 1);
				outtextxy(450, 260, "1��1");
				outtextxy(450, 510, "3��3");
				outtextxy(700, 260, "2��2");
				outtextxy(700, 510, "4��4");
				//���������
				TextBox* tbx1 = new TextBox(420, 50, 30, 30, 1);
				TextBox* tbx2 = new TextBox(670, 50, 30, 30, 1);
				TextBox* tbx3 = new TextBox(420, 300, 30, 30, 1);
				TextBox* tbx4 = new TextBox(670, 300, 30, 30, 1);
				TextBox* tby1 = new TextBox(420, 100, 30, 30, 1);
				TextBox* tby2 = new TextBox(670, 100, 30, 30, 1);
				TextBox* tby3 = new TextBox(420, 350, 30, 30, 1);
				TextBox* tby4 = new TextBox(670, 350, 30, 30, 1);
				finishAns->show();

				textBoxes.push_back(tbx1); textBoxes.push_back(tbx2);
				textBoxes.push_back(tbx3); textBoxes.push_back(tbx4);
				textBoxes.push_back(tby1); textBoxes.push_back(tby2);
				textBoxes.push_back(tby3); textBoxes.push_back(tby4);

				//�����ı���
				drawAllTextBoxes(textBoxes);

				judge = false;//�ж������Ƿ���Ϲ���
				//�ж��Ƿ���
				while (true)
				{
					// ��ȡ����������¼�
					msg = getmessage();
					if (msg.message == WM_LBUTTONDOWN)
					{
						onMouseClick(msg.x, msg.y, textBoxes);
					}
					// ��ȡ�������������
					if (_kbhit())
					{
						wchar_t ch = _getch();
						for (TextBox* box : textBoxes)
						{
							if (box->getSelect())
							{
								box->keyInput(ch);
								box->updateCursor(); // ���¹��״̬
								break;
							}
						}
					}
					if (tbx1->getText() != "") { x1 = stoi(tbx1->getText()); };
					if (tbx2->getText() != "") { x2 = stoi(tbx2->getText()); };
					if (tbx3->getText() != "") { x3 = stoi(tbx3->getText()); };
					if (tbx4->getText() != "") { x4 = stoi(tbx4->getText()); };
					if (tby1->getText() != "") { y1 = stoi(tby1->getText()); };
					if (tby2->getText() != "") { y2 = stoi(tby2->getText()); };
					if (tby3->getText() != "") { y3 = stoi(tby3->getText()); };
					if (tby4->getText() != "") { y4 = stoi(tby4->getText()); };

					{
						if ((0 <= x1) && (x1 < 6) && (0 <= x2) && (x2 < 5) && (0 <= x3) && (x3 < 4) && (0 <= x4) && (x4 < 3) &&
							(0 <= y1) && (y1 < 6) && (0 <= y2) && (y2 < 5) && (0 <= y3) && (y3 < 4) && (0 <= y4) && (y4 < 3))
						{
							judge = true;
							cout << "judge=true" << endl;
						}
						else
						{
							judge = false;
						}
					}

					if (finishAns->state(msg))
					{
						if (judge == true)break;
						if (judge == false)MessageBox(hnd, "���𲻷��Ϲ���", "��ʾ", MB_OK | MB_ICONWARNING);
					}
					drawAllTextBoxes(textBoxes);
					FlushBatchDraw();
				}
				//�����������õľ���
				for (int i = 0; i < 4; i++)
				{
					this->p->matrixToFill[i]->setMatrixToZero();
				}
				this->p->finalMatrix->setMatrixToZero();
				//��������������
				this->p->matrixToFill[0]->fillMatrix(x1, y1, x1, y1);
				this->p->matrixToFill[1]->fillMatrix(x2, y2, x2 + 1, y2 + 1);
				this->p->matrixToFill[2]->fillMatrix(x3, y3, x3 + 2, y3 + 2);
				this->p->matrixToFill[3]->fillMatrix(x4, y4, x4 + 3, y4 + 3);
				//�õ����վ���
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						for (int k = 0; k < 4; k++)
						{
							this->p->finalMatrix->arr[i][j] += this->p->matrixToFill[k]->arr[i][j];
						}
					}
				}
				//���ӻ�չʾ��������ľ���
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						if (this->p->matrixToFill[0]->arr[i][j] == 1)putimage(450 + j * 35, 50 + i * 35, &imgPlant);//1*1
						if (this->p->matrixToFill[1]->arr[i][j] == 1)putimage(700 + j * 35, 50 + i * 35, &imgPlant);//2*2
						if (this->p->matrixToFill[2]->arr[i][j] == 1)putimage(450 + j * 35, 300 + i * 35, &imgPlant);//3*3
						if (this->p->matrixToFill[3]->arr[i][j] == 1)putimage(700 + j * 35, 300 + i * 35, &imgPlant);//4*4
					}
				}

				if (this->p->checkTheAnswer(tempM))
				{
					putimage(480, 650, &imgWin);
				}
				else
				{
					putimage(480, 650, &imgLose);
				}
				//���ؼ�
				btn10->show();
				while (true)
				{
					msg = getmessage();
					if (btn10->state(msg))
					{
						break;
					}
					FlushBatchDraw();
				}
				//�����������õľ���
				for (int i = 0; i < 4; i++)
				{
					this->p->matrixToFill[i]->setMatrixToZero();
				}
				this->p->finalMatrix->setMatrixToZero();
				vector<TextBox*>().swap(textBoxes);
				vector<pair<int, int>>().swap(tempM);
				delete tbx1, tbx2, tbx3, tbx4, tby1, tby2, tby3, tby4;
				delete textbox1;
				delete btnOK;
			}
			t = true;
		}
		

		//���ؼ�
		if (btn6->state(msg))
		{
			t = false;
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
}
//���ӻ������а�
void PlayGame::viewRank()
{
	cleardevice();//����
	IMAGE img;
	loadimage(&img, "./res./��ʼ����.jpg");
	putimage(0, 0, &img);
	
	btn6->show();
	btn7->show();
	btn8->show();
	btn9->show();

	bool t = true;
	bool t1 = true;
	ExMessage msg;
	while (t)
	{
		
		msg = getmessage();
		//���ؼ�
		if (btn6->state(msg))
		{
			t = false;
		}
		//������ʱ���а�
		if (btn7->state(msg))
		{
			cleardevice();
			putimage(0, 0, &img);
			btn10->show();
			this->R->displayTimeRankOfCM();
			//���ؼ�
			t1 = true;
			while (t1)
			{
				msg = getmessage();
				if (btn10->state(msg))
				{
					t1 = false;
				}
			}
			cleardevice();
			putimage(0, 0, &img);
			btn6->show();
			btn7->show();
			btn8->show();
			btn9->show();
		}
		
		//��ȷ�������а�
		if (btn8->state(msg))
		{
			cleardevice();
			putimage(0, 0, &img);
			btn10->show();//����������һ���˵�
			this->R->displayCorrectNumRankOfCM();
			//���ؼ�
			t1 = true;
			while (t1)
			{
				msg = getmessage();
				if (btn10->state(msg))
				{
					t1 = false;
				}
			}
			cleardevice();
			putimage(0, 0, &img);
			btn6->show();
			btn7->show();
			btn8->show();
			btn9->show();
		}
		//�����а�
		if (btn9->state(msg))
		{
			cleardevice();
			putimage(0, 0, &img);
			btn10->show();
			this->R->displayComprehensiveRankOfCM();
			//���ؼ�
			t1 = true;
			while (t1)
			{
				msg = getmessage();
				if (btn10->state(msg))
				{
					t1 = false;
				}
			}
			cleardevice();
			putimage(0, 0, &img);
			btn6->show();
			btn7->show();
			btn8->show();
			btn9->show();
		}
	}
}
//���ӻ�����սģʽ----------------------------------------------------------------------------------------------
void PlayGame::newChanllengeMode()
{
	cleardevice();//����
	IMAGE img;
	IMAGE img0, img2, img3, img4, imgBlank, imgWin, imgLose, imgPlant;
	Button* btnOK = new Button(0, 0, W, H, "ȷ���������");
	loadimage(&img, "./res./��ʼ����.jpg");
	loadimage(&img0, "./res./0.jpg",35,35);
	loadimage(&img2, "./res./0or2.jpg",35,35);
	loadimage(&img3, "./res./1or3.jpg",35,35);
	loadimage(&img4, "./res./4.jpg",35,35);
	loadimage(&imgBlank, "./res./�ո�.jpg",35,35);
	loadimage(&imgWin, "./res./ʤ��.jpg",254,83);//putimage(370, 50, &imgWin);
	loadimage(&imgLose, "./res./ʧ��.jpg");//putimage(370, 50, &imgLose);
	loadimage(&imgPlant, "./res./����.jpg",35,35);
	putimage(0, 0, &img);
	ExMessage msg;
	btn6->show();
	bool t = true;
	bool temp =true;
	bool t1 = true;
	bool c = true;
	int j = 1;
	int n = 0;//ѡ�����Ŀ���
	int num[6] = { 1,2,3,4,5,6 };//�������
	clock_t startTime{};//��ʼʱ��
	clock_t endTime{};//����ʱ��
	setfillcolor(CYAN);
	fillroundrect((994 - 600) / 2.0,0, (994 - 600) / 2.0+650,30,1,1);
	outtextxy((994 - 600) / 2.0, 0, "��ģʽ��һ��Ҫ�������������ѡȡ���������𣬻��¼������ʱ����ȷ����");
	btn11->show();
	vector<pair<int, int>>tempMatrix;//�������
	p->displayPuzzleAndSetToMatrix();
	int x1, x2, x3, x4, y1, y2, y3, y4;//�������������

	bool judge=false;//�ж������Ƿ����
	int count=0;//������Ŀ��ȷ�Ĵ���
	double duration = 0;//������ʱ��
	double correctNum = 0;
	while (t)
	{
		cleardevice();
		loadimage(&img, "./res./��ʼ����.jpg");
		putimage(0, 0, &img);
		
		setfillcolor(CYAN);
		fillroundrect((994 - 600) / 2.0, 0, (994 - 600) / 2.0 + 680, 60, 1, 1);
		outtextxy((994 - 600) / 2.0, 0, "��ģʽ��һ��Ҫ�������������ѡȡ���������𣬻��¼������ʱ����ȷ����");
		outtextxy((994 - 600) / 2.0, 30, "ע�⣺����ʱ�Ϸ�Ϊ�������Ͻ�����ţ��·�Ϊ�������Ͻ�����ţ���Ŵ�0��ʼ");
		btn6->show();
		btn11->show();
		msg = getmessage();
		t1 = true;
		string s = "��ѡ�����";
		while (t1)
		{
			msg = getmessage();
			temp = true;
			//��ʼ��ս
			if (btn11->state(msg))
			{
				while (j <= 3 && temp == true)
				{
					x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
					msg = getmessage();
					cleardevice();
					loadimage(&img, "./res./��ʼ����.jpg");
					putimage(0, 0, &img);
					setfillcolor(CYAN);
					fillroundrect((994 - 600) / 2.0 + 100, 0, (994 - 600) / 2.0 + 650 - 100, 30, 1, 1);
					displayDoubleAt(j, (994 - 10) / 2.0, 0);
					//ѡ����ţ������ظ���
					TextBox* textbox1 = new TextBox(450, 300, 120, 30, 1);//�����ı�������ֻ������һλ����
					BeginBatchDraw();
					c = true;
					while (c)
					{
						
						outtextxy(455, 252, s.c_str());
						textbox1->draw();
						btnOK->show();
						msg = getmessage();
						int mouseX = msg.x;
						int mouseY = msg.y;
						switch (msg.message)
						{
						case WM_LBUTTONDOWN:
							textbox1->checkClick(mouseX, mouseY);
							break;
						case WM_CHAR:
							textbox1->keyInput(msg.ch);
							break;
						}
						if (textbox1->getSelect())
						{
							textbox1->updateCursor();
						}
						n = (int)(static_cast<int>((textbox1->getText())[0]) - '0');//�ַ�����ת��Ϊ��������
						textbox1->draw();//�����ı���
						btnOK->show();//ȷ��������밴��
						//���ȷ����ͬʱ�ж������Ƿ����Ҫ��
						if (btnOK->state(msg))
						{
							if (n != 0)
							{
								//��������Ƿ���ϣ����������ظ��ı��&��������1~6֮��ı��
								for (int i = 0; i < 6; i++)
								{
									if (n == num[i])
									{
										num[i] = 0;
										c = false;//�����������������ѭ��
										break;
									}
								}
							}
						}
						FlushBatchDraw();
					}//�����ѭ��
					EndBatchDraw();
					
					cleardevice();
					putimage(0, 0, &img);
					setfillcolor(CYAN);
					fillroundrect((994 - 600) / 2.0 + 100, 0, (994 - 600) / 2.0 + 650 - 100, 30, 1, 1);
					displayDoubleAt(j, (994 - 10) / 2.0, 0);
					cout << n << endl;
					tempMatrix = p->getTheSelectedMatrixQuestion(n);
					this->p->printMatrixQuestion(tempMatrix);/////////////
					//���ӻ�չʾ�������
					for (int i = 0; i < 6; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							putimage(450 + j * 35, 50 + i * 35, &imgBlank);
							putimage(450 + j * 35, 300 + i * 35, &imgBlank);
							putimage(700 + j * 35, 300 + i * 35, &imgBlank);
							putimage(700 + j * 35, 50 + i * 35, &imgBlank);
							if (tempMatrix[i * 6 + j].first == 0 && tempMatrix[i * 6 + j].second == 0)
							{
								putimage(100+j*35, 50+i*35, &img0);
							}
							else if (tempMatrix[i * 6 + j].first == 0 && tempMatrix[i * 6 + j].second == 2)
							{
								putimage(100+j*35, 50+i*35, &img2);
							}
							else if (tempMatrix[i * 6 + j].first == 1 && tempMatrix[i * 6 + j].second == 3)
							{
								putimage(100+j*35, 50+i*35, &img3);
							}
							else if (tempMatrix[i * 6 + j].first == 4 && tempMatrix[i * 6 + j].second == 4)
							{
								putimage(100+j*35, 50+i*35, &img4);
							}
						}
					}
					fillroundrect(450, 260,550,290,1, 1);
					fillroundrect(450, 510, 550,540, 1, 1);
					fillroundrect(700, 260,800,290, 1, 1);
					fillroundrect(700, 510,800,540, 1, 1);
					outtextxy(450, 260, "1��1");
					outtextxy(450, 510, "3��3");
					outtextxy(700, 260, "2��2");
					outtextxy(700, 510, "4��4");
					//���������
					TextBox* tbx1 = new TextBox(420, 50, 30, 30, 1); 
					TextBox* tbx2 = new TextBox(670, 50, 30, 30, 1); 
					TextBox* tbx3 = new TextBox(420, 300, 30, 30, 1);
					TextBox* tbx4 = new TextBox(670, 300, 30, 30, 1);
					TextBox* tby1 = new TextBox(420, 100, 30, 30, 1); 
					TextBox* tby2 = new TextBox(670, 100, 30, 30, 1); 
					TextBox* tby3 = new TextBox(420, 350, 30, 30, 1); 
					TextBox* tby4 = new TextBox(670, 350, 30, 30, 1); 
					finishAns->show();

					textBoxes.push_back(tbx1); textBoxes.push_back(tbx2); 
					textBoxes.push_back(tbx3); textBoxes.push_back(tbx4);
					textBoxes.push_back(tby1); textBoxes.push_back(tby2);
					textBoxes.push_back(tby3); textBoxes.push_back(tby4);
					
					//�����ı���
					drawAllTextBoxes(textBoxes);

					judge = false;//�ж������Ƿ���Ϲ���
					startTime = clock();//��¼��ʼʱ��
					//�ж��Ƿ���
					BeginBatchDraw();
					while (true)
					{
						// ��ȡ����������¼�
						msg = getmessage();
						if (msg.message == WM_LBUTTONDOWN) 
						{
							onMouseClick(msg.x, msg.y, textBoxes);
						}
						// ��ȡ�������������
						if (_kbhit()) 
						{
							wchar_t ch = _getch();
							for (TextBox* box : textBoxes) 
							{
								if (box->getSelect()) 
								{
									box->keyInput(ch);
									box->updateCursor(); // ���¹��״̬
									break;
								}
							}
						}
						if (tbx1->getText() != "") { x1 = stoi(tbx1->getText()); };
						if (tbx2->getText() != "") { x2 = stoi(tbx2->getText()); };
						if (tbx3->getText() != "") { x3 = stoi(tbx3->getText()); };
						if (tbx4->getText() != "") { x4 = stoi(tbx4->getText()); };
						if (tby1->getText() != "") { y1 = stoi(tby1->getText()); };
						if (tby2->getText() != "") { y2 = stoi(tby2->getText()); };
						if (tby3->getText() != "") { y3 = stoi(tby3->getText()); };
						if (tby4->getText() != "") { y4 = stoi(tby4->getText()); };
						
						{
							if ((0 <=x1)&&( x1 < 6) && (0<=x2)&&( x2 < 5) && (0<= x3)&&(x3 < 4) && (0 <= x4)&&(x4 < 3) &&
								(0 <= y1) && (y1 < 6) && (0 <= y2) && (y2 < 5) && (0 <= y3) && (y3 < 4) && (0 <= y4)&&(y4 < 3))
							{
								judge = true;
								cout << "judge=true" << endl;
							}
							else
							{
								judge = false;
							}
						}
						
						if (finishAns->state(msg)) 
						{
							if(judge==true)break;
							if (judge == false)MessageBox(hnd,"���𲻷��Ϲ���","��ʾ", MB_OK | MB_ICONWARNING);
						}
						drawAllTextBoxes(textBoxes);
						FlushBatchDraw();
					}
					EndBatchDraw();
					endTime = clock();//��¼�������ʱ��
					duration += (double)(endTime - startTime)/ CLOCKS_PER_SEC;//����ʱ��Ϊ��������ʱ��ĺ�
					//�����������õľ���
					for (int i = 0; i < 4; i++)
					{
						this->p->matrixToFill[i]->setMatrixToZero();
					}
					this->p->finalMatrix->setMatrixToZero();
					//��������������
					this->p->matrixToFill[0]->fillMatrix(x1, y1, x1, y1);
					this->p->matrixToFill[1]->fillMatrix(x2, y2, x2 + 1, y2 + 1);
					this->p->matrixToFill[2]->fillMatrix(x3, y3, x3 + 2, y3 + 2);
					this->p->matrixToFill[3]->fillMatrix(x4, y4, x4 + 3, y4 + 3);
					//�õ����վ���
					for (int i = 0; i < 6; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							for (int k = 0; k < 4; k++)
							{
								this->p->finalMatrix->arr[i][j] += this->p->matrixToFill[k]->arr[i][j];
							}
						}
					}
					//���ӻ�չʾ��������ľ���
					for (int i = 0; i < 6; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							if (this->p->matrixToFill[0]->arr[i][j] == 1)putimage(450 + j * 35, 50 + i * 35, &imgPlant);//1*1
							if (this->p->matrixToFill[1]->arr[i][j] == 1)putimage(700 + j * 35, 50 + i * 35, &imgPlant);//2*2
							if (this->p->matrixToFill[2]->arr[i][j] == 1)putimage(450 + j * 35, 300 + i * 35, &imgPlant);//3*3
							if (this->p->matrixToFill[3]->arr[i][j] == 1)putimage(700 + j * 35, 300 + i * 35, &imgPlant);//4*4
						}
					}
					
					if (this->p->checkTheAnswer(tempMatrix))
					{
						putimage(480, 650, &imgWin);
						count++;//������ȷ�Ĵ�����һ
					}
					else
					{
						putimage(480, 650, &imgLose);
					}
					
					j++;//������ɺ󣬴����������һ��
					vector<TextBox*>().swap(textBoxes);
					delete textbox1;
					delete tbx1, tbx2, tbx3, tbx4,tby1,tby2,tby3,tby4;
					btnNext->show();
					while (true)
					{
						msg = getmessage();
						if (btnNext->state(msg))break;
					}
				}
				//////////////////////////////
				fstream f1;
				fstream f2;
				fstream f3;
				f1.open("��ʱ���а�.dat", ios::app | ios::binary);
				f2.open("��ȷ�������а�.dat", ios::app | ios::binary);
				f3.open("�����а�.dat", ios::app | ios::binary);
				correctNum = count;
				this->R->comprehensiveRankRecordForCM.push_back(make_pair(correctNum, duration));
				this->R->correctNumRecordForCM.push_back(correctNum);
				if (correctNum > 0)this->R->timeRecordForCM.push_back(duration);
				//����������ݱ��浽�������ļ���
				f1 << duration << "\n";
				f2 << correctNum << "\n";
				f3 << correctNum << "\t" << duration << "\n";
				f1.close();
				f2.close();
				f3.close();
				//����
				this->R->sortTheCorrectNum();
				this->R->sortTheTime();
				////////////////////////
				cleardevice();
				loadimage(&img, "./res./��ʼ����.jpg");
				putimage(0, 0, &img);
				outtextxy(250, 100, "����������");
				displayDoubleAt(correctNum, 400, 100);
				outtextxy(450, 100, "���⣬��ʱΪ");
				displayDoubleAt(duration, 600, 100);
				outtextxy(700, 100, "��");
				//���ؼ�
				btn6->show();
				t = true;
				while (t)
				{
					msg = getmessage();
					if (btn6->state(msg))
					{
						t = false;
						t1 = false;//��սģʽ�������������˵�
					}
				}
			}
			if (btn6->state(msg))
			{
				t1 = false;
				t = false;
			}
		}
	}
}
//��սģʽ-------------------------------------------------------------------------
void PlayGame::chanllengeMode()
{
	fstream f1;
	fstream f2;
	fstream f3;
	f1.open("��ʱ���а�.dat", ios::app | ios::binary);
	f2.open("��ȷ�������а�.dat", ios::app | ios::binary);
	f3.open("�����а�.dat", ios::app | ios::binary);
	bool t;
	int i = 0;
	int a[3] = {0};
	int count=0;
	clock_t startTime{};
	clock_t endTime{};
	p->displayPuzzleAndSetToMatrix();
	vector<pair<int, int>>tempMatrix;
	while (i<1)
	{
		//ѡ����Ŀ
		std::cout << "\n��������ѡ�����Ŀ�����(�������1~5֮��)��" << endl;
		startTime = clock();//��¼��ʼʱ��
		int n;
		cin >> n;
		while (n < 1 || n>6)
		{
			std::cout << "���޴����⣬������ѡ����Ŀ��" << endl;
			cin >> n;
		}
		do
		{
			t = true;
			//�ж��Ƿ��Ѿ������������Ŀ��ű�ʾ����Ŀ
			for (int j = 0; j < 3; j++)
			{
				if (a[j] == n)
				{
					t = false;
					break;
				}
			}
			switch (t)
			{
			case false:
				std::cout << "����������"<<n<<"���⣬��ѡ��δ��������Ŀ�ı�ţ�" << endl;
				cin >> n;
				break;
			case true:
				std::cout << "���ѳɹ�ѡ����Ŀ" << endl;
				break;
			}
		} while (!t);
		a[i] = n;//��ѡ�������Ŀ��ű��浽�����У��Ա�����ж�
		tempMatrix = p->getTheSelectedMatrixQuestion(n);
		p->printMatrixQuestion(tempMatrix);
		//�����
		std::cout << "���ڿ�ʼ�������Ĵ𰸣�" << endl;
		p->inputTheAnswer();
		//��¼����ʱ��
		if (i == 0)endTime = clock();
		//�����Ƿ���ȷ
		switch (p->checkTheAnswer(tempMatrix))
		{
		case true:
			std::cout << "��ϲ���ش���ȷ��" << endl;
			count++;
			break;
		case false:
			std::cout << "���ź������ش����" << endl;
			break;
		}
		i++;
	}
	/*cout << "�����ε�����˳��Ϊ��";
	for (int b = 0; b < 5; b++)
	{
		cout << a[b] << " ";
	}*/
	double correctNum = count;
	std::cout << "\n������սģʽ�����������" << count << "���⣬�����" << (3 - count) << "����,��ȷ����Ϊ"<<correctNum<< endl;
	double duration = (double)(endTime-startTime)/CLOCKS_PER_SEC;//������ʱ��
	std::cout << "������ս��ʱΪ" << duration << "��" << endl;
	std::cout << "�������һ����սģʽ" << endl;
	this->R->comprehensiveRankRecordForCM.push_back(make_pair(correctNum, duration));
	this->R->correctNumRecordForCM.push_back(correctNum);
	if(correctNum>0)this->R->timeRecordForCM.push_back(duration);
	//����������ݱ��浽�������ļ���
	f1 << duration << "\n";
	f2 << correctNum << "\n";
	f3 << correctNum << "\t" << duration<<"\n";
	f1.close();
	f2.close();
	f3.close();
	//����
	this->R->sortTheCorrectNum();
	this->R->sortTheTime();
	//չʾ���а�
	this->R->displayCorrectNumRankOfCM();
	this->R->displayTimeRankOfCM();
	this->R->displayComprehensiveRankOfCM();
}
//------------------------------------------------------------------------------------------------------------------------------------
void PlayGame::viewRule()
{
	cleardevice();//����
	settextcolor(BLACK);
	IMAGE img;
	IMAGE img1;
	IMAGE img2;
	IMAGE img3;
	IMAGE img4;
	loadimage(&img, "./res./��ʼ����.jpg");
	loadimage(&img1, "./res./0.jpg",65,65);
	loadimage(&img2, "./res./0or2.jpg",65,65);
	loadimage(&img3, "./res./1or3.jpg",65,65);
	loadimage(&img4, "./res./4.jpg",65,65);
	putimage(0, 0, &img);
	putimage((994 - W) / 2.0, 100, &img1);
	putimage((994 - W) / 2.0, 170, &img2);
	putimage((994 - W) / 2.0, 240, &img3);
	putimage((994 - W) / 2.0, 310, &img4);
	outtextxy((994 - W) / 2.0+70, 100,"��ʾ��λ�ò���Ҫֲ��");
	outtextxy((994 - W) / 2.0 + 70, 170, "��ʾ��λ����Ҫ0��2��ֲ��");
	outtextxy((994 - W) / 2.0 + 70, 240, "��ʾ��λ����Ҫ1��3ֲ��");
	outtextxy((994 - W) / 2.0 + 70, 310, "��ʾ��λ����Ҫ4ֲ��");
	outtextxy(0,0,"��Ŀ��Ϊ6��6�ľ���ÿ��λ����һ��ͼ����������ʾ��������Ҫ��4���յ�6��6�����еĶ�Ӧ��λ��");
	outtextxy(0,20, "�ֱ�����1��1��2��2��3��3��4��4�ľ���(����Ӧ����ֲ��)ʹ��4������ĺ�������ĿҪ��");
	ExMessage msg;
	btn6 = new Button(844, 686, W, H, "�������ز˵�");
	btn6->show();
	bool t = true;
	while (t)
	{
		msg = getmessage();
		//���ؼ�
		if (btn6->state(msg))
		{
			t = false;
		}
	}
}

bool PlayGame::checkIfPuzzleIsSolvable(vector<char>&c)
{
	Matrix* tempMatrix[4] = {NULL,NULL,NULL,NULL};
	for (int i = 0; i < 4; i++)
	{
		tempMatrix[i] = new Matrix;
	}
	Matrix* tMatrix = new Matrix;

	vector<pair<int, int>>m;
	for (int i = 0; i < 36; i++)
	{
		if (c[i] == '*')m.push_back(make_pair(0, 0));
		else if (c[i] == '^')m.push_back(make_pair(1, 3));
		else if (c[i] == 'O')m.push_back(make_pair(0, 2));
		else if (c[i] == '4')m.push_back(make_pair(4, 4));
	}

	//�����鿴�Ƿ��н�
	int t = 0;//��ֹ�ж�
	bool res=false;//�жϽ��
	for (int a1 = 0; a1 < 6; a1++)
	{
		for (int a2 = 0; a2 < 6; a2++)
		{
			tempMatrix[0]->setMatrixToZero();
			tempMatrix[0]->fillMatrix(a1, a2, a1, a2);
			for (int b1 = 0; b1 < 5; b1++)
			{
				for (int b2 = 0; b2 < 5; b2++)
				{
					tempMatrix[1]->setMatrixToZero();
					tempMatrix[1]->fillMatrix(b1, b2, b1 + 1, b2 + 1);
					for (int c1 = 0; c1 < 4; c1++)
					{
						for (int c2 = 0; c2 < 4; c2++)
						{
							tempMatrix[2]->setMatrixToZero();
							tempMatrix[2]->fillMatrix(c1, c2, c1 + 2, c2 + 2);
							for (int d1 = 0; d1 < 3; d1++)
							{
								for (int d2 = 0; d2 < 3; d2++)
								{
									tempMatrix[3]->setMatrixToZero();
									tMatrix->setMatrixToZero();
									tempMatrix[3]->fillMatrix(d1, d2, d1 + 3, d2 + 3);
									//�ĸ��������
									for (int i = 0; i < 6; i++)
									{
										for (int j = 0; j < 6; j++)
										{
											for (int k = 0; k < 4; k++)
											{
												tMatrix->arr[i][j] += tempMatrix[k]->arr[i][j];
											}
										}
									}
									//�ж��Ƿ������Ŀ
									t = 0;
									for (int i = 0; i < 6; i++)
									{
										for (int j = 0; j < 6; j++)
										{
											if (!(tMatrix->arr[i][j] == m[i * 6 + j].first || tMatrix->arr[i][j] == m[i * 6 + j].second))
												{
													t = 1;
													break;
												}
										}
										if (t == 1)break;
									}
									if (t == 0)res= true;
									if (res == true)break;
								}
								if (res == true)break;
							}
							if (res == true)break;
						}
						if (res == true)break;
					}
					if (res == true)break;
				}
				if (res == true)break;
			}
			if (res == true)break;
		}
		if (res == true)break;
	}
	for (int i = 0; i < 4; i++)
	{
		delete tempMatrix[i];
	}
	delete tMatrix;
	switch (res)
	{
	case true:
		return true;
	case false:
		return false;
	}
}
void PlayGame::displayAnswer(vector<char>& c)
{
	Matrix* tempMatrix[4] = { NULL,NULL,NULL,NULL };
	for (int i = 0; i < 4; i++)
	{
		tempMatrix[i] = new Matrix;
	}
	Matrix* tMatrix = new Matrix;

	vector<pair<int, int>>m;
	m = this->p->charToPair(c);

	//�����鿴�Ƿ��н�
	int t = 0;//��ֹ�ж�
	bool res = false;//�жϽ��
	for (int a1 = 0; a1 < 6; a1++)
	{
		for (int a2 = 0; a2 < 6; a2++)
		{
			tempMatrix[0]->setMatrixToZero();
			tempMatrix[0]->fillMatrix(a1, a2, a1, a2);
			for (int b1 = 0; b1 < 5; b1++)
			{
				for (int b2 = 0; b2 < 5; b2++)
				{
					tempMatrix[1]->setMatrixToZero();
					tempMatrix[1]->fillMatrix(b1, b2, b1 + 1, b2 + 1);
					for (int c1 = 0; c1 < 4; c1++)
					{
						for (int c2 = 0; c2 < 4; c2++)
						{
							tempMatrix[2]->setMatrixToZero();
							tempMatrix[2]->fillMatrix(c1, c2, c1 + 2, c2 + 2);
							for (int d1 = 0; d1 < 3; d1++)
							{
								for (int d2 = 0; d2 < 3; d2++)
								{
									tempMatrix[3]->setMatrixToZero();
									tMatrix->setMatrixToZero();
									tempMatrix[3]->fillMatrix(d1, d2, d1 + 3, d2 + 3);
									//�ĸ��������
									for (int i = 0; i < 6; i++)
									{
										for (int j = 0; j < 6; j++)
										{
											for (int k = 0; k < 4; k++)
											{
												tMatrix->arr[i][j] += tempMatrix[k]->arr[i][j];
											}
										}
									}
									//�ж��Ƿ������Ŀ
									t = 0;
									for (int i = 0; i < 6; i++)
									{
										for (int j = 0; j < 6; j++)
										{
											if (!(tMatrix->arr[i][j] == m[i * 6 + j].first || tMatrix->arr[i][j] == m[i * 6 + j].second))
											{
												t = 1;
												break;
											}
										}
										if (t == 1)break;
									}
									if (t == 0)res = true;
									if (res == true)break;
								}
								if (res == true)break;
							}
							if (res == true)break;
						}
						if (res == true)break;
					}
					if (res == true)break;
				}
				if (res == true)break;
			}
			if (res == true)break;
		}
		if (res == true)break;
	}
	//չʾ��Ŀ�Ľ��
	IMAGE img0, img2, img3, img4, imgBlank, imgWin, imgLose, imgPlant;
	loadimage(&img0, "./res./0.jpg", 35, 35);
	loadimage(&img2, "./res./0or2.jpg", 35, 35);
	loadimage(&img3, "./res./1or3.jpg", 35, 35);
	loadimage(&img4, "./res./4.jpg", 35, 35);
	loadimage(&imgBlank, "./res./�ո�.jpg", 35, 35);
	loadimage(&imgWin, "./res./ʤ��.jpg", 254, 83);//putimage(370, 50, &imgWin);
	loadimage(&imgLose, "./res./ʧ��.jpg");//putimage(370, 50, &imgLose);
	loadimage(&imgPlant, "./res./����.jpg", 35, 35);
	vector<pair<int, int>>puz;
	puz = this->p->charToPair(c);
	//���ӻ�չʾ�������
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			putimage(450 + j * 35, 50 + i * 35, &imgBlank);
			putimage(450 + j * 35, 300 + i * 35, &imgBlank);
			putimage(700 + j * 35, 300 + i * 35, &imgBlank);
			putimage(700 + j * 35, 50 + i * 35, &imgBlank);
			if (puz[i * 6 + j].first == 0 && puz[i * 6 + j].second == 0)
			{
				putimage(100 + j * 35, 50 + i * 35, &img0);
			}
			else if (puz[i * 6 + j].first == 0 &&puz[i * 6 + j].second == 2)
			{
				putimage(100 + j * 35, 50 + i * 35, &img2);
			}
			else if (puz[i * 6 + j].first == 1 && puz[i * 6 + j].second == 3)
			{
				putimage(100 + j * 35, 50 + i * 35, &img3);
			}
			else if (puz[i * 6 + j].first == 4 && puz[i * 6 + j].second == 4)
			{
				putimage(100 + j * 35, 50 + i * 35, &img4);
			}
		}
	}
	//���ӻ�չʾ��
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (tempMatrix[0]->arr[i][j] == 1)putimage(450 + j * 35, 50 + i * 35, &imgPlant);//1*1
			if (tempMatrix[1]->arr[i][j] == 1)putimage(700 + j * 35, 50 + i * 35, &imgPlant);//2*2
			if (tempMatrix[2]->arr[i][j] == 1)putimage(450 + j * 35, 300 + i * 35, &imgPlant);//3*3
			if (tempMatrix[3]->arr[i][j] == 1)putimage(700 + j * 35, 300 + i * 35, &imgPlant);//4*4
		}
	}
	//�ͷ��ڴ�
	for (int i = 0; i < 4; i++)
	{
		delete tempMatrix[i];
	}
	delete tMatrix;
}
void displayDoubleAt(double value, int x, int y) {
	std::ostringstream oss;
	//oss << std::fixed << std::setprecision(std::numeric_limits<double>::max_digits10) << value;
	oss << std::fixed << std::setprecision(2) << value;
	std::string str = oss.str();
	str.erase(str.find_last_not_of('0') + 1, std::string::npos);
	if (str.back() == '.') {
		str.pop_back(); // Remove trailing dot if it exists
	}
	//settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // Set text style as needed
	outtextxy(x, y, str.c_str()); // Display the formatted string at given coordinates
}




