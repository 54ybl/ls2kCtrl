/*
 * uart.c
 *
 * created: 2021/4/30
 *  author:
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uart.h"
#include "ls1b.h"
#include "ls1b_gpio.h"
#include "ns16550.h"
#include "stdio.h"
#include "led.h"
#include "string.h"
#include "uart.h"
#include "temp.h"
/*******************************************************************
 **函数名：UART5_set_IO
 **函数功能：初始化uart的IO口
 **形参：无
 **返回值：无
 **说明：   UART5_RX:60 -- 数据接收
            UART5_TX:61 -- 数据发送
 *******************************************************************/
void UART5_Config_Init(void)
{
    unsigned int BaudRate = 115200;
    ls1x_uart_init(devUART5, (void *)BaudRate); // 初始化串口
    ls1x_uart_open(devUART5, NULL);             // 打开串口
}

void UART4_Config_Init(void)
{
    unsigned int BaudRate = 115200;
    ls1x_uart_init(devUART4, (void *)BaudRate); // 初始化串口
    ls1x_uart_open(devUART4, NULL);             // 打开串口
}

char *UART5_Read()
{
    count = ls1x_uart_read(devUART5, buff, 1, NULL);
    if (count > 0)
    {
        printf("串口收到信息");
        // delay_ms(10);
    }
    else
    {
        return 0;
    }
    count = 0;
}

// int i = 1;
// int flag = 0;
// char temp[1024];
void UART5_Write(char *buff)
{
    if (count > 0)
    {
        // strcpy(buff,strlen(buff));
        // printf("%d:",i);
        ls1x_uart_write(devUART5, buff, strlen(buff), NULL);
        // strcpy(temp[i],buff);
    }
    // if(count = 0 && flag == 1);
    // {
    //     printf("接收完成");
    //     flag = 0;
    // }
}

char *UART4_Read(void)
{
    count = ls1x_uart_read(devUART4, buff, 1, NULL);
    strcpy(read2, buff);
    return read;
}

void UART4_Write(char *buff)
{
    if (count > 0)
    {
        // strcpy(buff,strlen(buff));
        ls1x_uart_write(devUART4, buff, strlen(buff), NULL);
    }
}

// 测试
int UART5_Test(void)
{
    // 接收数据
    // count = ls1x_uart_read(devUART5, buff, 1, NULL);
    // if (count > 0)
    // {
    //     // 发送数据
    //     ls1x_uart_write(devUART5, buff, strlen(buff), NULL);
    // }
    count = ls1x_uart_read(devUART5, buff, 256, NULL);
    // delay_ms(500);

    if (strncmp(buff, "0101", 4) == 0)
    {
        char tmp[8] = "0";
        char dev[8] = "0";
        char add[8] = "0";
        char exe[8] = "0";
        char op[8] = "0";
        strncpy(tmp, buff, 8);
        strncpy(dev, &tmp[0], 2);
        strncpy(add, &tmp[2], 2);
        strncpy(exe, &tmp[4], 2);
        strncpy(op, &tmp[6], 2);

        if (strncmp(dev, "01", 2) == 0)
        {
            printf("已连接至2K1000:");
            if (strncmp(add, "01", 2) == 0)
            {
                printf("%s\r\n", add);
                if (strncmp(exe, "00", 2) == 0)
                {
                    // 十六进制操作指令转为十进制
                    int number = 0, i = 0;
                    for (i = 0; op[i] != '\0'; i++)
                    {
                        if (op[i] >= '0' && op[i] <= '9')
                            number = number * 16 + op[i] - '0'; // 字符零在ASCII码表里面的值是48，所以数字字符的值减去数字字符'0'的值得到该数字字符的数值
                        else if (op[i] >= 'A' && op[i] <= 'F')
                            number = number * 16 + op[i] - 'A' + 10;
                        else if (op[i] >= 'a' && op[i] <= 'f')
                            number = number * 16 + op[i] - 'a' + 10;
                    }
                    // printf("%d",number);
                    Fan_Speed_Control(number);
                    printf("风扇转速:%d",number);
                }
                else if (strncmp(exe, "01", 2) == 0)
                {
                    if (strncmp(op, "00", 2) == 0)
                    {
                        Cement_Heat(CEMENT_OFF);
                        printf("加热关");
                    }

                    else if (strncmp(op, "01", 2) == 0)
                    {
                        Cement_Heat(CEMENT_ON);
                        printf("加热开");
                    }
                }
            }

            // char i = "00";
            // strncpy(i,&tmp[4],2);
            // switch (i)
            // {
            // case 01:
            //     printf("控制风扇\r\n");
            //     break;

            // default:
            //     break;
            // }
        }
    }
    else if (strncmp(buff, "time", 4) == 0)
    {
        char tmp[8] = "0";
        char time[8] = "0";
        strncpy(tmp,buff,7);
        strncpy(time,&buff[4],3);
        int number = 0, i = 0;
                    for (i = 0; time[i] != '\0'; i++)
                    {
                        if (time[i] >= '0' && time[i] <= '9')
                            number = number * 16 + time[i] - '0'; // 字符零在ASCII码表里面的值是48，所以数字字符的值减去数字字符'0'的值得到该数字字符的数值
                        else if (time[i] >= 'A' && time[i] <= 'F')
                            number = number * 16 + time[i] - 'A' + 10;
                        else if (time[i] >= 'a' && time[i] <= 'f')
                            number = number * 16 + time[i] - 'a' + 10;
                    }
        printf("延时:%dms",number);
        return number;
    }

    /////////////////
    // if (strncmp(buff, "010101", 6) == 0)
    // {
    //     LED_All_ON();
    //     Fan_Speed_Control(50);
    // }
    // if (strncmp(buff, "010100", 6) == 0)
    // {
    //     LED_All_OFF();
    //     Fan_Speed_Control(0);
    //     // char *t = &buff[4];
    //     char str[100];
    //     strncpy(str,&buff[4],2);
    //     printf("%s\r\n",str);
    // }
    // if (strncmp(buff, "010102", 6) == 0)
    // {
    //     LED_Waterfall();
    // }
    /////////////

    // if(strncmp(buff,"led_on",6) == 0) //比较前n个字节
    // {
    //     LED_All_ON();// 开启LED
    // }
    // if(strncmp(buff,"led_off",6) == 0)
    // {
    //     LED_All_OFF();//关闭LED
    // }
    // if(strncmp(buff,"led_demo",6)==0)
    // {
    //     LED_Waterfall();//流水灯
    //     LED_Waterfall();
    // }
}

