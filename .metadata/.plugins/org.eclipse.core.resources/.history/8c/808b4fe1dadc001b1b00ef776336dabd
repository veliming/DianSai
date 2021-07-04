#ifndef ADS8688_H
#define ADS8688_H

// include the correct file according to you MCU
#include "stm32f4xx_hal.h"


// datasheet link
// https://www.ti.com/lit/ds/symlink/ads8668.pdf?ts=1620233637463&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FADS8668

// ----------------------- ADS Commands and Registers ------------------------ //
// Commands
#define NO_OP 0x00				/*在选定模式下继续操作在设备操作期间将SDI线连续保持为低电平（相当于向所有16位写入0）
								将继续在最后选择的模式（STDBY，PWR_DN或AUTO_RST，MAN_Ch_n）下进行设备操作。
								在这种模式下，设备将遵循程序寄存器（地址01h至3Ch）中已配置的相同设置。*/
#define STDBY 0x82				/*待机模式器件支持低功耗待机模式（STDBY），在该模式下，仅部分电路断电。
								内部基准电压源和缓冲器未断电，在退出STDBY模式时，可以在20 μs内为器件加电。
								退出STDBY模式时，程序寄存器不会复位为默认值。*/
#define PWR_DN 0x83				/*掉电模式（PWR_DN）
								器件支持硬件和软件掉电模式（PWR_DN），在该模式下，所有内部电路均被掉电，包括内部基准电压源和缓冲器。
								如果设备在内部参考模式下运行（REFSEL = 0），则退出PWR_DN模式后，设备加电并转换所选模拟输入通道至少需要15 ms的时间。
								设备的硬件电源模式在RST / PD（输入）部分中说明。
								硬件和软件掉电模式之间的主要区别在于，当设备从硬件掉电唤醒时，程序寄存器会重置为默认值，但是当设备从软件唤醒时，程序寄存器的先前设置会保留掉电。*/
#define RST 0x85				/*重置程序寄存器（RST）
								器件支持硬件和软件复位（RST）模式，在该模式下，
								所有程序寄存器均复位为其默认值。也可以使用硬件引脚将设备置于RST模式*/
#define AUTO_RST 0xa0			/*自动通道启用
								自动扫描所有模拟信道上的输入信号。自动扫描的通道序列可由程序寄存器中的自动扫描顺序控制寄存器（01h至02h）配置；请参阅程序寄存器映射部分。
								在此模式下，设备以升序连续循环通过所选通道，从最低通道开始，转换程序寄存器中选择的所有通道。
								序列完成后，设备返回到程序寄存器中的最低计数通道，并重复该序列。通过设置程序寄存器的范围选择寄存器，可以配置自动扫描序列中每个通道的输入电压范围。*/
#define MAN_CH_0 0xc0				// Channel 0 manual input selected
#define MAN_CH_1 0xc4				// Channel 1 manual input selected
#define MAN_CH_2 0xc8				// Channel 2 manual input selected
#define MAN_CH_3 0xcc				// Channel 3 manual input selected
#define MAN_CH_4 0xd0				// Channel 4 manual input selected
#define MAN_CH_5 0xd4				// Channel 5 manual input selected
#define MAN_CH_6 0xd8				// Channel 6 manual input selected
#define MAN_CH_7 0xdc				/*手动通道n选择（MAN_Ch_n）
									通过在手动通道n扫描模式（MAN_Ch_n）中进行操作，
									可以对设备进行编程以转换特定的模拟输入通道。
									通过在命令寄存器中写入有效的手动通道n选择命令（MAN_Ch_n）来完成该编程*/

// Register addresses
#define AUTO_SEQ_EN 0x01		// Auto Scan Sequencing Control
#define CH_PD 0x02			// Channel Power Down
#define F_S 0x03		// Feature Select
#define CHIR_0 0x05		// Channel 0 Input Range
#define CHIR_1 0x06		// Channel 1 Input Range
#define CHIR_2 0x07		// Channel 2 Input Range
#define CHIR_3 0x08		// Channel 3 Input Range
#define CHIR_4 0x09		// Channel 4 Input Range
#define CHIR_5 0x0a		// Channel 5 Input Range
#define CHIR_6 0x0b		// Channel 6 Input Range
#define CHIR_7 0x0c		// Channel 7 Input Range
/*
	Here place the rest of the registers you want to use...
*/
#define IR_10V    0x00  //+-10.24V
#define IR_5V   0x01  //+-5.12V
#define IR_2V  0x02  //+-2.56V

#define IR10V   	0x05  //0-10.24V
#define IR5V    0x06  //0-5.12V

#define CMD_READ 0x3f			// COMMAND READ BACK (Read-Only)

// --------------------------------------------------------------------------- //

#define CHNS_NUM_READ 2			// the number of channel you want to get the raw data (you also have to adjust the AUTO_SEQ_EN register value to match with the number of channel you like to read)

typedef struct {

	/* SPI */
	SPI_HandleTypeDef *spiHandle;
	GPIO_TypeDef 	  *csPinBank;
	uint16_t 		   csPin;

} ADS8688;


/*
 *
 * INITIALISATION
 *
 */
uint8_t ADS8688_Init(ADS8688 *ads, SPI_HandleTypeDef *spiHandle, GPIO_TypeDef *csPinBank, uint16_t csPin);

/*
 *
 * REGISTER AND COMAND LOW LEVEL FUNCTIONS
 *
 */
HAL_StatusTypeDef ADS_Prog_Read(ADS8688 *ads, uint8_t addr, uint8_t *data);
HAL_StatusTypeDef ADS_Prog_Write(ADS8688 *ads, uint8_t addr, uint8_t *data);
HAL_StatusTypeDef ADS_Cmd_Write(ADS8688 *ads, uint8_t cmd, uint8_t *data);


/*
 *
 * HIGHER LEVEL FUNCTIONS
 *
 */

HAL_StatusTypeDef ADS_Read_All_Raw(ADS8688 *ads, uint16_t *data);





#endif
