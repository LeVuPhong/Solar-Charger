/*
 * process_command.c
 *
 *  Created on: Apr 12, 2021
 *      Author: levup
 */

/* Private includes ----------------------------------------------------------*/
#include "math.h"
#include "process_command.h"

#include "usart.h"
#include "ina2xx.h"
#include "adc.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define COMMAND_UART1	huart1
#define COMMAND_UART3	huart3

#define UART1_CH		1
#define UART3_CH		3
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
extern uint8_t Recieve_Buffer_1[32];
extern uint8_t Recieve_Lengh_1;
extern uint8_t Recieve_Status_1;

extern uint8_t Recieve_Buffer_3[32];
extern uint8_t Recieve_Lengh_3;
extern uint8_t Recieve_Status_3;
/* Private function prototypes -----------------------------------------------*/

/* Exported function prototypes ----------------------------------------------*/

uint8_t Is_CheckSum_16(uint8_t * pData, uint8_t len, uint8_t pCK_A, uint8_t pCK_B)
{
	uint8_t i;
	uint8_t ck_a=0xFF, ck_b=0xFF;

	for(i=0; i<len; i++)
	{
		ck_a ^= pData[i];
		ck_b ^= ck_a;
	}
	if(pCK_A != ck_a || pCK_B != ck_b) return 0;
	return 1;
}

void Calculate_CheckSum_16(uint8_t * pData, uint8_t len, uint8_t * pCK_A, uint8_t * pCK_B)
{
	uint8_t i;
	uint8_t ck_a=0xFF, ck_b=0xFF;

	for(i=0; i<len; i++)
	{
		ck_a ^= pData[i];
		ck_b ^= ck_a;
	}

	*pCK_A = ck_a;
	*pCK_B = ck_b;
}

void Command_Response_Add_Data(uint8_t Funtion, uint8_t ID_cmd, uint8_t * Data, uint8_t Error, uint8_t len, uint8_t uart_ch)
{
//	debug_write("Add Response [%.2X] [%.2X]\n", Funtion, Data);
//	uint8_t* msg = QueueTransmit.Item[QueueTransmit.Rear].Msg;
	uint8_t msg[32];
	uint8_t i;
//	uint8_t pos=0;
	msg[CMD_TYPE_INDEX] = CMD_TYPE_RESPONSE;
	msg[CMD_FUNTION_INDEX] = Funtion;
	msg[CMD_DATA_LENGTH_INDEX] = len+2;
	msg[CMD_ID_INDEX] = ID_cmd;
	msg[CMD_ERROR_CODE] = Error;

	Calculate_CheckSum_16(msg, msg[CMD_DATA_LENGTH_INDEX]+3, &msg[msg[CMD_DATA_LENGTH_INDEX]+CMD_CRC_A_INDEX], &msg[msg[CMD_DATA_LENGTH_INDEX]+CMD_CRC_B_INDEX]);

	for(i=0; i<len; i++)
	{
		msg[CMD_DATA_RES_INDEX+i] = Data[i];
	}

	if(uart_ch == UART1_CH)
	{
		HAL_UART_Transmit(&COMMAND_UART1, msg, msg[CMD_DATA_LENGTH_INDEX] + 5, 50);
	}
	else
	{
		HAL_UART_Transmit(&COMMAND_UART3, msg, msg[CMD_DATA_LENGTH_INDEX] + 5, 50);
	}
}
void Command_Response_Add_Msg(uint8_t Funtion, uint8_t ID_cmd, uint8_t Data, uint8_t Error, uint8_t uart_ch)
{
	uint8_t msg[16];
	msg[CMD_TYPE_INDEX] = CMD_TYPE_RESPONSE;
	msg[CMD_FUNTION_INDEX] = Funtion;
	msg[CMD_DATA_LENGTH_INDEX] = 3;
	msg[CMD_ID_INDEX] = ID_cmd;
	msg[CMD_ERROR_CODE] = Error;
	msg[CMD_DATA_RES_INDEX] = Data;

	Calculate_CheckSum_16(msg, msg[CMD_DATA_LENGTH_INDEX]+3, &msg[msg[CMD_DATA_LENGTH_INDEX]+CMD_CRC_A_INDEX], &msg[msg[CMD_DATA_LENGTH_INDEX]+CMD_CRC_B_INDEX]);

	if(uart_ch == UART1_CH)
		{
			HAL_UART_Transmit(&COMMAND_UART1, msg, msg[CMD_DATA_LENGTH_INDEX] + 5, 50);
		}
		else
		{
			HAL_UART_Transmit(&COMMAND_UART3, msg, msg[CMD_DATA_LENGTH_INDEX] + 5, 50);
		}
}

//
//void Command_Notifi_Add_Msg(uint8_t Funtion, uint8_t Data)
//{
//	uint8_t msg[20];
//	msg[CMD_TYPE_INDEX] = CMD_TYPE_NOTIFI;
//	msg[CMD_FUNTION_INDEX] = Funtion;
//	msg[CMD_DATA_LENGTH_INDEX] = 2;
//	msg[CMD_ID_INDEX] = Notifi_CMD_ID;
//	msg[CMD_DATA_NOTI_INDEX] = Data;
//	Queue_EnMessage(&QueueTransmit, msg, msg[CMD_DATA_LENGTH_INDEX]+3);
//}

void Process_Recieve_Command_1(void)
{
	if(Recieve_Status_1 == 0) return;

	Command_Response_Add_Msg(Recieve_Buffer_1[CMD_FUNTION_INDEX], Recieve_Buffer_1[CMD_ID_INDEX], Recieve_Buffer_1[CMD_DATA_REQ_INDEX], 0, UART1_CH);
}
