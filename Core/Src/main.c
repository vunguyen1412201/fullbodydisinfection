/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "../user_lib/lcd_i2c.h"
#include "../user_lib/MLX90614.h"
#include "../user_lib/DFPLAYER.h"



/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char txt[30]="";
DFPLAYER_Name MP3;

//35.5
void Sound1()
{
	int t=900;
	//36,5
	DFPLAYER_PlayFileInFolder(&MP3,F_03,mp3_03); HAL_Delay(1200);
	DFPLAYER_PlayFileInFolder(&MP3,F_05,mp3_05); HAL_Delay(t);
	DFPLAYER_PlayFileInFolder(&MP3,F_00,mp3_00); HAL_Delay(t);
	DFPLAYER_PlayFileInFolder(&MP3,F_05,mp3_05); HAL_Delay(t);
}

//37.3
void Sound2()
{
	int t=900;
	//37,5
	DFPLAYER_PlayFileInFolder(&MP3,F_03,mp3_03); HAL_Delay(1200);
	DFPLAYER_PlayFileInFolder(&MP3,F_07,mp3_07); HAL_Delay(t);
	DFPLAYER_PlayFileInFolder(&MP3,F_00,mp3_00); HAL_Delay(t);
	DFPLAYER_PlayFileInFolder(&MP3,F_03,mp3_03); HAL_Delay(t);
}

#define ON 1
#define OFF 0
#define RL1(stt) HAL_GPIO_WritePin(RL1_GPIO_Port, RL1_Pin, stt)
#define RL2(stt) HAL_GPIO_WritePin(RL2_GPIO_Port, RL2_Pin, stt)
#define RL3(stt) HAL_GPIO_WritePin(RL3_GPIO_Port, RL3_Pin, stt)
#define RL4(stt) HAL_GPIO_WritePin(RL4_GPIO_Port, RL4_Pin, stt)
#define ReadTC1 HAL_GPIO_ReadPin(TC2_GPIO_Port, TC2_Pin)
#define ReadTC2 HAL_GPIO_ReadPin(TC1_GPIO_Port, TC1_Pin)
#define ReadBtnOk HAL_GPIO_ReadPin(BTN_OK_GPIO_Port, BTN_OK_Pin)
#define ReadBtnUp HAL_GPIO_ReadPin(BTN_UP_GPIO_Port, BTN_UP_Pin)
#define ReadBtnDown HAL_GPIO_ReadPin(BTN_DOWN_GPIO_Port, BTN_DOWN_Pin)

float nhiet_do=0;

void delay_user(int t);

void delay_user(int t)
{
	while(t>0)
	{
		t--;
		HAL_Delay(1);
		if(!ReadTC2)
		{
		  RL4(ON);
		  HAL_Delay(50);
		}
		else RL4(OFF);
		if(!(ReadTC1)) break;
		else if(ReadBtnDown || ReadBtnOk || ReadBtnUp) break;
	}
}

void phatAmThanhNhietDo(float t);
void phatAmThanhNhietDo(float t)
{
	float t_temp=t*100;
	DFPLAYER_PlayFileInFolder(&MP3,F_01,nhietDoLa); HAL_Delay(2000); //phay
	mapSound((int)t_temp/1000%10, 1200);
	mapSound((int)t_temp/100%10, 1000);
	DFPLAYER_PlayFileInFolder(&MP3,F_01,phay); HAL_Delay(1000); //phay
	mapSound((int)t_temp/10%10, 1000);
	//mapSound(t_temp%10, 1000);
}

