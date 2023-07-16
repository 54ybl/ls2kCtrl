/*
 * temp.h
 *
 * created: 2021/5/25
 *  author: 
 */

#ifndef _TEMP_H
#define _TEMP_H


#define CEMENT      45      //����ˮ�����������

#define CEMENT_ON   1       //ˮ��������
#define CEMENT_OFF  0       //ˮ����費����

//��ʼ���¿�ģ��
void Temp_Control_Init(void);

/*
 * ���ȿ���
 * @pwm��ת�٣�0-100��
 */
void Fan_Speed_Control(int pwm);

/*
 * ˮ�������ȿ���
 * on: CEMENT_ON -����  CEMENT_OFF -������
 */
void Cement_Heat(int on);

/*
 * �¿�ģ���CT75�¶ȴ�������ȡ�¶�
 */
float Temp_Control_Get_Temp(void);

#endif // _TEMP_H

