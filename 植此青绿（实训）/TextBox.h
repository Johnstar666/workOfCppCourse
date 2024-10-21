#pragma once
#include <graphics.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <string>
#include<string>
using namespace std;
class TextBox
{
private:
    int x;
    int y;
    int width;
    int height;
    int maxWord;    //最长单词个数
    string text;   //文本
    bool isSelected;    //是否被选中
    bool showCursor;    //是否显示光标
    int cursorPos;      //光标位置

public:
    TextBox(int x, int y, int width, int height, int maxWord)
        : x(x), y(y), width(width), height(height), maxWord(maxWord), isSelected(false), showCursor(false), cursorPos(0)
    {
    }

    string& getText();

    bool getSelect() const;

    bool isEmpty() const;
 
    void setSelect(bool b)
    {
        isSelected = b;
    };

    void clear();

    void setText(const string& newText);

    void draw();

    bool checkClick(int mouseX, int mouseY);

    void keyInput(wchar_t ch);

    void updateCursor();
};
//输入框运行示例
/*cleardevice();
TextBox* textbox1 = new TextBox(200, 300, 120, 30, 8);
ExMessage msg;
BeginBatchDraw();
while (true)
{
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
    textbox1->draw();
    FlushBatchDraw();
}
EndBatchDraw(); */


