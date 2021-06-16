/*
 * process_command.h
 *
 *  Created on: Apr 12, 2021
 *      Author: levup
 */

#ifndef INC_PROCESS_COMMAND_H_
#define INC_PROCESS_COMMAND_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported defines ----------------------------------------------------------*/

/*Define Type Command*/
#define CMD_TYPE_REQUEST	0x02
#define CMD_TYPE_RESPONSE	0x03
#define CMD_TYPE_NOTIFI		0x04
#define FUNTION_Mask		0xF0

/* define format index*/
#define CMD_TYPE_INDEX			0
#define CMD_FUNTION_INDEX		1
#define CMD_DATA_LENGTH_INDEX	2
#define CMD_ID_INDEX			3
#define CMD_DATA_REQ_INDEX		4
#define CMD_DATA_RES_INDEX		5
#define CMD_DATA_NOTI_INDEX		4
#define CMD_ERROR_CODE			4
#define CMD_CRC_A_INDEX			3
#define CMD_CRC_B_INDEX			4

void Process_Recieve_Command_1(void);

#endif /* INC_PROCESS_COMMAND_H_ */
