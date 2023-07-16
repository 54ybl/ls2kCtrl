/*
 * temp.c
 *
 * created: 2021/4/30
 *  author: 
 */

#include "ls1b.h"
#include "ls1b_gpio.h"
#include "i2c/gp7101.h"
#include "ls1x_i2c_bus.h"
#include "temp.h"
#include "i2c/ct75.h"


/*
 * ��GPIO����ΪI2C1������
 */
void Temp_Control_Init(void)
{
    //��gpio38/39����Ϊ��ͨ����
    gpio_disable(38);
    gpio_disable(39);

    //��gpio38/39����ΪI2C1����
    LS1B_MUX_CTRL0 |= 1 << 24;

    //��ʼ��I2C1������
    ls1x_i2c_initialize(busI2C1);
    
    //ʹ��ˮ�������ȹܽ�
    gpio_enable(CEMENT,DIR_OUT);
    
    //Ĭ��ˮ����費����
    Cement_Heat(CEMENT_OFF);
    
    //Ĭ�Ϸ��Ȳ���
    Fan_Speed_Control(0);

    return;
}


/*
 * ���ȿ���
 * @pwm��ת�٣�0-100��
 */
void Fan_Speed_Control(int pwm)
{
    set_lcd_brightness(busI2C1, pwm);
    
    return;
}


/*
 * ˮ�������ȿ���
 * on: CEMENT_ON -����  CEMENT_OFF -������
 */
void Cement_Heat(int on)
{
    gpio_write(CEMENT, on);
    
    return;
}


/*
 * �¿�ģ���CT75�¶ȴ�������ȡ�¶�
 */
float Temp_Control_Get_Temp(void)
{
    float temp;

    temp = CT75_Get_Temp(busI2C1);
    return temp;
}
