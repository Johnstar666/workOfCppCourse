#pragma once
#include "Widget.h"
#include <string>
using namespace std;
// ��ť��
class Button :
    public Widget
{
public:
    Button(int x = 0, int y = 0, int width = 100, int height = 60,const string& text="��ʼ");
    void show() const;                      // ��ʾ��ť
    bool state(const ExMessage& msg);       // ��ť״̬��true ��ʾ��ť����
    string& getText();    // ��ȡ��ť�ı�
    void setText(string& text); // ���ð�ť�ı�

protected:
    bool isIn(const ExMessage& msg) const;  // �ж�����Ƿ��ڰ�ť����
    string text;                      // ��ť�ı�
    bool isChange;     // ��ť״̬�Ƿ�ı�

public:
    //  ���ڰ�ť��Ƶ�һЩ����
    int linestyle = PS_SOLID;        //������ʽ
    int button_color = CYAN;        //��ť��ɫ
    int in_color = LIGHTBLUE;       //������ڰ�ť�ϵ���ɫ
    int click_clolor = LIGHTBLUE;  //�����°�ťʱ��ť����ɫ
};



