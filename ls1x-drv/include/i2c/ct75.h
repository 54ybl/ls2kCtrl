/*
 * ct75.h
 *
 * created: 2021/4/30
 *  author: 
 */

#ifndef _CT75_H
#define _CT75_H

#ifdef	__cplusplus
extern "C" {
#endif

#define CT75_REG_TEMP           0x00
#define CT75_REG_CONFIG         0x01
#define CT75_REG_LOWTEMPSET     0x02
#define CT75_REG_HIGHTEMPSET    0x03
#define CT75_REGISTER_COUNT    	4

float CT75_Get_Temp(void *bus);

#ifdef	__cplusplus
}
#endif


#endif // _CT75_H