// 测试
void UART4_Test(void)
{
    // 接收数据
    // count = ls1x_uart_read(devUART5, buff, 1, NULL);
    // if (count > 0)
    // {
    //     // 发送数据
    //     ls1x_uart_write(devUART5, buff, strlen(buff), NULL);
    // }
    count = ls1x_uart_read(devUART4, buff, 256, NULL);
    // delay_ms(500);

    if (strncmp(buff, "0101", 4) == 0)
    {
        char tmp[8] = "0";
        char dev[8] = "0";
        char add[8] = "0";
        char exe[8] = "0";
        char op[8] = "0";
        strncpy(tmp, buff, 8);
        strncpy(dev, &tmp[0], 2);
        strncpy(add, &tmp[2], 2);
        strncpy(exe, &tmp[4], 2);
        strncpy(op, &tmp[6], 2);

        if (strncmp(dev, "01", 2) == 0)
        {
            printf("已连接至2K1000:");
            if (strncmp(add, "01", 2) == 0)
            {
                printf("%s\r\n", add);
                if (strncmp(exe, "00", 2) == 0)
                {
                    // 十六进制操作指令转为十进制
                    int number = 0, i = 0;
                    for (i = 0; op[i] != '\0'; i++)
                    {
                        if (op[i] >= '0' && op[i] <= '9')
                            number = number * 16 + op[i] - '0'; // 字符零在ASCII码表里面的值是48，所以数字字符的值减去数字字符'0'的值得到该数字字符的数值
                        else if (op[i] >= 'A' && op[i] <= 'F')
                            number = number * 16 + op[i] - 'A' + 10;
                        else if (op[i] >= 'a' && op[i] <= 'f')
                            number = number * 16 + op[i] - 'a' + 10;
                    }
                    // printf("%d",number);
                    Fan_Speed_Control(number);
                    printf("风扇转速:%d",number);
                }
                else if (strncmp(exe, "01", 2) == 0)
                {
                    if (strncmp(op, "00", 2) == 0)
                    {
                        Cement_Heat(CEMENT_OFF);
                        printf("加热关");
                    }

                    else if (strncmp(op, "01", 2) == 0)
                    {
                        Cement_Heat(CEMENT_ON);
                        printf("加热开");
                    }
                }
            }
        }
    }
    else if (strncmp(buff, "time", 4) == 0)
    {
        char tmp[8] = "0";
        char time[8] = "0";
        strncpy(tmp,buff,7);
        strncpy(time,&buff[4],3);
        int number = 0, i = 0;
                    for (i = 0; time[i] != '\0'; i++)
                    {
                        if (time[i] >= '0' && time[i] <= '9')
                            number = number * 16 + time[i] - '0'; // 字符零在ASCII码表里面的值是48，所以数字字符的值减去数字字符'0'的值得到该数字字符的数值
                        else if (time[i] >= 'A' && time[i] <= 'F')
                            number = number * 16 + time[i] - 'A' + 10;
                        else if (time[i] >= 'a' && time[i] <= 'f')
                            number = number * 16 + time[i] - 'a' + 10;
                    }
        printf("延时:%dms",number);
        return number;
    }
}

// char *UART4_Test(void)
// {
//     // 接收数据
//     // count = ls1x_uart_read(devUART4, buff, 1, NULL);
//     // if (count > 0)
//     // {
//     //     // 发送数据
//     //     ls1x_uart_write(devUART4, buff, strlen(buff), NULL);
//     // }

//     ls1x_uart_read(devUART4, buff, 256, NULL);
//     delay_ms(500);

//     if (strncmp(buff, "010101", 6) == 0)
//     {
//         LED_All_ON();
//     }
//     if (strncmp(buff, "010100", 6) == 0)
//     {
//         LED_All_OFF();
//     }
//     if (strncmp(buff, "010102", 6) == 0)
//     {
//         LED_Waterfall();
//     }
// }
