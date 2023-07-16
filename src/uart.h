/*
 * uart.h
 *
 * created: 2021/4/30
 *  author: 
 */

#ifndef _UART_H
#define _UART_H

int count;
char buff[256];
char read[1024];
char read2[1024];

void UART5_Config_Init(void);
void UART4_Config_Init(void);
int UART5_Test(void);
void UART4_Test(void);
// char* UART4_Test(void);
char* UART5_Read(void);
void UART5_Write(char* buff);
char* UART4_Read(void);
void UART4_Write(char *buff);

#endif // _UART_H