void mapSound(int p,int t);
void mapSound(int p,int t)
{
	switch(p)
	{
		case 0: DFPLAYER_PlayFileInFolder(&MP3,F_00,mp3_00); HAL_Delay(t); break;
		case 1: DFPLAYER_PlayFileInFolder(&MP3,F_00,mp3_01); HAL_Delay(t); break;
		case 2: DFPLAYER_PlayFileInFolder(&MP3,F_00,mp3_02); HAL_Delay(t); break;
		case 3: DFPLAYER_PlayFileInFolder(&MP3,F_00,mp3_03); HAL_Delay(t); break;
		case 4: DFPLAYER_PlayFileInFolder(&MP3,F_00,mp3_04); HAL_Delay(t); break;
		case 5: DFPLAYER_PlayFileInFolder(&MP3,F_00,mp3_05); HAL_Delay(t); break;
		case 6: DFPLAYER_PlayFileInFolder(&MP3,F_00,mp3_06); HAL_Delay(t); break;
		case 7: DFPLAYER_PlayFileInFolder(&MP3,F_00,mp3_07); HAL_Delay(t); break;
		case 8: DFPLAYER_PlayFileInFolder(&MP3,F_00,mp3_08); HAL_Delay(t); break;
		case 9: DFPLAYER_PlayFileInFolder(&MP3,F_00,mp3_09); HAL_Delay(t); break;
		default: break;
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  RL1(OFF);
  RL2(OFF);
  RL3(OFF);
  RL4(OFF);

  HAL_Delay(2000);
  lcd_init();
  HAL_Delay(100);
  int count=0;
  int count1=0;
  int tempSet=36;
  lcd_clear(); lcd_string(1, 1, "Run application");
	DFPLAYER_Init(&MP3,&huart2);
	DFPLAYER_SetVolume(&MP3,30);
	HAL_Delay(500);
	lcd_clear();

  while(1)
  {

	  nhiet_do=readObjectTempC();
	  sprintf(txt,"Temp: %0.1f",nhiet_do);
	  lcd_string(1, 1, txt);
	  sprintf(txt,"Count: %d",count);
	  lcd_string(2,1,txt);

	  if(!(ReadTC1))
	  {
		  HAL_Delay(100);
		  sprintf(txt,"Temp: %0.1f",nhiet_do);
		  lcd_string(1, 1, txt);
		  count++;
		  sprintf(txt,"Count: %d",count);
		  lcd_string(2,1,txt);

		  phatAmThanhNhietDo(nhiet_do);

		  if(nhiet_do>=tempSet)
		  {
			  lcd_clear();
			  lcd_string(1, 2, "CANH BAO NHIET");
			  lcd_string(2, 6, "DO CAO");
		  }
		  else
		  {
			  lcd_clear();
			  lcd_string(1,2, "NHIET DO BINH");
			  lcd_string(2,6, "THUONG");
		  }

		  HAL_Delay(3000);
		  lcd_clear(); lcd_string(1, 3, "YEU CAU KHU"); lcd_string(2, 6, "KHUAN");
		  DFPLAYER_PlayFileInFolder(&MP3,F_01,yeuCauKhuKhuan); HAL_Delay(1200);
		  HAL_GPIO_WritePin(RL3_GPIO_Port, RL3_Pin, 1);
		  HAL_Delay(12000);

		  HAL_GPIO_WritePin(RL3_GPIO_Port, RL3_Pin, 0);
		  lcd_clear(); lcd_string(1, 3, "DA KHU KHUAN"); lcd_string(2, 7, "XONG");
		  DFPLAYER_PlayFileInFolder(&MP3,F_01,daKhuKhuanXong); HAL_Delay(1200);
		  HAL_Delay(3000);
		  while(!HAL_GPIO_ReadPin(TC2_GPIO_Port, TC2_Pin));
		  lcd_clear();
		  sprintf(txt,"Temp: %0.1f",nhiet_do);
		  lcd_string(1, 1, txt);
		  sprintf(txt,"Count: %d",count);
		  lcd_string(2,1,txt);
	  }//if(!(ReadTC1))


	  if(ReadBtnOk)
	  {
		  lcd_clear();
		  sprintf(txt,"Set temp: %d",tempSet);
		  lcd_string(1, 1, txt);
		  while(ReadBtnOk);
		  while(1)
		  {
			  if(ReadBtnUp)
			  {
				  sprintf(txt,"Set temp: %d",tempSet++);
				  lcd_string(1, 1, txt);
				  while(ReadBtnUp);
			  }
			  else if(ReadBtnDown)
			  {
				  sprintf(txt,"Set temp: %d",tempSet--);
				  lcd_string(1, 1, txt);
				  while(ReadBtnDown);
			  }
			  HAL_Delay(10);
			  if(HAL_GPIO_ReadPin(BTN_OK_GPIO_Port, BTN_OK_Pin)) break;
		  }
		  lcd_clear();
		  sprintf(txt,"Temp: %0.1f",nhiet_do);
		  lcd_string(1, 1, txt);
		  sprintf(txt,"Count: %d",count);
		  lcd_string(2,1,txt);
		  while(ReadBtnOk);
	  }

	  delay_user(1000);
	  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED_STT_Pin);
  }//while





  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  float nhiet_do=readObjectTempC();
	  sprintf(txt,"Nhiet do: %0.2f",nhiet_do);
	  lcd_string(1, 1, txt);
	  HAL_GPIO_TogglePin(LED_STT_GPIO_Port, LED_STT_Pin);
	  HAL_Delay(500);


	  //HAL_Delay(100);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
