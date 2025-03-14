/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {
	CAN_Polling,
	CAN_Interrupt
}CAN_ModeOperation;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define ToggleBit(Variable, BitNumber)	Variable ^= (1<<BitNumber)
#define SetBit(Variable, BitNumber)		Variable |= (1<<BitNumber)
#define ClearBit(Variable, BitNumber)	Variable &= ~(1<<BitNumber)

#define Acceleration				1
#define NoAcceleration				0

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */

void CAN_TX(uint32_t ID, uint8_t DataLength_Bytes, uint8_t* TxDataBuffer, CAN_ModeOperation ModeOperation);
void CAN_RxFilters_Init(uint32_t ID, uint32_t Mask);
void CAN_RX(uint32_t* ID, uint8_t* DataLength_Bytes, uint8_t* RxDataBuffer, CAN_ModeOperation ModeOperation);

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan);
void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan);
void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan);

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t TxData[8] = {0};
uint8_t RxData[8] = {0};

uint32_t RxSpeed = 0;
uint32_t RxID;
uint8_t RxDLC;

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
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */

  CAN_RxFilters_Init(0x3AB, 0x7FF);

  if ( HAL_CAN_ActivateNotification(&hcan, (CAN_IT_TX_MAILBOX_EMPTY | CAN_IT_RX_FIFO0_MSG_PENDING) ) != HAL_OK )
    {
  	  Error_Handler();
    }


  if ( HAL_CAN_Start(&hcan) != HAL_OK )
  {
	  Error_Handler();
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  TxData[0] = Acceleration;

  while (1)
  {
	  HAL_Delay(1000);
	  CAN_TX(0x30, 1, TxData, CAN_Interrupt);
	  ToggleBit(TxData[0], 0);

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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 1;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_6TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = ENABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void CAN_TX(uint32_t ID, uint8_t DataLength_Bytes, uint8_t* TxDataBuffer, CAN_ModeOperation ModeOperation)
{
	CAN_TxHeaderTypeDef TxHeader;
	TxHeader.StdId = ID;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.DLC = DataLength_Bytes;

	uint32_t TxMailbox;

	uint32_t TxMailboxesFreeLevel = HAL_CAN_GetTxMailboxesFreeLevel(&hcan);

	if (TxMailboxesFreeLevel != 0)
	{
		if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxDataBuffer, &TxMailbox) != HAL_OK)
		{
			Error_Handler();
		}

		if (ModeOperation == CAN_Polling)
		{
			while( HAL_CAN_IsTxMessagePending(&hcan, TxMailbox) == 1 );
		}
	}



}
void CAN_RxFilters_Init(uint32_t ID, uint32_t Mask)
{
	CAN_FilterTypeDef FilterConfig;
	FilterConfig.FilterIdHigh = (ID << 5);
	FilterConfig.FilterIdLow = 0x0000;
	FilterConfig.FilterMaskIdHigh = (Mask << 5);
	FilterConfig.FilterMaskIdLow = 0x0000;
	FilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	FilterConfig.FilterBank = 0;
	FilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	FilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	FilterConfig.FilterActivation = CAN_FILTER_ENABLE;

	if ( HAL_CAN_ConfigFilter(&hcan, &FilterConfig) != HAL_OK )
	{
		Error_Handler();
	}
}
void CAN_RX(uint32_t* ID, uint8_t* DataLength_Bytes, uint8_t* RxDataBuffer, CAN_ModeOperation ModeOperation)
{
	CAN_RxHeaderTypeDef RxHeader;

	uint8_t RxFifoFillLevel = HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO0);

	if (ModeOperation == CAN_Polling)
	{
		while(RxFifoFillLevel == 0);
	}

	if ( HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &RxHeader, RxDataBuffer) != HAL_OK )
		{
			Error_Handler();
		}
	*ID = RxHeader.StdId;
	*DataLength_Bytes = RxHeader.DLC;
}

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
{

}
void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan)
{

}
void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan)
{

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_RX(&RxID, &RxDLC, RxData, CAN_Interrupt);
	RxSpeed = RxData[0];
}

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
