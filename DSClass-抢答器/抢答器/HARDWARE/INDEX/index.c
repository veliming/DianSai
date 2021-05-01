#include "index.h"
//#include "Chinese.h"
extern u8 CH_Title[];   //标题的字模
extern u8 Button_64[];   //按键汉字的字模
extern u8 Player_CH[];   

void Index_Title(){
	POINT_COLOR=BLUE;
	LCD_Show_Ch_Font96(72,64,0,CH_Title);
	LCD_Show_Ch_Font96(192,64,1,CH_Title);
	LCD_Show_Ch_Font96(312,64,2,CH_Title);
}

void Index_Button(){
	POINT_COLOR=GREEN;
	LCD_Fill(72,600,408,750,GREEN);
	POINT_COLOR=BLACK;
	BACK_COLOR=GREEN;
	LCD_Show_Ch_Font64(142,643,0,Button_64);
	LCD_Show_Ch_Font64(284,643,1,Button_64);
	
}

void Index_Player(u8 num){
	u16 x;
	BACK_COLOR=WHITE;
	
	if(num==1){POINT_COLOR=RED;}
	else {POINT_COLOR=BLUE;}
	x=42;
	LCD_Show_Ch_Font32(x,400,0,Player_CH);
	LCD_Show_Ch_Font32(x+36,400,1,Player_CH);
	LCD_Show_Ch_Font32(x+72,400,2,Player_CH);
	
	if(num==2){POINT_COLOR=RED;}
	else {POINT_COLOR=BLUE;}
	x=196;
	LCD_Show_Ch_Font32(x,400,0,Player_CH);
	LCD_Show_Ch_Font32(x+36,400,1,Player_CH);
	LCD_Show_Ch_Font32(x+72,400,3,Player_CH);
	
	if(num==3){POINT_COLOR=RED;}
	else {POINT_COLOR=BLUE;}
	x=350;
	LCD_Show_Ch_Font32(x,400,0,Player_CH);
	LCD_Show_Ch_Font32(x+36,400,1,Player_CH);
	LCD_Show_Ch_Font32(x+72,400,4,Player_CH);
	
}

void Index_Redbutton(){
	POINT_COLOR=RED;
	LCD_Fill(72,600,408,750,RED);
	POINT_COLOR=BLACK;
	BACK_COLOR=RED;
	LCD_Show_Ch_Font64(110,643,4,Button_64);
	LCD_Show_Ch_Font64(180,643,5,Button_64);
	LCD_Show_Ch_Font64(250,643,6,Button_64);
	LCD_Show_Ch_Font64(320,643,7,Button_64);
}

void Index_Red(u16 x1,u16 y1,u16 x2,u16 y2){
	u16 x,y;
	for(x=x1;x<=x2;x++){
		for(y=y1;y<=y2;y++){
			if(LCD_ReadPoint(x,y)!=WHITE){
				LCD_Fast_DrawPoint(x,y,RED);
			}
		}
	}
}

