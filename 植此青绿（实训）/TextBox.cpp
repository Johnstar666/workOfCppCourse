#include "TextBox.h"
#include<easyx.h>
#include<iostream>
#include<string>

bool TextBox::getSelect() const
{
    return isSelected;
}

bool TextBox::isEmpty() const
{
    return text.empty();
}

void TextBox::clear()
{
    text = "";
}

void TextBox::setText(const string& newText)
{
    text = newText;
    cursorPos = text.length();
}

void TextBox::draw()
{
    setfillcolor(WHITE);
    if (isSelected)
    {
        setlinecolor(RGB(0, 120, 215));
        fillrectangle(x, y, x + width, y + height);
    }
    else
    {
        setlinecolor(RGB(122, 122, 122));
        fillrectangle(x, y, x + width, y + height);
    }

    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(height * 3 / 4, 0, _T("微软雅黑"));

    outtextxy(x + 5, y + (height - textheight(_T("微软雅黑"))) / 2, text.c_str());

    setlinecolor(BLACK);
    if (isSelected && showCursor)
    {
        int cursorX = x + 5 + textwidth(text.substr(0, cursorPos).c_str());
        line(cursorX, y + 2 + height / 8, cursorX, y + height * 7 / 8 - 2);
    }
}

bool TextBox::checkClick(int mouseX, int mouseY)
{
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
    {
        isSelected = true;
        return true;
    }
    else
    {
        isSelected = false;
        cursorPos = text.length();
        return false;
    }
}

void TextBox::keyInput(wchar_t ch)
{
    if (isSelected)
    {
        switch (ch)
        {
        case '\b':				// 用户按退格键，删掉一个字符
            if (!text.empty() && cursorPos > 0)
            {
                text.erase(cursorPos - 1, 1);
                cursorPos--;
            }
            break;
        case '\r':
        case '\n':
            cursorPos = text.length();
            isSelected = false;
            break;
        default:				// 用户按其它键，接受文本输入
            if (text.length() < maxWord)
            {
                text.insert(cursorPos, 1, ch);
                cursorPos++;
            }
        }
    }
}

void TextBox::updateCursor()
{
    static DWORD lastTick = GetTickCount();
    DWORD currentTick = GetTickCount();
    if (currentTick - lastTick >= 500) // 每500毫秒切换光标状态
    {
        showCursor = !showCursor;
        lastTick = currentTick;
    }
}

string& TextBox::getText()
{
    return text;
}
