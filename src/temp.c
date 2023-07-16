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
 * 将GPIO复用为I2C1控制器
 */
void Temp_Control_Init(void)
{
    //将gpio38/39复用为普通功能
    gpio_disable(38);
    gpio_disable(39);

    //将gpio38/39复用为I2C1功能
    LS1B_MUX_CTRL0 |= 1 << 24;

    //初始化I2C1控制器
    ls1x_i2c_initialize(busI2C1);
    
    //使能水泥电阻加热管脚
    gpio_enable(CEMENT,DIR_OUT);
    
    //默认水泥电阻不加热
    Cement_Heat(CEMENT_OFF);
    
    //默认风扇不打开
    Fan_Speed_Control(0);

    return;
}


/*
 * 风扇控制
 * @pwm：转速（0-100）
 */
void Fan_Speed_Control(int pwm)
{
    set_lcd_brightness(busI2C1, pwm);
    
    return;
}


/*
 * 水泥电阻加热开关
 * on: CEMENT_ON -加热  CEMENT_OFF -不加热
 */
void Cement_Heat(int on)
{
    gpio_write(CEMENT, on);
    
    return;
}


/*
 * 温控模块的CT75温度传感器获取温度
 */
float Temp_Control_Get_Temp(void)
{
    float temp;

    temp = CT75_Get_Temp(busI2C1);
    return temp;
}
