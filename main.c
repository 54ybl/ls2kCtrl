
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ls1b.h"
#include "mips.h"
#include "led.h"
#include "uart.h"
#include "ns16550.h"
#include "parse/parse.h"
#include "ls1x_fb.h"
#include "libc/lwmem.h"
#include "ls1b_gpio.h"
#include "i2c/gp7101.h"
#include "ls1x_i2c_bus.h"
#include "temp.h"
#include "ls1x-drv/include/i2c/ct75.h"

char LCD_display_mode[] = LCD_480x800;

//-------------------------------------------------------------------------------------------------
// BSP
//-------------------------------------------------------------------------------------------------

#include "bsp.h"

//-------------------------------------------------------------------------------------------------
// 主程序
//-------------------------------------------------------------------------------------------------

int main(void)
{
  int cnt = 0,i = 0,tm = 100;
  LED_IO_Config_Init();
  Temp_Control_Init();
  UART5_Config_Init();
  UART4_Config_Init();

  gpio_enable(54, DIR_OUT);
  gpio_write(54, 1);

  for (;;)
  {
    UART5_Test();
    UART4_Test(); // 串口控制函数
    if (cnt == 10)
    {
      i++;
      // printf("%d",i);
      cnt = 0;
    }
    cnt++;
    tm = UART5_Test();
    delay_ms(100);

    // UART5_Write(read);
    // UART4_Read();
    // UART4_Write(read2);
    // memset(read, 0, sizeof(read));
  }

  return 0;
}

// {"A":"01:01:17:00:00:01","I":"00","J":"01"}
// const char tmp[] = "{\"A\":\"01:01:17:00:00:01\",\"I\":\"00\",\"J\":\"01\"}";

// char *ptrMac;
// const char chMac = 'A';
// const char chDev = 'I';
// const char chOp = 'J';
// char result[100];
// char mac[17];
// char dev[10];
// char op[10];

// // 查找mac地址
// ptrMac = strchr(tmp, chMac);
// sprintf(result, "%s", ptrMac + 4);
// strncpy(mac, result, 17);
// printf("mac地址：%s", mac);
// memset(result, 0, strlen(result));
// // memset(ptrMac,0,strlen(ptrMac));

// // 识别设备型号
// if (mac[0] == 48 && mac[1] == 49)
// {
//   printf("设备型号：2K1000");
// }
// else if (mac[0] == 48 && mac[1] == 50)
// {
//   printf("设备型号：1B200");
// }
// else
// {
//   return 0;
// }
// // 识别设备类型
// if (mac[3] == 48 && mac[4] == 49)
// {
//   printf("设备类型：主机");
// }
// else if (mac[3] == 48 && mac[4] == 50)
// {
//   printf("设备类型：传感器");
// }
// else if (mac[3] == 48 && mac[4] == 51)
// {
//   printf("设备类型：执行器");
// }

// // 查找操作设备
// ptrMac = strchr(tmp, chDev);
// sprintf(result, "%s", ptrMac + 4);
// strncpy(dev, result, 2);
// printf("操作设备：%s", dev);
// memset(result, 0, strlen(result));

// if (dev[0] == 48 && dev[1] == 48)
// {
//   printf("操作设备：风扇");
// }
// else if (dev[0] == 48 && dev[1] == 49)
// {
//   printf("操作设备：电热器");
// }
// else
// {
//   return 0;
// }

// // 查找操作设备
// ptrMac = strchr(tmp, chOp);
// sprintf(result, "%s", ptrMac + 4);
// // printf("%s",result);
// strncpy(op, result, 2);
// printf("操作指令：%s", op);
// memset(result, 0, strlen(result));

// if (op[0] == 48 && op[1] == 48)
// {
//   printf("操作指令：关");
// }
// else if (op[0] == 48 && op[1] == 49)
// {
//   printf("操作指令：开");
// }
// else
// {
//   return 0;
// }

// char str1[80] = "hello", str2[40]= "world"; // 定义字符数组
// int i = 0, j = 0;        // 定义整型变量且赋初值

// while (str1[i] != '\0')  // 判断str1是不是最后一个字符
// {
//   i++;
// }
// while (str2[j] != '\0') // 判断str2是不是最后一个字符
// {
//   str1[i++] = str2[j++]; // 逐个拼接
// }
// str1[i] = '\0';
// printf("\n新的字符串是：%s\n", str1); // 输出拼接后的字符串
