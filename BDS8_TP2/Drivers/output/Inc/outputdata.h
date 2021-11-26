#ifndef _outputdata_H
#define _outputdata_H
#include <stdint.h>
extern float OutData[4];
void OutPut_Data(void);
void OutPut_DataAll(uint8_t channel,float *Pdata,uint32_t len);
#endif 
