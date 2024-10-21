#include "Button.h"
#include<graphics.h>
#include<conio.h>
#include<string>
#include"Windows.h"
#include<locale>
#include<codecvt>
// ����Ϊ�ⲿ��������Ҫ������Դ�ļ��ж���
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
	// ������ʽ
	setlinestyle(linestyle, 2);	//PS_SOLID��ָһ�����ض���ɫ��ʵ�ߣ����ߵĿ���ɵ���GDI API�Ĳ�����ָ���Ŀ�Ⱦ�����
	//PS_SOLIDͨ�����ڴ����߿򣬱߿��������Ҫ����������ͼ��Ԫ��
	setfillcolor(button_color);	//��ť����ɫ
	settextstyle(25, 0, "΢���ź�");

	// ���ư�ť
	fillrectangle(x, y, x + width, y + height);

	// �����ı�
	RECT rect = { x, y, x + width, y + height };
	
	drawtext(text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

bool Button::state(const ExMessage& msg)//��ť��״̬
{
	if (msg.message == WM_MOUSEMOVE && isIn(msg))	// ��ť����
	{
		// ������ʽ
		setlinestyle(linestyle, 2);
		setfillcolor(in_color);	// �����Ϻ�ť����ɫ
		settextstyle(25, 0, "΢���ź�");

		// ���ư�ť
		fillrectangle(x, y, x + width, y + height);

		// �����ı�
		RECT rect = { x, y, x + width, y + height };
		
		drawtext(text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		isChange = true;
		return false;
	}
	else if ((msg.message == WM_LBUTTONDOWN || msg.message == WM_LBUTTONUP) && isIn(msg))	// ��ť�����
	{
		// ������ʽ
		setlinestyle(linestyle, 2);
		setfillcolor(click_clolor);	// ��갴�º�ť����ɫ
		settextstyle(25, 0, "΢���ź�");

		// ���ư�ť
		fillrectangle(x, y, x + width, y + height);

		// �����ı�
		RECT rect = { x, y, x + width, y + height };
		drawtext(text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		isChange = true;
		return true;
	}
	else	// �ڰ�ť״̬�ı��ʱ�򣬻ָ���ťԭ����״̬����ֹ����
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
	// TODO: �ڴ˴����� return ���
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