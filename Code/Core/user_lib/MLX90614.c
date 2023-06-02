#include "MLX90614.h"

/**
 * @brief Read the raw value from the emissivity register
 *
 * @return unsigned int The unscaled emissivity value or '0' if reading failed
 */
unsigned int readEmissivityReg(void) {
  return read16(MLX90614_EMISS);
}
/**
 * @brief Write the raw unscaled emissivity value to the emissivity register
 *
 * @param ereg The unscaled emissivity value
 */
void writeEmissivityReg(unsigned int ereg) {
  write16(MLX90614_EMISS, 0); // erase
  HAL_Delay(10);
  write16(MLX90614_EMISS, ereg);
  HAL_Delay(10);
}
/**
 * @brief Read the emissivity value from the sensor's register and scale
 *
 * @return double The emissivity value, ranging from 0.1 - 1.0 or NAN if reading
 * failed
 */
double readEmissivity(void) {
  unsigned int ereg = read16(MLX90614_EMISS);
  if (ereg == 0)
    return 0;
  return ((double)ereg) / 65535.0;
}
/**
 * @brief Set the emissivity value
 *
 * @param emissivity The emissivity value to use, between 0.1 and 1.0
 */
void writeEmissivity(double emissivity) {
  unsigned int ereg = (unsigned int)(0xffff * emissivity);

  writeEmissivityReg(ereg);
}

/**
 * @brief Get the current temperature of an object in degrees Farenheit
 *
 * @return double The temperature in degrees Farenheit or NAN if reading failed
 */
double readObjectTempF(void) {
  return (readTemp(MLX90614_TOBJ1) * 9 / 5) + 32;
}
/**
 * @brief Get the current ambient temperature in degrees Farenheit
 *
 * @return double The temperature in degrees Farenheit or NAN if reading failed
 */
double readAmbientTempF(void) {
  return (readTemp(MLX90614_TA) * 9 / 5) + 32;
}

/**
 * @brief Get the current temperature of an object in degrees Celcius
 *
 * @return double The temperature in degrees Celcius or NAN if reading failed
 */
double readObjectTempC(void) {
  return readTemp(MLX90614_TOBJ1);
}

/**
 * @brief Get the current ambient temperature in degrees Celcius
 *
 * @return double The temperature in degrees Celcius or NAN if reading failed
 */
double readAmbientTempC(void) {
  return readTemp(MLX90614_TA);
}

float readTemp(unsigned char reg) {
  float temp;

  temp = read16(reg);
  if (temp == 0)
    return 0;
  temp *= .02;
  temp -= 273.15;
  return temp;
}

/*********************************************************************/

unsigned int read16(unsigned char a) {
  unsigned char buffer[3];
  buffer[0] = a;
  // read two bytes of data + pec

  /*
   I2C_Master_Start();                                  // Start I2C protocol
   I2C_Master_Write(MLX90614_I2CADDR);                              // DS1307 address
   I2C_Master_Write(a);                                 // Send register address
   I2C_Master_RepeatedStart();                                  // Restart I2C
   I2C_Master_Write((MLX90614_I2CADDR)|1);                              // Initialize data read
   buffer[0]  = I2C_Master_Read(1);                         // Read month from register 5
   buffer[1]   = I2C_Master_Read(0);                         // Read year from register 6
   I2C_Master_Stop(); 
   */
  uint8_t reg[1];
  reg[0]=a;
 // HAL_I2C_Master_Transmit(&hi2c1,MLX90614_I2CADDR,reg,1,100);
 // HAL_I2C_Master_Receive(&hi2c1,MLX90614_I2CADDR,buffer,2,100);

  HAL_I2C_Mem_Read(&hi2c1, MLX90614_I2CADDR, a, 1, buffer, 2, 1000);


  // return data, ignore pec
  return ((unsigned int)(buffer[0])) | ((unsigned int)(buffer[1]) << 8);
}

char crc8(char *addr, char len)
// The PEC calculation includes all bits except the START, REPEATED START, STOP,
// ACK, and NACK bits. The PEC is a CRC-8 with polynomial X8+X2+X1+1.
{
  char crc = 0;
  while (len--) {
    char inbyte = *addr++;
    for (char i = 8; i; i--) {
      char carry = (crc ^ inbyte) & 0x80;
      crc <<= 1;
      if (carry)
        crc ^= 0x7;
      inbyte <<= 1;
    }
  }
  return crc;
}

void write16(unsigned char a, unsigned int v) 
{
  unsigned char buffer[4];
  unsigned char pec;
  buffer[0] = MLX90614_I2CADDR;
  buffer[1] = a;
  buffer[2] = v & 0xff;
  buffer[3] = v >> 8;

  pec = crc8(buffer, 4);

  buffer[0] = buffer[1];
  buffer[1] = buffer[2];
  buffer[2] = buffer[3];
  buffer[3] = pec;

  //HAL_I2C_Master_Transmit(&hi2c1,MLX90614_I2CADDR,buffer,4,100);
  HAL_I2C_Mem_Read(&hi2c1, MLX90614_I2CADDR, a, 1, buffer, 4, 1000);
  /*
  I2C_Master_Start();           
  I2C_Master_Write(buffer[0]);                 
  I2C_Master_Write(buffer[1]); 
  I2C_Master_Write(buffer[2]); 
  I2C_Master_Write(buffer[3]); 
  I2C_Master_Stop();
  */
}
