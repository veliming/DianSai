#ifndef ADS8688_H
#define ADS8688_H

// include the correct file according to you MCU
#include "stm32f4xx_hal.h"


// datasheet link
// https://www.ti.com/lit/ds/symlink/ads8668.pdf?ts=1620233637463&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FADS8668

// ----------------------- ADS Commands and Registers ------------------------ //
// Commands
#define NO_OP 0x00				/*鍦ㄩ�夊畾妯″紡涓嬬户缁搷浣滃湪璁惧鎿嶄綔鏈熼棿灏哠DI绾胯繛缁繚鎸佷负浣庣數骞筹紙鐩稿綋浜庡悜鎵�鏈�16浣嶅啓鍏�0锛�
								灏嗙户缁湪鏈�鍚庨�夋嫨鐨勬ā寮忥紙STDBY锛孭WR_DN鎴朅UTO_RST锛孧AN_Ch_n锛変笅杩涜璁惧鎿嶄綔銆�
								鍦ㄨ繖绉嶆ā寮忎笅锛岃澶囧皢閬靛惊绋嬪簭瀵勫瓨鍣紙鍦板潃01h鑷�3Ch锛変腑宸查厤缃殑鐩稿悓璁剧疆銆�*/
#define STDBY 0x82				/*寰呮満妯″紡鍣ㄤ欢鏀寔浣庡姛鑰楀緟鏈烘ā寮忥紙STDBY锛夛紝鍦ㄨ妯″紡涓嬶紝浠呴儴鍒嗙數璺柇鐢点��
								鍐呴儴鍩哄噯鐢靛帇婧愬拰缂撳啿鍣ㄦ湭鏂數锛屽湪閫�鍑篠TDBY妯″紡鏃讹紝鍙互鍦�20 渭s鍐呬负鍣ㄤ欢鍔犵數銆�
								閫�鍑篠TDBY妯″紡鏃讹紝绋嬪簭瀵勫瓨鍣ㄤ笉浼氬浣嶄负榛樿鍊笺��*/
#define PWR_DN 0x83				/*鎺夌數妯″紡锛圥WR_DN锛�
								鍣ㄤ欢鏀寔纭欢鍜岃蒋浠舵帀鐢垫ā寮忥紙PWR_DN锛夛紝鍦ㄨ妯″紡涓嬶紝鎵�鏈夊唴閮ㄧ數璺潎琚帀鐢碉紝鍖呮嫭鍐呴儴鍩哄噯鐢靛帇婧愬拰缂撳啿鍣ㄣ��
								濡傛灉璁惧鍦ㄥ唴閮ㄥ弬鑰冩ā寮忎笅杩愯锛圧EFSEL = 0锛夛紝鍒欓��鍑篜WR_DN妯″紡鍚庯紝璁惧鍔犵數骞惰浆鎹㈡墍閫夋ā鎷熻緭鍏ラ�氶亾鑷冲皯闇�瑕�15 ms鐨勬椂闂淬��
								璁惧鐨勭‖浠剁數婧愭ā寮忓湪RST / PD锛堣緭鍏ワ級閮ㄥ垎涓鏄庛��
								纭欢鍜岃蒋浠舵帀鐢垫ā寮忎箣闂寸殑涓昏鍖哄埆鍦ㄤ簬锛屽綋璁惧浠庣‖浠舵帀鐢靛敜閱掓椂锛岀▼搴忓瘎瀛樺櫒浼氶噸缃负榛樿鍊硷紝浣嗘槸褰撹澶囦粠杞欢鍞ら啋鏃讹紝绋嬪簭瀵勫瓨鍣ㄧ殑鍏堝墠璁剧疆浼氫繚鐣欐帀鐢点��*/
#define RST 0x85				/*閲嶇疆绋嬪簭瀵勫瓨鍣紙RST锛�
								鍣ㄤ欢鏀寔纭欢鍜岃蒋浠跺浣嶏紙RST锛夋ā寮忥紝鍦ㄨ妯″紡涓嬶紝
								鎵�鏈夌▼搴忓瘎瀛樺櫒鍧囧浣嶄负鍏堕粯璁ゅ�笺�備篃鍙互浣跨敤纭欢寮曡剼灏嗚澶囩疆浜嶳ST妯″紡*/
#define AUTO_RST 0xa0			/*鑷姩閫氶亾鍚敤
								鑷姩鎵弿鎵�鏈夋ā鎷熶俊閬撲笂鐨勮緭鍏ヤ俊鍙枫�傝嚜鍔ㄦ壂鎻忕殑閫氶亾搴忓垪鍙敱绋嬪簭瀵勫瓨鍣ㄤ腑鐨勮嚜鍔ㄦ壂鎻忛『搴忔帶鍒跺瘎瀛樺櫒锛�01h鑷�02h锛夐厤缃紱璇峰弬闃呯▼搴忓瘎瀛樺櫒鏄犲皠閮ㄥ垎銆�
								鍦ㄦ妯″紡涓嬶紝璁惧浠ュ崌搴忚繛缁惊鐜�氳繃鎵�閫夐�氶亾锛屼粠鏈�浣庨�氶亾寮�濮嬶紝杞崲绋嬪簭瀵勫瓨鍣ㄤ腑閫夋嫨鐨勬墍鏈夐�氶亾銆�
								搴忓垪瀹屾垚鍚庯紝璁惧杩斿洖鍒扮▼搴忓瘎瀛樺櫒涓殑鏈�浣庤鏁伴�氶亾锛屽苟閲嶅璇ュ簭鍒椼�傞�氳繃璁剧疆绋嬪簭瀵勫瓨鍣ㄧ殑鑼冨洿閫夋嫨瀵勫瓨鍣紝鍙互閰嶇疆鑷姩鎵弿搴忓垪涓瘡涓�氶亾鐨勮緭鍏ョ數鍘嬭寖鍥淬��*/
#define MAN_CH_0 0xc0				// Channel 0 manual input selected
#define MAN_CH_1 0xc4				// Channel 1 manual input selected
#define MAN_CH_2 0xc8				// Channel 2 manual input selected
#define MAN_CH_3 0xcc				// Channel 3 manual input selected
#define MAN_CH_4 0xd0				// Channel 4 manual input selected
#define MAN_CH_5 0xd4				// Channel 5 manual input selected
#define MAN_CH_6 0xd8				// Channel 6 manual input selected
#define MAN_CH_7 0xdc				/*鎵嬪姩閫氶亾n閫夋嫨锛圡AN_Ch_n锛�
									閫氳繃鍦ㄦ墜鍔ㄩ�氶亾n鎵弿妯″紡锛圡AN_Ch_n锛変腑杩涜鎿嶄綔锛�
									鍙互瀵硅澶囪繘琛岀紪绋嬩互杞崲鐗瑰畾鐨勬ā鎷熻緭鍏ラ�氶亾銆�
									閫氳繃鍦ㄥ懡浠ゅ瘎瀛樺櫒涓啓鍏ユ湁鏁堢殑鎵嬪姩閫氶亾n閫夋嫨鍛戒护锛圡AN_Ch_n锛夋潵瀹屾垚璇ョ紪绋�*/

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
