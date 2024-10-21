#pragma once
#include "Widget.h"
#include <string>
using namespace std;
// 按钮类
class Button :
    public Widget
{
public:
    Button(int x = 0, int y = 0, int width = 100, int height = 60,const string& text="开始");
    void show() const;                      // 显示按钮
    bool state(const ExMessage& msg);       // 按钮状态，true 表示按钮按下
    string& getText();    // 获取按钮文本
    void setText(string& text); // 设置按钮文本

protected:
    bool isIn(const ExMessage& msg) const;  // 判断鼠标是否在按钮里面
    string text;                      // 按钮文本
    bool isChange;     // 按钮状态是否改变

public:
    //  关于按钮设计的一些变量
    int linestyle = PS_SOLID;        //线条样式
    int button_color = CYAN;        //按钮颜色
    int in_color = LIGHTBLUE;       //当鼠标在按钮上的颜色
    int click_clolor = LIGHTBLUE;  //当按下按钮时按钮的颜色
};



