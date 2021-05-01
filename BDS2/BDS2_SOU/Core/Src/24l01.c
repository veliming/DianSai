/*
 * 24l01.c
 *
 *  Created on: Apr 26, 2021
 *      Author: vecto
 */
#include "24l01.h"
#include "spi.h"
#include "base.h"
const u8 TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址
const u8 RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址
void NRF24L01_SPI_Init(void)
{
    __HAL_SPI_DISABLE(&hspi1);               //先关闭SPI1
    hspi1.Init.CLKPolarity=SPI_POLARITY_LOW; //串行同步时钟的空闲状态为低电平
    hspi1.Init.CLKPhase=SPI_PHASE_1EDGE;     //串行同步时钟的第1个跳变沿（上升或下降）数据被采样
    HAL_SPI_Init(&hspi1);
    __HAL_SPI_ENABLE(&hspi1);                //使能SPI1
}
//SPI速度设置函数
//SPI速度=fAPB1/分频系数
//@ref SPI_BaudRate_Prescaler:SPI_BAUDRATEPRESCALER_2~SPI_BAUDRATEPRESCALER_2 256
//fAPB1时钟一般为42Mhz：
void SPI1_SetSpeed(uint8_t SPI_BaudRatePrescaler)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
    __HAL_SPI_DISABLE(&hspi1);            //关闭SPI
    hspi1.Instance->CR1&=0XFFC7;          //位3-5清零，用来设置波特率
    hspi1.Instance->CR1|=SPI_BaudRatePrescaler;//设置SPI速度
    __HAL_SPI_ENABLE(&hspi1);             //使能SPI

}
//SPI1 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
uint8_t SPI1_ReadWriteByte(uint8_t TxData)
{
	uint8_t Rxdata;
    HAL_SPI_TransmitReceive(&hspi1,&TxData,&Rxdata,1, 1000);
 	return Rxdata;          		    //返回收到的数据
}
//初始化24L01的IO口
void NRF24L01_Init(void)
{
//    GPIO_InitTypeDef GPIO_Initure;
//    __HAL_RCC_GPIOB_CLK_ENABLE();			//开启GPIOB时钟
//    __HAL_RCC_GPIOG_CLK_ENABLE();			//开启GPIOG时钟
//
//	//GPIOB14初始化设置:推挽输出
//    GPIO_Initure.Pin=GPIO_PIN_14; 			//PB14
//    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
//    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
//    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
//    HAL_GPIO_Init(GPIOB,&GPIO_Initure);     //初始化
//
//	//GPIOG6,7推挽输出
//    GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7;	//PG6,7
//    HAL_GPIO_Init(GPIOG,&GPIO_Initure);     //初始化
//
//	//GPIOG.8上拉输入
//	GPIO_Initure.Pin=GPIO_PIN_8;			//PG8
//	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
//	HAL_GPIO_Init(GPIOG,&GPIO_Initure);     //初始化

	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);//PB14输出1,防止SPI FLASH干扰NRF的通信

	//SPI1_Init();    		                //初始化SPI1
