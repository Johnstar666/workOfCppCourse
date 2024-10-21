#include<stdio.h>
#include <graphics.h>
#include<iostream>
#include"PlayGame.h"
#include"Button.h"
#include<conio.h>
#include"TextBox.h"
using namespace std;
int main()
{
    PlayGame* g=new PlayGame;
    g->runGame();
    delete g;
    return 0;
}
//整个程序共3083行