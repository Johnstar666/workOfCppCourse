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
    int width; // 宽度
    int height; // 高度
    int currentIndex; // 当前页面索引
    vector<IMAGE*> pages; // 存储所有页面的图片指针
    vector<vector<Button*>> buttons; // 存储每个页面上的按钮

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

