#ifndef __FACE_H
#define __FACE_H	 
#include "sys.h"


void draw_font64(u16 x,u16 y,u8 index,u8 showstring[]);//64位字体

void draw_font32(u16 x,u16 y,u8 index,u8 showstring[]);//32位字体

void Face_index();//主界面
void Face_indexsc();//主界面刷新

								
#endif
