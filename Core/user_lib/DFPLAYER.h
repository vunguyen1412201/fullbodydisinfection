/******************************************************************************************************************
@File:  	DFPlayer Mini Module
@Author:  Khue Nguyen
@Website: khuenguyencreator.com
@Youtube: https://www.youtube.com/channel/UCt8cFnPOaHrQXWmVkk-lfvg
Huong dan su dung:
- Su dung thu vien HAL
- Khoi tao UART Baud 9600
- Khoi tao bien DFPlayer : DFPLAYER_Name MP3;
- Khoi tao DFPlayer do:
	DFPLAYER_Init(&MP3, &huart1);
- Su dung cac ham phai truyen dia chi cua DFPlayer do: 
	DFPLAYER_Play(&MP3);
******************************************************************************************************************/
#ifndef __DFPLAYER_H
#define __DFPLAYER_H
#include "stm32f1xx_hal.h"

typedef struct
{
	UART_HandleTypeDef* DFP_UART;
	uint8_t SendBuff[10];
	uint16_t Checksum;
}DFPLAYER_Name;

#define F_01	01
#define F_02	02
#define F_03	03
#define F_04	04
#define F_05	05
#define F_06	06
#define F_07	07
#define F_08	010
#define F_09	011
#define F_00	00

#define mp3_00	000 //phay
#define mp3_01	001 //nhiet do la
#define mp3_02	002 //yeucaukhukhuan
#define mp3_03	003 //da khukhuanxong
#define mp3_04	004
#define mp3_05	005
#define mp3_06	006
#define mp3_07	007
#define mp3_08	010
#define mp3_09	011

#define phay 000
#define nhietDoLa 001
#define yeuCauKhuKhuan 002
#define daKhuKhuanXong 003

#define DFP_PLAYTRACK 				0X12
#define DFP_NEXT 							0X01
#define DFP_PREV		  				0X02
#define DFP_SETVOLUME 				0X06
#define DFP_PLAY		 				 	0X0D
#define DFP_PAUSE		 				  0X0E
#define DFP_STOP					  	0X16
#define DFP_RANDOM 						0X18
#define DFP_PLAYFILEINFOLDER  0X0F

void DFPLAYER_Init(DFPLAYER_Name* MP3, UART_HandleTypeDef* UART);
void DFPLAYER_PlayTrack(DFPLAYER_Name* MP3, uint16_t num);
void DFPLAYER_Next(DFPLAYER_Name* MP3);
void DFPLAYER_Prev(DFPLAYER_Name* MP3);
void DFPLAYER_SetVolume(DFPLAYER_Name* MP3, uint16_t volume);
void DFPLAYER_Play(DFPLAYER_Name* MP3);
void DFPLAYER_Pause(DFPLAYER_Name* MP3);
void DFPLAYER_Stop(DFPLAYER_Name* MP3);
void DFPLAYER_RandomPlay(DFPLAYER_Name* MP3);
void DFPLAYER_PlayFileInFolder(DFPLAYER_Name* MP3, uint8_t folder, uint32_t num);
#endif
