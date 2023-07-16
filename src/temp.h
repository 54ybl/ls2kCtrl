/*
 * temp.h
 *
 * created: 2021/5/25
 *  author: 
 */

#ifndef _TEMP_H
#define _TEMP_H


#define CEMENT      45      //控制水泥电阻加热与否

#define CEMENT_ON   1       //水泥电阻加热
#define CEMENT_OFF  0       //水泥电阻不加热

//初始化温控模块
void Temp_Control_Init(void);

/*
 * 风扇控制
 * @pwm：转速（0-100）
 */
void Fan_Speed_Control(int pwm);

/*
 * 水泥电阻加热开关
 * on: CEMENT_ON -加热  CEMENT_OFF -不加热
 */
void Cement_Heat(int on);

/*
 * 温控模块的CT75温度传感器获取温度
 */
float Temp_Control_Get_Temp(void);

#endif // _TEMP_H

