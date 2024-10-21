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
//把整形数字num输出到屏幕上 outtextxy(x,y,to_string(num).c_str())
//显示浮点数
void displayDoubleAt(double, int, int);
//可视化相关的全局变量
#define W 150
#define H 40

Button* btn1 = new Button((994 - W) / 2.0, 100, W, H, "查看规则");
Button* btn2 = new Button((994 - W) / 2.0, 150, W, H, "挑战模式");
Button* btn3 = new Button((994 - W) / 2.0, 200, W, H, "出题模式");
Button* btn4 = new Button((994 - W) / 2.0, 250, W, H, "排行榜");
Button* btn5 = new Button((994 - W) / 2.0, 300, W, H, "退出游戏");
Button* btn6 = new Button(844, 686, W, H, "结束返回菜单");
Button* btn7 = new Button((994 - W) / 2.0, 100, W, H, "作答用时排行榜");
Button* btn8 = new Button((994 - W) / 2.0, 150, W, H, "正确题数排行榜");
Button* btn9 = new Button((994 - W) / 2.0, 200, W, H, "总排行榜");
Button* btn10 = new Button(794, 0, 200, H, "结束返回上一级菜单");	
Button* btn11 = new Button((994 - W) / 2.0, 250, W, H, "开始挑战");	
Button* finishAns = new Button(50, 500, W, H, "完成输入");
Button* btnNext = new Button(50, 600, W, H, "下一题");
Button* btn12 = new Button(450, 250, W, H, "作答");
Button* btnRandomPuzzle = new Button((994 - W) / 2.0, 100, W, H, "随机出题");
Button* btnUserSetPuzzle = new Button((994 - W) / 2.0, 150, W, H, "自主出题");
Button* btnAnswer = new Button((994 - W) / 2.0, 250, W, H, "题库作答");
Button* btnBack = new Button(50, 600, W, H, "返回");
Button* btnC = new Button(50, 600, W, H, "看可解性");
HWND hnd;

