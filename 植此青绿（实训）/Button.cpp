#include "Button.h"
#include<graphics.h>
#include<conio.h>
#include<string>
#include"Windows.h"
#include<locale>
#include<codecvt>
// 声明为外部变量，需要在其他源文件中定义
extern int linestyle;
extern int button_color;
extern int in_color;
extern int click_clolor;

Button::Button(int x, int y, int width, int height, const string&text) 
	: Widget(x, y, width, height), text(text), isChange(false)
{
}

void Button::show() const
{
	// 设置样式
	setlinestyle(linestyle, 2);	//PS_SOLID是指一条由特定颜色的实线，该线的宽度由调用GDI API的参数所指定的宽度决定。
	//PS_SOLID通常用于创建线框，边框或其他需要绘制线条的图形元素
	setfillcolor(button_color);	//按钮的颜色
	settextstyle(25, 0, "微软雅黑");

	// 绘制按钮
	fillrectangle(x, y, x + width, y + height);

	// 绘制文本
	RECT rect = { x, y, x + width, y + height };
	
	drawtext(text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

bool Button::state(const ExMessage& msg)//按钮的状态
{
	if (msg.message == WM_MOUSEMOVE && isIn(msg))	// 按钮悬浮
	{
		// 设置样式
		setlinestyle(linestyle, 2);
		setfillcolor(in_color);	// 鼠标放上后按钮的颜色
		settextstyle(25, 0, "微软雅黑");

		// 绘制按钮
		fillrectangle(x, y, x + width, y + height);

		// 绘制文本
		RECT rect = { x, y, x + width, y + height };
		
		drawtext(text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		isChange = true;
		return false;
	}
	else if ((msg.message == WM_LBUTTONDOWN || msg.message == WM_LBUTTONUP) && isIn(msg))	// 按钮被点击
	{
		// 设置样式
		setlinestyle(linestyle, 2);
		setfillcolor(click_clolor);	// 鼠标按下后按钮的颜色
		settextstyle(25, 0, "微软雅黑");

		// 绘制按钮
		fillrectangle(x, y, x + width, y + height);

		// 绘制文本
		RECT rect = { x, y, x + width, y + height };
		drawtext(text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		isChange = true;
		return true;
	}
	else	// 在按钮状态改变的时候，恢复按钮原来的状态，防止屏闪
	{
		if (isChange)
		{
			show();
			isChange = false;
		}
		return false;
	}
}
string& Button::getText()
{
	// TODO: 在此处插入 return 语句
	return text;
}

void Button::setText(string& text)
{
	this->text = text;
}

bool Button::isIn(const ExMessage& msg) const
{
	if (msg.x >= this->x && msg.x <= this->x + width && msg.y >= this->y && msg.y <= this->y + height)
	{
		return true;
	}
	return false;
}