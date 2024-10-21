#pragma once
#include <graphics.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include<stdio.h>
#include"PlayGame.h"
#include"Widget.h"
#include"Button.h"
#include"TextBox.h"
class ShowPage
{
private:
    int width; // ���
    int height; // �߶�
    int currentIndex; // ��ǰҳ������
    vector<IMAGE*> pages; // �洢����ҳ���ͼƬָ��
    vector<vector<Button*>> buttons; // �洢ÿ��ҳ���ϵİ�ť

    void addPage(IMAGE*);
    void addButton(int, Button*);
    void seCurrentIndex(int);
    void mouseClick(int, int);
    void mouseMove(int, int);
    void draw();
public:
    ShowPage(int width, int height)
        :width(width), height(height)
    {

    }
    ~ShowPage() {};
    void init();
    void close();
    void run();
};