/// ///////////////
vector<TextBox*>textBoxes;//存储作答的文本框
vector<Button*>buttonsForAnsweringQuestions;
//绘制文本框
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
// 处理鼠标点击事件，检查是否点击了文本框并设置焦点
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
	loadimage(&img, "./res./初始背景.jpg");
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);//处理字体背景
	setfillcolor(CYAN);//设置填充色，这里是浅青色
	setlinecolor(BLACK); //设置当前线条的颜色为黑色
	//cleardevice();//显示背景颜色
	//展示按钮
	btn1->show();
	btn2->show();
	btn3->show();
	btn4->show();
	btn5->show();
}
void PlayGame::runGame()
{
	//以下是一些基础设置
	initgraph(994, 726,NOCLOSE);//创建窗口
	HWND hnd = GetHWnd();
	settextstyle(40,0,"楷体");//设置字体
	setbkcolor(WHITE);//设置背景颜色
	settextcolor(BLACK);
	menu();
	ExMessage msg;
	bool on = 1;
	double i = 1.5;
	while (on)
	{
		msg = getmessage();
		if (btn1->state(msg))		// 查看规则
		{
			viewRule();
			menu();
		}
		if (btn2->state(msg))		// 挑战模式
		{
			this->newChanllengeMode();
			menu();
		}
		if (btn3->state(msg))		// 出题模式
		{
			userSetPuzzle();
			menu();
		}
		if (btn4->state(msg))		//排行榜
		{
			viewRank();
			menu();
		}
		if (btn5->state(msg))		// 退出游戏
		{
			exit(0);
		}
	}
	getchar();
}
//可视化的出题模式
void PlayGame::userSetPuzzle()
{
	cleardevice();//清屏
	IMAGE img;
	loadimage(&img, "./res./初始背景.jpg");
	putimage(0, 0, &img);
	ExMessage msg;
	vector<pair<int, int>>randomPuzzle;
	btn6->show();//结束返回菜单
	bool t = true,t1=true;//循环条件
	IMAGE img0, img2, img3, img4, imgBlank, imgWin, imgLose, imgPlant;
	int x1=-1, x2=-1, x3=-1, x4=-1, y1=-1, y2=-1, y3=-1, y4=-1;//横坐标和纵坐标
	bool judge = true;//判断作答是否合适
	//用于自主输入题目
	string line0;
	string line1;
	string line2;
	string line3;
	string line4;
	string line5;
	string filename = "用户输入的题库.txt";
	fstream f;
	int nm=0;//文件中题目总数
	int n = 0;//选择的题目编号
	string c;//提取文件中题目总数
	/////////////
	loadimage(&img0, "./res./0.jpg", 35, 35);
	loadimage(&img2, "./res./0or2.jpg", 35, 35);
	loadimage(&img3, "./res./1or3.jpg", 35, 35);
	loadimage(&img4, "./res./4.jpg", 35, 35);
	loadimage(&imgBlank, "./res./空格.jpg", 35, 35);
	loadimage(&imgWin, "./res./胜利.jpg", 254, 83);//putimage(370, 50, &imgWin);
	loadimage(&imgLose, "./res./失败.jpg");//putimage(370, 50, &imgLose);
	loadimage(&imgPlant, "./res./种树.jpg", 35, 35);
	putimage(0, 0, &img);
	BeginBatchDraw();
	while (t)
	{
		cleardevice();//清屏
		putimage(0, 0, &img);
		msg = getmessage();/////
		btnRandomPuzzle->show();
		btnAnswer->show();
		btnUserSetPuzzle->show();
		btn6->show();//结束返回菜单
		//随机出题
		if (btnRandomPuzzle->state(msg))
		{
			randomPuzzle = this->p->charToPair(p->setRandomQuestion());
			t1 = true;
			while (t1)
			{
				x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
				cleardevice();//清屏
				putimage(0, 0, &img);
				btn10->show();
				btn12->show();
				//可视化展示问题矩阵
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
				//退出
				msg = getmessage();
				if (btn10->state(msg))t1 =false;
				else if (btn12->state(msg))
				{
					cleardevice();
					putimage(0, 0, &img);
					//可视化展示问题矩阵
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
					outtextxy(450, 260, "1×1");
					outtextxy(450, 510, "3×3");
					outtextxy(700, 260, "2×2");
					outtextxy(700, 510, "4×4");
					TextBox* tbx1 = new TextBox(420, 50, 30, 30, 1);
					TextBox* tbx2 = new TextBox(670, 50, 30, 30, 1);
					TextBox* tbx3 = new TextBox(420, 300, 30, 30, 1);
					TextBox* tbx4 = new TextBox(670, 300, 30, 30, 1);
					TextBox* tby1 = new TextBox(420, 100, 30, 30, 1);
					TextBox* tby2 = new TextBox(670, 100, 30, 30, 1);
					TextBox* tby3 = new TextBox(420, 350, 30, 30, 1);
					TextBox* tby4 = new TextBox(670, 350, 30, 30, 1);
					finishAns->show();//“完成作答”按钮

					textBoxes.push_back(tbx1); textBoxes.push_back(tbx2);
					textBoxes.push_back(tbx3); textBoxes.push_back(tbx4);
					textBoxes.push_back(tby1); textBoxes.push_back(tby2);
					textBoxes.push_back(tby3); textBoxes.push_back(tby4);
					drawAllTextBoxes(textBoxes);
					judge = false;//判断作答是否符合规则
					//判断是否点击
					while (true)
					{
						// 获取并处理鼠标事件
						msg = getmessage();
						if (msg.message == WM_LBUTTONDOWN)
						{
							onMouseClick(msg.x, msg.y, textBoxes);
						}
						// 获取并处理键盘输入
						if (_kbhit())
						{
							wchar_t ch = _getch();
							for (TextBox* box : textBoxes)
							{
								if (box->getSelect())
								{
									box->keyInput(ch);
									box->updateCursor(); // 更新光标状态
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
						//完成作答
						if (finishAns->state(msg))
						{
							if (judge == true)break;
							if (judge == false)MessageBox(hnd, "作答不符合规则！", "提示", MB_OK | MB_ICONWARNING);
						}
					}

					btnBack->show();//展示返回键
					//重置作答所用的矩阵
					for (int i = 0; i < 4; i++)
					{
						this->p->matrixToFill[i]->setMatrixToZero();
					}
					this->p->finalMatrix->setMatrixToZero();
					//根据输入填充矩阵
					this->p->matrixToFill[0]->fillMatrix(x1, y1, x1, y1);
					this->p->matrixToFill[1]->fillMatrix(x2, y2, x2 + 1, y2 + 1);
					this->p->matrixToFill[2]->fillMatrix(x3, y3, x3 + 2, y3 + 2);
					this->p->matrixToFill[3]->fillMatrix(x4, y4, x4 + 3, y4 + 3);
					//得到最终矩阵
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
					//可视化展示最终作答的矩阵
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
						putimage(480, 650, &imgWin);//显示回答正确
					}
					else
					{
						putimage(480, 650, &imgLose);//显示回答错误
					}
					FlushBatchDraw();
					//退出按键
					while (true)
					{
						msg = getmessage();
						if (btnBack->state(msg))break;
						FlushBatchDraw();
					}
					//////////////
					vector<TextBox*>().swap(textBoxes);
					delete tbx1, tbx2, tbx3, tbx4, tby1, tby2, tby3, tby4;
					//重置作答所用的矩阵
					for (int i = 0; i < 4; i++)
					{
						this->p->matrixToFill[i]->setMatrixToZero();
					}
					this->p->finalMatrix->setMatrixToZero();
					
				}
				FlushBatchDraw();
			}
			
		}
		//自主出题
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
			//绘制输入框
			drawAllTextBoxes(textBoxes);
			finishAns->show();
			btn10->show();
			//判断是否点击
			while (true)
			{
				// 获取并处理鼠标事件
				msg = getmessage();
				if (msg.message == WM_LBUTTONDOWN)
				{
					onMouseClick(msg.x, msg.y, textBoxes);
				}
				// 获取并处理键盘输入
				if (_kbhit())
				{
					wchar_t ch = _getch();
					for (TextBox* box : textBoxes)
					{
						if (box->getSelect())
						{
							box->keyInput(ch);
							box->updateCursor(); // 更新光标状态
							break;
						}
					}
				}
				drawAllTextBoxes(textBoxes);
				FlushBatchDraw();
				judge = true;//循环退出条件
				//完成输入
				if (finishAns->state(msg))
				{
					//检查输入是否符合要求
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
					//判断是否完成
					if(judge==true)break;
					else
					{
						MessageBox(hnd, "出题不符合规则！请重新输入", "提示", MB_OK | MB_ICONWARNING);
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
				//提取文件中题目总数
				f.open(filename, ios::in);//打开文件
				getline(f,c);
				n = stoi(c);//目前题目总数
				c = to_string(n+1);//题库中题目总数加一
				f.close();//关闭文件
				while (true)
				{
					btnC->show();
					msg = getmessage();
					if (btnC->state(msg))break;
					FlushBatchDraw();
				}
				//检查输入的题目是否有解
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
					//如果有解则把题目录入到题库中
					cleardevice();
					putimage(0, 0, &img);
					setfillcolor(CYAN);
					fillroundrect(400, 0, 460, 30, 1, 1);
					outtextxy(400, 0, "有解");

					f.open(filename, ios::app);
					f << "第" << (n + 1) << "题：\n";
					f << line0 << "\n";
					f << line1 << "\n";
					f << line2 << "\n";
					f << line3 << "\n";
					f << line4 << "\n";
					f << line5 << "\n";
					f.close();
					//修改文件中记录的题目总数
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
					outtextxy(400, 0, "无解");
					FlushBatchDraw();
				}
				//返回键
				while (true)
				{
					btn10->show();
					msg = getmessage();
					if (btn10->state(msg))break;
					FlushBatchDraw();
				}
				//释放内存
				vector<TextBox*>().swap(textBoxes);
				delete tb0, tb1, tb2, tb3, tb4, tb5;
			}
		}
		
		//作答
		if (btnAnswer->state(msg))
		{
			cleardevice();
			putimage(0, 0, &img);
			setfillcolor(CYAN);
			fillroundrect(440, 0, 710, 30, 1, 1);
			outtextxy(440, 0, "题库目前有");
			outtextxy(650, 0, "道题");
			string c;
			fstream f;
			f.open(filename, ios::in);
			getline(f,c);
			f.close();
			outtextxy(590, 0, c.c_str());
			nm = stoi(c);//目前题目总数
			TextBox* textbox1 = new TextBox(450, 300, 120, 30, 3);//创建文本框，设置只能输入一位数字
			Button* btnOK = new Button(0, 0, W, H, "确定完成输入");
			t = true;
			//从题库中选择题目
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
				
				textbox1->draw();//绘制文本框
				btnOK->show();//确定完成输入按键
				//点击确定，同时判断输入是否符合要求
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
						n = stoi(textbox1->getText());//字符数字转换为整型数字
						if (n >= 0)
						{
							//检查输入是否符合，不能输入大于题目总数的编号
							if (n <= nm)
							{
								t = true;//完成输入后跳出输入的循环
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
			}//输入的循环
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
					if (i >= (7 * n + 2))break;//读取完后跳出
					if (i > (7 * n - 5) && i < (7 * n + 2))
					{
						for (char ch : line)
						{
							if (ch != '\n')
							{
								v2.push_back(ch);//读取题目
							}
						}
					}
				}
				f.close();//关闭文件夹
				vector<pair<int, int>>tempM;
				tempM = this->p->charToPair(v2);
				//可视化展示问题矩阵
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
				outtextxy(450, 260, "1×1");
				outtextxy(450, 510, "3×3");
				outtextxy(700, 260, "2×2");
				outtextxy(700, 510, "4×4");
				//绘制输入框
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

				//绘制文本框
				drawAllTextBoxes(textBoxes);

				judge = false;//判断作答是否符合规则
				//判断是否点击
				while (true)
				{
					// 获取并处理鼠标事件
					msg = getmessage();
					if (msg.message == WM_LBUTTONDOWN)
					{
						onMouseClick(msg.x, msg.y, textBoxes);
					}
					// 获取并处理键盘输入
					if (_kbhit())
					{
						wchar_t ch = _getch();
						for (TextBox* box : textBoxes)
						{
							if (box->getSelect())
							{
								box->keyInput(ch);
								box->updateCursor(); // 更新光标状态
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
						if (judge == false)MessageBox(hnd, "作答不符合规则！", "提示", MB_OK | MB_ICONWARNING);
					}
					drawAllTextBoxes(textBoxes);
					FlushBatchDraw();
				}
				//重置作答所用的矩阵
				for (int i = 0; i < 4; i++)
				{
					this->p->matrixToFill[i]->setMatrixToZero();
				}
				this->p->finalMatrix->setMatrixToZero();
				//根据输入填充矩阵
				this->p->matrixToFill[0]->fillMatrix(x1, y1, x1, y1);
				this->p->matrixToFill[1]->fillMatrix(x2, y2, x2 + 1, y2 + 1);
				this->p->matrixToFill[2]->fillMatrix(x3, y3, x3 + 2, y3 + 2);
				this->p->matrixToFill[3]->fillMatrix(x4, y4, x4 + 3, y4 + 3);
				//得到最终矩阵
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
				//可视化展示最终作答的矩阵
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
				//返回键
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
				//重置作答所用的矩阵
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
		

		//返回键
		if (btn6->state(msg))
		{
			t = false;
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
}
//可视化的排行榜
void PlayGame::viewRank()
{
	cleardevice();//清屏
	IMAGE img;
	loadimage(&img, "./res./初始背景.jpg");
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
		//返回键
		if (btn6->state(msg))
		{
			t = false;
		}
		//作答用时排行榜
		if (btn7->state(msg))
		{
			cleardevice();
			putimage(0, 0, &img);
			btn10->show();
			this->R->displayTimeRankOfCM();
			//返回键
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
		
		//正确题数排行榜
		if (btn8->state(msg))
		{
			cleardevice();
			putimage(0, 0, &img);
			btn10->show();//结束返回上一级菜单
			this->R->displayCorrectNumRankOfCM();
			//返回键
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
		//总排行榜
		if (btn9->state(msg))
		{
			cleardevice();
			putimage(0, 0, &img);
			btn10->show();
			this->R->displayComprehensiveRankOfCM();
			//返回键
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
//可视化的挑战模式----------------------------------------------------------------------------------------------
void PlayGame::newChanllengeMode()
{
	cleardevice();//清屏
	IMAGE img;
	IMAGE img0, img2, img3, img4, imgBlank, imgWin, imgLose, imgPlant;
	Button* btnOK = new Button(0, 0, W, H, "确定完成输入");
	loadimage(&img, "./res./初始背景.jpg");
	loadimage(&img0, "./res./0.jpg",35,35);
	loadimage(&img2, "./res./0or2.jpg",35,35);
	loadimage(&img3, "./res./1or3.jpg",35,35);
	loadimage(&img4, "./res./4.jpg",35,35);
	loadimage(&imgBlank, "./res./空格.jpg",35,35);
	loadimage(&imgWin, "./res./胜利.jpg",254,83);//putimage(370, 50, &imgWin);
	loadimage(&imgLose, "./res./失败.jpg");//putimage(370, 50, &imgLose);
	loadimage(&imgPlant, "./res./种树.jpg",35,35);
	putimage(0, 0, &img);
	ExMessage msg;
	btn6->show();
	bool t = true;
	bool temp =true;
	bool t1 = true;
	bool c = true;
	int j = 1;
	int n = 0;//选择的题目编号
	int num[6] = { 1,2,3,4,5,6 };//题号数组
	clock_t startTime{};//开始时间
	clock_t endTime{};//结束时间
	setfillcolor(CYAN);
	fillroundrect((994 - 600) / 2.0,0, (994 - 600) / 2.0+650,30,1,1);
	outtextxy((994 - 600) / 2.0, 0, "该模式中一共要从题库六道题中选取三道题作答，会记录作答用时和正确题数");
	btn11->show();
	vector<pair<int, int>>tempMatrix;//问题矩阵
	p->displayPuzzleAndSetToMatrix();
	int x1, x2, x3, x4, y1, y2, y3, y4;//横坐标和纵坐标

	bool judge=false;//判断作答是否合适
	int count=0;//作答题目正确的次数
	double duration = 0;//作答总时长
	double correctNum = 0;
	while (t)
	{
		cleardevice();
		loadimage(&img, "./res./初始背景.jpg");
		putimage(0, 0, &img);
		
		setfillcolor(CYAN);
		fillroundrect((994 - 600) / 2.0, 0, (994 - 600) / 2.0 + 680, 60, 1, 1);
		outtextxy((994 - 600) / 2.0, 0, "该模式中一共要从题库六道题中选取三道题作答，会记录作答用时和正确题数");
		outtextxy((994 - 600) / 2.0, 30, "注意：输入时上方为矩阵左上角行序号，下方为矩阵左上角列序号，序号从0开始");
		btn6->show();
		btn11->show();
		msg = getmessage();
		t1 = true;
		string s = "请选择题号";
		while (t1)
		{
			msg = getmessage();
			temp = true;
			//开始挑战
			if (btn11->state(msg))
			{
				while (j <= 3 && temp == true)
				{
					x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
					msg = getmessage();
					cleardevice();
					loadimage(&img, "./res./初始背景.jpg");
					putimage(0, 0, &img);
					setfillcolor(CYAN);
					fillroundrect((994 - 600) / 2.0 + 100, 0, (994 - 600) / 2.0 + 650 - 100, 30, 1, 1);
					displayDoubleAt(j, (994 - 10) / 2.0, 0);
					//选择题号（不能重复）
					TextBox* textbox1 = new TextBox(450, 300, 120, 30, 1);//创建文本框，设置只能输入一位数字
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
						n = (int)(static_cast<int>((textbox1->getText())[0]) - '0');//字符数字转换为整型数字
						textbox1->draw();//绘制文本框
						btnOK->show();//确定完成输入按键
						//点击确定，同时判断输入是否符合要求
						if (btnOK->state(msg))
						{
							if (n != 0)
							{
								//检查输入是否符合，不能输入重复的编号&不能输入1~6之外的编号
								for (int i = 0; i < 6; i++)
								{
									if (n == num[i])
									{
										num[i] = 0;
										c = false;//完成输入后跳出输入的循环
										break;
									}
								}
							}
						}
						FlushBatchDraw();
					}//输入的循环
					EndBatchDraw();
					
					cleardevice();
					putimage(0, 0, &img);
					setfillcolor(CYAN);
					fillroundrect((994 - 600) / 2.0 + 100, 0, (994 - 600) / 2.0 + 650 - 100, 30, 1, 1);
					displayDoubleAt(j, (994 - 10) / 2.0, 0);
					cout << n << endl;
					tempMatrix = p->getTheSelectedMatrixQuestion(n);
					this->p->printMatrixQuestion(tempMatrix);/////////////
					//可视化展示问题矩阵
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
					outtextxy(450, 260, "1×1");
					outtextxy(450, 510, "3×3");
					outtextxy(700, 260, "2×2");
					outtextxy(700, 510, "4×4");
					//绘制输入框
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
					
					//绘制文本框
					drawAllTextBoxes(textBoxes);

					judge = false;//判断作答是否符合规则
					startTime = clock();//记录开始时间
					//判断是否点击
					BeginBatchDraw();
					while (true)
					{
						// 获取并处理鼠标事件
						msg = getmessage();
						if (msg.message == WM_LBUTTONDOWN) 
						{
							onMouseClick(msg.x, msg.y, textBoxes);
						}
						// 获取并处理键盘输入
						if (_kbhit()) 
						{
							wchar_t ch = _getch();
							for (TextBox* box : textBoxes) 
							{
								if (box->getSelect()) 
								{
									box->keyInput(ch);
									box->updateCursor(); // 更新光标状态
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
							if (judge == false)MessageBox(hnd,"作答不符合规则！","提示", MB_OK | MB_ICONWARNING);
						}
						drawAllTextBoxes(textBoxes);
						FlushBatchDraw();
					}
					EndBatchDraw();
					endTime = clock();//记录作答结束时间
					duration += (double)(endTime - startTime)/ CLOCKS_PER_SEC;//作答时间为三次作答时间的和
					//重置作答所用的矩阵
					for (int i = 0; i < 4; i++)
					{
						this->p->matrixToFill[i]->setMatrixToZero();
					}
					this->p->finalMatrix->setMatrixToZero();
					//根据输入填充矩阵
					this->p->matrixToFill[0]->fillMatrix(x1, y1, x1, y1);
					this->p->matrixToFill[1]->fillMatrix(x2, y2, x2 + 1, y2 + 1);
					this->p->matrixToFill[2]->fillMatrix(x3, y3, x3 + 2, y3 + 2);
					this->p->matrixToFill[3]->fillMatrix(x4, y4, x4 + 3, y4 + 3);
					//得到最终矩阵
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
					//可视化展示最终作答的矩阵
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
						count++;//作答正确的次数加一
					}
					else
					{
						putimage(480, 650, &imgLose);
					}
					
					j++;//答题完成后，答题次数增加一次
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
				f1.open("用时排行榜.dat", ios::app | ios::binary);
				f2.open("正确题数排行榜.dat", ios::app | ios::binary);
				f3.open("总排行榜.dat", ios::app | ios::binary);
				correctNum = count;
				this->R->comprehensiveRankRecordForCM.push_back(make_pair(correctNum, duration));
				this->R->correctNumRecordForCM.push_back(correctNum);
				if (correctNum > 0)this->R->timeRecordForCM.push_back(duration);
				//把作答的数据保存到二进制文件中
				f1 << duration << "\n";
				f2 << correctNum << "\n";
				f3 << correctNum << "\t" << duration << "\n";
				f1.close();
				f2.close();
				f3.close();
				//排序
				this->R->sortTheCorrectNum();
				this->R->sortTheTime();
				////////////////////////
				cleardevice();
				loadimage(&img, "./res./初始背景.jpg");
				putimage(0, 0, &img);
				outtextxy(250, 100, "本次作答答对");
				displayDoubleAt(correctNum, 400, 100);
				outtextxy(450, 100, "道题，用时为");
				displayDoubleAt(duration, 600, 100);
				outtextxy(700, 100, "秒");
				//返回键
				btn6->show();
				t = true;
				while (t)
				{
					msg = getmessage();
					if (btn6->state(msg))
					{
						t = false;
						t1 = false;//挑战模式结束，返回主菜单
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
//挑战模式-------------------------------------------------------------------------
void PlayGame::chanllengeMode()
{
	fstream f1;
	fstream f2;
	fstream f3;
	f1.open("用时排行榜.dat", ios::app | ios::binary);
	f2.open("正确题数排行榜.dat", ios::app | ios::binary);
	f3.open("总排行榜.dat", ios::app | ios::binary);
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
		//选择题目
		std::cout << "\n请输入您选择的题目的序号(序号须在1~5之间)：" << endl;
		startTime = clock();//记录开始时间
		int n;
		cin >> n;
		while (n < 1 || n>6)
		{
			std::cout << "查无此问题，请重新选择题目：" << endl;
			cin >> n;
		}
		do
		{
			t = true;
			//判断是否已经做过输入的题目编号表示的题目
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
				std::cout << "您已做过第"<<n<<"道题，请选择未做过的题目的编号：" << endl;
				cin >> n;
				break;
			case true:
				std::cout << "您已成功选择题目" << endl;
				break;
			}
		} while (!t);
		a[i] = n;//把选择过的题目编号保存到数组中，以便后续判断
		tempMatrix = p->getTheSelectedMatrixQuestion(n);
		p->printMatrixQuestion(tempMatrix);
		//输入答案
		std::cout << "现在开始输入您的答案：" << endl;
		p->inputTheAnswer();
		//记录结束时间
		if (i == 0)endTime = clock();
		//检查答案是否正确
		switch (p->checkTheAnswer(tempMatrix))
		{
		case true:
			std::cout << "恭喜您回答正确。" << endl;
			count++;
			break;
		case false:
			std::cout << "很遗憾，您回答错误。" << endl;
			break;
		}
		i++;
	}
	/*cout << "您本次的做题顺序为：";
	for (int b = 0; b < 5; b++)
	{
		cout << a[b] << " ";
	}*/
	double correctNum = count;
	std::cout << "\n本次挑战模式中您共答对了" << count << "道题，答错了" << (3 - count) << "道题,正确题数为"<<correctNum<< endl;
	double duration = (double)(endTime-startTime)/CLOCKS_PER_SEC;//作答总时长
	std::cout << "本次挑战用时为" << duration << "秒" << endl;
	std::cout << "您已完成一次挑战模式" << endl;
	this->R->comprehensiveRankRecordForCM.push_back(make_pair(correctNum, duration));
	this->R->correctNumRecordForCM.push_back(correctNum);
	if(correctNum>0)this->R->timeRecordForCM.push_back(duration);
	//把作答的数据保存到二进制文件中
	f1 << duration << "\n";
	f2 << correctNum << "\n";
	f3 << correctNum << "\t" << duration<<"\n";
	f1.close();
	f2.close();
	f3.close();
	//排序
	this->R->sortTheCorrectNum();
	this->R->sortTheTime();
	//展示排行榜
	this->R->displayCorrectNumRankOfCM();
	this->R->displayTimeRankOfCM();
	this->R->displayComprehensiveRankOfCM();
}
//------------------------------------------------------------------------------------------------------------------------------------
void PlayGame::viewRule()
{
	cleardevice();//清屏
	settextcolor(BLACK);
	IMAGE img;
	IMAGE img1;
	IMAGE img2;
	IMAGE img3;
	IMAGE img4;
	loadimage(&img, "./res./初始背景.jpg");
	loadimage(&img1, "./res./0.jpg",65,65);
	loadimage(&img2, "./res./0or2.jpg",65,65);
	loadimage(&img3, "./res./1or3.jpg",65,65);
	loadimage(&img4, "./res./4.jpg",65,65);
	putimage(0, 0, &img);
	putimage((994 - W) / 2.0, 100, &img1);
	putimage((994 - W) / 2.0, 170, &img2);
	putimage((994 - W) / 2.0, 240, &img3);
	putimage((994 - W) / 2.0, 310, &img4);
	outtextxy((994 - W) / 2.0+70, 100,"表示该位置不需要植树");
	outtextxy((994 - W) / 2.0 + 70, 170, "表示该位置需要0或2棵植树");
	outtextxy((994 - W) / 2.0 + 70, 240, "表示该位置需要1或3植树");
	outtextxy((994 - W) / 2.0 + 70, 310, "表示该位置需要4植树");
	outtextxy(0,0,"题目是为6×6的矩阵，每个位置有一个图案（如下所示），您需要在4个空的6×6矩阵中的对应的位置");
	outtextxy(0,20, "分别填入1×1、2×2、3×3、4×4的矩阵(在相应区域植树)使得4个矩阵的和满足题目要求");
	ExMessage msg;
	btn6 = new Button(844, 686, W, H, "结束返回菜单");
	btn6->show();
	bool t = true;
	while (t)
	{
		msg = getmessage();
		//返回键
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

	//遍历查看是否有解
	int t = 0;//终止判断
	bool res=false;//判断结果
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
									//四个矩阵相加
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
									//判断是否符合题目
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

	//遍历查看是否有解
	int t = 0;//终止判断
	bool res = false;//判断结果
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
									//四个矩阵相加
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
									//判断是否符合题目
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
	//展示题目的解答
	IMAGE img0, img2, img3, img4, imgBlank, imgWin, imgLose, imgPlant;
	loadimage(&img0, "./res./0.jpg", 35, 35);
	loadimage(&img2, "./res./0or2.jpg", 35, 35);
	loadimage(&img3, "./res./1or3.jpg", 35, 35);
	loadimage(&img4, "./res./4.jpg", 35, 35);
	loadimage(&imgBlank, "./res./空格.jpg", 35, 35);
	loadimage(&imgWin, "./res./胜利.jpg", 254, 83);//putimage(370, 50, &imgWin);
	loadimage(&imgLose, "./res./失败.jpg");//putimage(370, 50, &imgLose);
	loadimage(&imgPlant, "./res./种树.jpg", 35, 35);
	vector<pair<int, int>>puz;
	puz = this->p->charToPair(c);
	//可视化展示问题矩阵
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
	//可视化展示解
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
	//释放内存
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




