
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
// ������
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
    UART4_Test(); // ���ڿ��ƺ���
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

// // ����mac��ַ
// ptrMac = strchr(tmp, chMac);
// sprintf(result, "%s", ptrMac + 4);
// strncpy(mac, result, 17);
// printf("mac��ַ��%s", mac);
// memset(result, 0, strlen(result));
// // memset(ptrMac,0,strlen(ptrMac));

// // ʶ���豸�ͺ�
// if (mac[0] == 48 && mac[1] == 49)
// {
//   printf("�豸�ͺţ�2K1000");
// }
// else if (mac[0] == 48 && mac[1] == 50)
// {
//   printf("�豸�ͺţ�1B200");
// }
// else
// {
//   return 0;
// }
// // ʶ���豸����
// if (mac[3] == 48 && mac[4] == 49)
// {
//   printf("�豸���ͣ�����");
// }
// else if (mac[3] == 48 && mac[4] == 50)
// {
//   printf("�豸���ͣ�������");
// }
// else if (mac[3] == 48 && mac[4] == 51)
// {
//   printf("�豸���ͣ�ִ����");
// }

// // ���Ҳ����豸
// ptrMac = strchr(tmp, chDev);
// sprintf(result, "%s", ptrMac + 4);
// strncpy(dev, result, 2);
// printf("�����豸��%s", dev);
// memset(result, 0, strlen(result));

// if (dev[0] == 48 && dev[1] == 48)
// {
//   printf("�����豸������");
// }
// else if (dev[0] == 48 && dev[1] == 49)
// {
//   printf("�����豸��������");
// }
// else
// {
//   return 0;
// }

// // ���Ҳ����豸
// ptrMac = strchr(tmp, chOp);
// sprintf(result, "%s", ptrMac + 4);
// // printf("%s",result);
// strncpy(op, result, 2);
// printf("����ָ�%s", op);
// memset(result, 0, strlen(result));

// if (op[0] == 48 && op[1] == 48)
// {
//   printf("����ָ���");
// }
// else if (op[0] == 48 && op[1] == 49)
// {
//   printf("����ָ���");
// }
// else
// {
//   return 0;
// }

// char str1[80] = "hello", str2[40]= "world"; // �����ַ�����
// int i = 0, j = 0;        // �������ͱ����Ҹ���ֵ

// while (str1[i] != '\0')  // �ж�str1�ǲ������һ���ַ�
// {
//   i++;
// }
// while (str2[j] != '\0') // �ж�str2�ǲ������һ���ַ�
// {
//   str1[i++] = str2[j++]; // ���ƴ��
// }
// str1[i] = '\0';
// printf("\n�µ��ַ����ǣ�%s\n", str1); // ���ƴ�Ӻ���ַ���
