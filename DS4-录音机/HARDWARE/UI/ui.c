#include "lcd.h"
#include "cnfont.h"
#include "ui.h"
#include "w25qxx.h"
#include "usart.h"	 
extern u8 audionum;
void draw_font64(u16 x,u16 y,u8 index,u8 showstring[]){
		u16 temp,t,t1;
    u16 y0=y;
  
    for(t=0;t<512;t++) //=24*24   72??
    {   
       temp=showstring[index*512+t]; 
       for(t1=0;t1<8;t1++)
       {
				  if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			    else LCD_Fast_DrawPoint(x,y,BACK_COLOR);  
          temp<<=1;
          y++;
         if((y-y0)==64)
         {
          y=y0;
          x++;
          break;
         }
       }  
 
    } 
}//64位字体

void draw_font32(u16 x,u16 y,u8 index,u8 showstring[]){
		u8 temp,t,t1;
    u16 y0=y;
  
    for(t=0;t<128;t++) //=24*24   72??
    {   
       temp=showstring[index*128+t]; 
       for(t1=0;t1<8;t1++)
       {
				  if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			    else LCD_Fast_DrawPoint(x,y,BACK_COLOR);  
          temp<<=1;
          y++;
         if((y-y0)==32)
         {
          y=y0;
          x++;
          break;
         }
       }  
 
    }  
}//32位字体


void Face_index(){
BACK_COLOR=YELLOW;
	for(u8 i=0;i<=5;i++){
		draw_font64(48+i*64,40,i,char64);
	}
	
	LCD_Fill(75,140,135,200,GRAY);
	LCD_Fill(165,140,225,200,GREEN);
	LCD_Fill(255,140,315,200,GREEN);
	LCD_Fill(345,140,405,200,GREEN);
	POINT_COLOR=BLACK;
	BACK_COLOR=GRAY;
	LCD_ShowNum(100,160,1,1,24);
	BACK_COLOR=GREEN;	
	LCD_ShowNum(190,160,2,1,24);
	LCD_ShowNum(280,160,3,1,24);
	LCD_ShowNum(370,160,4,1,24);
	BACK_COLOR=WHITE;
	LCD_DrawRectangle(60,300,420,350);
	
	LCD_DrawRectangle(60,400,420,450);
	LCD_Fill(60,400,420,450,BLACK);
	
	for(u8 i=50;i>0;i--){
	LCD_Draw_Circle(60, 600, i);
		POINT_COLOR=BLUE;
	LCD_Draw_Circle(240, 600, i);
		POINT_COLOR=GREEN;
	LCD_Draw_Circle(420, 600, i);
		POINT_COLOR=BLACK;
	}
	LCD_ShowString(30,700,100,24,24,"RECORD");
	LCD_ShowString(220,700,100,24,24,"PLAY");
	LCD_ShowString(390,700,100,24,24,"EMPTY");
	LCD_ShowString(60,280,50,16,16,"RATE");
	LCD_ShowString(60,380,50,16,16,"VOLUME");
extern u8 a[];
			for(u8 audionum=0;audionum<4;audionum++){
			W25QXX_Read(a,0x180000*audionum,1);
				if(a[0]!=255){
					switch(audionum)
					{
						case 0:LCD_Fill(75,200,135,220,RED);break;
						case 1:LCD_Fill(165,200,225,220,RED);break;
						case 2:LCD_Fill(255,200,315,220,RED);break;
						case 3:LCD_Fill(345,200,405,220,RED);break;						
					}
				}
			}
}//主界面
void Face_indexsc(){
switch(audionum)
			{
				case 0:
						BACK_COLOR=GRAY;
					LCD_Fill(75,140,135,200,GRAY);
					LCD_Fill(165,140,225,200,GREEN);
					LCD_Fill(255,140,315,200,GREEN);
					LCD_Fill(345,140,405,200,GREEN);
					LCD_ShowNum(100,160,1,1,24);
						BACK_COLOR=GREEN;
					LCD_ShowNum(190,160,2,1,24);
					LCD_ShowNum(280,160,3,1,24);
					LCD_ShowNum(370,160,4,1,24);
						BACK_COLOR=WHITE;
				break;
				
				case 1:
						BACK_COLOR=GRAY;
					LCD_Fill(75,140,135,200,GREEN);
					LCD_Fill(165,140,225,200,GRAY);
					LCD_Fill(255,140,315,200,GREEN);
					LCD_Fill(345,140,405,200,GREEN);
					LCD_ShowNum(190,160,2,1,24);
						BACK_COLOR=GREEN;
					LCD_ShowNum(100,160,1,1,24);
					LCD_ShowNum(280,160,3,1,24);
					LCD_ShowNum(370,160,4,1,24);
						BACK_COLOR=WHITE;
				break;
				
				case 2:
						BACK_COLOR=GRAY;
					LCD_Fill(75,140,135,200,GREEN);
					LCD_Fill(165,140,225,200,GREEN);
					LCD_Fill(255,140,315,200,GRAY);
					LCD_Fill(345,140,405,200,GREEN);
					LCD_ShowNum(280,160,3,1,24);
						BACK_COLOR=GREEN;
					LCD_ShowNum(100,160,1,1,24);
					LCD_ShowNum(190,160,2,1,24);
					LCD_ShowNum(370,160,4,1,24);
						BACK_COLOR=WHITE;
				break;
				
				case 3:
						BACK_COLOR=GRAY;
					LCD_Fill(75,140,135,200,GREEN);
					LCD_Fill(165,140,225,200,GREEN);
					LCD_Fill(255,140,315,200,GREEN);
					LCD_Fill(345,140,405,200,GRAY);
					LCD_ShowNum(370,160,4,1,24);
						BACK_COLOR=GREEN;
					LCD_ShowNum(100,160,1,1,24);
					LCD_ShowNum(190,160,2,1,24);
					LCD_ShowNum(280,160,3,1,24);
						BACK_COLOR=WHITE;
				break;
				
				default:
					break;}}















