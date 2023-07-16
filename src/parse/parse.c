/*
 * parse.c
 *
 * created: 2023/7/13
 *  author:
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ls1b.h"
#include "mips.h"
#include "led.h"
#include "uart.h"
#include "ns16550.h"
#include "parse/parse.h"


void parse(char *buff)
{
    //{"A":"01:01:17:00:00:01","I":"00","J":"01"}
    // const char tmp[] = "{\"A\":\"01:01:17:00:00:01\",\"I\":\"00\",\"J\":\"01\"}";
    char tmp[strlen(buff)];
    strncpy(tmp,buff,strlen(buff));
    printf("%d",strlen(tmp));

    char *ptrMac;
    const char chMac = 'A';
    const char chDev = 'I';
    const char chOp = 'J';
    char result[100];
    char mac[17];
    char dev[10];
    char op[10];
    printf("variable init.\r\n");
    printf("%s",tmp);
    printf("傻逼2312");

    // 查找mac地址
    ptrMac = strchr(tmp, chMac);
    sprintf(result, "%s", ptrMac + 4);
    strncpy(mac, result, 17);
    printf("mac:%s\r\n", mac);
    memset(result, 0, strlen(result));
    // memset(ptrMac,0,strlen(ptrMac));

    // 识别设备型号
    if (mac[0] == 48 && mac[1] == 49)
    {
        // printf("设备型号：2K1000");
        printf("device:2K1000,");
    }
    else if (mac[0] == 48 && mac[1] == 50)
    {
        printf("device:1B200,");
    }
    else
    {
        return 0;
    }
    // 识别设备类型
    if (mac[3] == 48 && mac[4] == 49)
    {
        printf("host device,");
    }
    else if (mac[3] == 48 && mac[4] == 50)
    {
        printf("sensor device,");
    }
    else if (mac[3] == 48 && mac[4] == 51)
    {
        printf("executer device,");
    }

    // 查找操作设备
    ptrMac = strchr(tmp, chDev);
    sprintf(result, "%s", ptrMac + 4);
    strncpy(dev, result, 2);
    // printf("operate:%s", dev);
    memset(result, 0, strlen(result));

    if (dev[0] == 48 && dev[1] == 48)
    {
        printf("execute:fan,");
    }
    else if (dev[0] == 48 && dev[1] == 49)
    {
        printf("execute:heat");
    }
    else
    {
        return 0;
    }

    // 查找操作设备
    ptrMac = strchr(tmp, chOp);
    sprintf(result, "%s", ptrMac + 4);
    // printf("%s",result);
    strncpy(op, result, 2);
    // printf("op:%s", op);
    memset(result, 0, strlen(result));

    if (op[0] == 48 && op[1] == 48)
    {
        printf("op:off");
    }
    else if (op[0] == 48 && op[1] == 49)
    {
        printf("op:on");
    }
    else
    {
        return 0;
    }
    return 0;
}