//    NRF24L01_SPI_Init();                    //针对NRF的特点修改SPI的设置
	NRF24L01_CE=0; 			                //使能24L01
	NRF24L01_CSN=1;			                //SPI片选取消
}
//检测24L01是否存在
//返回值:0，成功;1，失败
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;
	//SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_8); //spi速度为10.5Mhz（（24L01的最大SPI时钟为10Mhz,这里大一点没关系）
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//写入5个字节的地址.
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //读出写入的地址
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;
	if(i!=5)return 1;//检测24L01错误
	return 0;		 //检测到24L01
}
//SPI写寄存器
//reg:指定寄存器地址
//value:写入的值
u8 NRF24L01_Write_Reg(u8 reg,u8 value)
{
	  u8 status;
   	NRF24L01_CSN=0;                 //使能SPI传输
  	status =SPI1_ReadWriteByte(reg);//发送寄存器号
  	SPI1_ReadWriteByte(value);      //写入寄存器的值
  	NRF24L01_CSN=1;                 //禁止SPI传输
  	return(status);       		    //返回状态值
}
//读取SPI寄存器值
//reg:要读的寄存器
u8 NRF24L01_Read_Reg(u8 reg)
{
	  u8 reg_val;
   	NRF24L01_CSN=0;             //使能SPI传输
  	SPI1_ReadWriteByte(reg);    //发送寄存器号
  	reg_val=SPI1_ReadWriteByte(0XFF);//读取寄存器内容
  	NRF24L01_CSN=1;             //禁止SPI传输
  	return(reg_val);            //返回状态值
}
//在指定位置读出指定长度的数据
//reg:寄存器(位置)
//*pBuf:数据指针
//len:数据长度
//返回值,此次读到的状态寄存器值
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len)
{
	u8 status,u8_ctr;
  	NRF24L01_CSN=0;            //使能SPI传输
  	status=SPI1_ReadWriteByte(reg);//发送寄存器值(位置),并读取状态值
	for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=SPI1_ReadWriteByte(0XFF);//读出数据
  	NRF24L01_CSN=1;            //关闭SPI传输
  	return status;             //返回读到的状态值
}
//在指定位置写指定长度的数据
//reg:寄存器(位置)
//*pBuf:数据指针
//len:数据长度
//返回值,此次读到的状态寄存器值
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
	u8 status,u8_ctr;
	NRF24L01_CSN=0;             //使能SPI传输
  	status = SPI1_ReadWriteByte(reg);//发送寄存器值(位置),并读取状态值
  	for(u8_ctr=0; u8_ctr<len; u8_ctr++)SPI1_ReadWriteByte(*pBuf++); //写入数据
  	NRF24L01_CSN=1;             //关闭SPI传输
  	return status;              //返回读到的状态值
}
//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:发送完成状况
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 sta;
 	//SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_8); //spi速度为6.75Mhz（24L01的最大SPI时钟为10Mhz）
	NRF24L01_CE=0;
  	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//写数据到TX BUF  32个字节
 	NRF24L01_CE=1;                         //启动发送
	while(NRF24L01_IRQ!=0);                 //等待发送完成
	sta=NRF24L01_Read_Reg(STATUS);          //读取状态寄存器的值
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //清除TX_DS或MAX_RT中断标志
	if(sta&MAX_TX)                          //达到最大重发次数
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);  //清除TX FIFO寄存器
		return MAX_TX;
	}
	if(sta&TX_OK)                           //发送完成
	{
		return TX_OK;
	}
	return 0xff;//其他原因发送失败
}
//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:0，接收完成；其他，错误代码
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 sta;
	//SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_8); //spi速度为6.75Mhz（24L01的最大SPI时钟为10Mhz）
	sta=NRF24L01_Read_Reg(STATUS);          //读取状态寄存器的值
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //清除TX_DS或MAX_RT中断标志
	if(sta&RX_OK)//接收到数据
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据
		NRF24L01_Write_Reg(FLUSH_RX,0xff);  //清除RX FIFO寄存器
		return 0;
	}
	return 1;//没收到任何数据
}

//该函数初始化NRF24L01到RX模式
//设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
//当CE变高后,即进入RX模式,并可以接收数据了
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE=0;
  	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址

  	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);       //使能通道0的自动应答
  	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);   //使能通道0的接收地址
  	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);	        //设置RF通信频率
  	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//选择通道0的有效数据宽度
  	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);    //设置TX发射参数,0db增益,2Mbps,低噪声增益开启
  	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);     //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式
  	NRF24L01_CE=1; //CE为高,进入接收模式
}
//该函数初始化NRF24L01到TX模式
//设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,选择RF频道,波特率和LNA HCURR
//PWR_UP,CRC使能
//当CE变高后,即进入RX模式,并可以接收数据了
//CE为高大于10us,则启动发送.
void NRF24L01_TX_Mode(void)
{
	NRF24L01_CE=0;
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//写TX节点地址
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK

	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     //使能通道0的自动应答
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //使能通道0的接收地址
	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);       //设置RF通道为40
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	NRF24L01_CE=1;//CE为高,10us后启动发送
}
