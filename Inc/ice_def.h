/**
* @file     ice_def.h    
* @brief    
* @note     
* @author   lizhongyu
* @date     2022/5/9
* @version  V1.0
* @par Copyright(c):  806277022@qq.com
* @par History:  2022/5/9 ��һ���汾V1.0
*/

#ifndef _ICE_DEF_H
#define _ICE_DEF_H


/************ Definition *********/
//--------------------------------------------------------------------------------------------------------------------//
#if ICE_UART /* ���� defines */
/* error definition */
typedef enum
{
    Ack_OK = 0,                     //communication normal
    Packtet_Size_Err,               //packet size error
    Head_Or_End_Err,                //head or end error
    Check_Err,                      //check error
    CMD_Err,                        //command error
}Ack_Flag_Type;

/* ice uart structure */
typedef struct
{
    //UART_HandleTypeDef *huart;      //pointer to stm32 huart x
    uint32_t huart;                 //gd32 usartx
    uint8_t rx[ICE_DMA_SIZE];   //ice uart receive data buffer(maxlength:256)
    uint8_t rx_flag;                //ice uart rx flag, 0:wait for receive, 1:received packet data
    uint8_t rx_len;                 //ice uart actually receive packet length
    uint8_t tx[ICE_DMA_SIZE];   //ice uart tx data buffer(maxlength:256)
    uint8_t error;                  //ice error
}IceUart;
#endif
//--------------------------------------------------------------------------------------------------------------------//
#define ICE_ASSERT(EXPR)                                                      \
if (!(EXPR))                                                                  \
{                                                                             \
    while (1);                                                                \
}


#endif //_ICE_DEF_H