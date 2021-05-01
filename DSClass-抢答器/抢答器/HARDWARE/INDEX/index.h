#ifndef __INDEX_H
#define __INDEX_H
#include "lcd.h"


//显示标题函数
void Index_Title();
//显示抢题按钮函数
void Index_Button();
//显示选手，参数num为哪个选手抢答成功，弱无则为0;
void Index_Player(u8 num);
//红按钮
void Index_Redbutton();
//把蓝字刷乘红字
//起始X  起始Y 终点x和y
void Index_Red(u16 x1,u16 y1,u16 x2,u16 y2);









#endif