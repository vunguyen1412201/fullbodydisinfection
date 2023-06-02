#ifndef MLX90614_H
#define MLX90614_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stm32f1xx_hal.h"
#include "i2c.h"

#define MLX90614_I2CADDR 0x5A<<1

// RAM
#define MLX90614_RAWIR1 0x04
#define MLX90614_RAWIR2 0x05
#define MLX90614_TA 0x06
#define MLX90614_TOBJ1 0x07
#define MLX90614_TOBJ2 0x08
// EEPROM
#define MLX90614_TOMAX 0x20
#define MLX90614_TOMIN 0x21
#define MLX90614_PWMCTRL 0x22
#define MLX90614_TARANGE 0x23
#define MLX90614_EMISS 0x24
#define MLX90614_CONFIG 0x25
#define MLX90614_ADDR 0x2E
#define MLX90614_ID1 0x3C
#define MLX90614_ID2 0x3D
#define MLX90614_ID3 0x3E
#define MLX90614_ID4 0x3F


double readObjectTempC(void);
double readAmbientTempC(void);
double readObjectTempF(void);
double readAmbientTempF(void);
unsigned int readEmissivityReg(void);
void writeEmissivityReg(unsigned int ereg);
double readEmissivity(void);
void writeEmissivity(double emissivity);

float readTemp(unsigned char reg);

unsigned int read16(unsigned char a);
void write16(unsigned char a, unsigned int v) ;
char crc8(char *addr, char len);
//uint8_t _addr;

#endif

