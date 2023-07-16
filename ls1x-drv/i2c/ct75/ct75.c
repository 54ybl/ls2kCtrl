/*
 * ct75.c
 *
 * created: 2021/4/30
 *  author: 
 */

#include "bsp.h"

#ifdef CT75_DRV

#include <stdio.h>
#include <errno.h>
#include <stdint.h>

#include "ls1x_io.h"
#include "ls1x_i2c_bus.h"
#include "../ls1x_i2c_bus_hw.h"

#if defined(LS1B)
#include "ls1b.h"
#elif defined(LS1C)
#include "ls1c.h"
#else
#error "No Loongson1x SoC defined."
#endif

#include "i2c/ct75.h"

//-----------------------------------------------------------------------------

#define CT75_ADDRESS          0x48      //1001 000

#define CT75_BAUDRATE         1000000

//-----------------------------------------------------------------------------

#define CHECK_DONE(rt) \
	do {               \
        if (0 != rt)   \
            goto lbl_done; \
    } while (0);
    
//-----------------------------------------------------------------------------
// driver routine
//-----------------------------------------------------------------------------

static int CT75_write_two_byte(LS1x_I2C_bus_t *pIIC, uint16_t regVal, uint8_t regNum)
{
    int rt, rw_cnt;
	unsigned char buf[4] = { 0 };
	
	if (regNum >= CT75_REGISTER_COUNT)
		return -1;

	/* start transfer */
	rt = ls1x_i2c_send_start(pIIC, CT75_ADDRESS);
	CHECK_DONE(rt);

	/* set transfer mode */
	rt = ls1x_i2c_ioctl(pIIC, IOCTL_SPI_I2C_SET_TFRMODE, (void *)CT75_BAUDRATE);
	CHECK_DONE(rt);

	/* address device, FALSE = WRITE */
	rt = ls1x_i2c_send_addr(pIIC, CT75_ADDRESS, false);
	CHECK_DONE(rt);
	
	buf[0] = regNum;
	buf[1] = regVal >> 8;
	buf[2] = regVal & 0xFF;
	rw_cnt = ls1x_i2c_write_bytes(pIIC, buf, 3);
	if (rw_cnt < 0)
		rt = rw_cnt;
	CHECK_DONE(rt);
	
lbl_done:
	/* terminate transfer */
	ls1x_i2c_send_stop(pIIC, CT75_ADDRESS);
	
	return rt;
}


static int CT75_read_two_byte(LS1x_I2C_bus_t *pIIC, uint16_t *regVal, uint8_t regNum)
{
    int rt, rw_cnt;
	unsigned char buf[4] = { 0 };

	if (regNum >= CT75_REGISTER_COUNT)
		return -1;

	/* start transfer */
	rt = ls1x_i2c_send_start(pIIC, CT75_ADDRESS);
	CHECK_DONE(rt);

	/* set transfer mode */
	rt = ls1x_i2c_ioctl(pIIC, IOCTL_SPI_I2C_SET_TFRMODE, (void *)CT75_BAUDRATE);
	CHECK_DONE(rt);

	/* address device, FALSE = WRITE */
	rt = ls1x_i2c_send_addr(pIIC, CT75_ADDRESS, false);
	CHECK_DONE(rt);

	buf[0] = regNum;
	rw_cnt = ls1x_i2c_write_bytes(pIIC, buf, 1);
	if (rw_cnt < 0)
		rt = rw_cnt;
	CHECK_DONE(rt);

	/* restart - address device address device, TRUE = READ
	 */
	rt = ls1x_i2c_send_addr(pIIC, CT75_ADDRESS, true);
	CHECK_DONE(rt);

	/*
	 * fetch register data
	 */
	rw_cnt = ls1x_i2c_read_bytes(pIIC, buf+1, 2);
    if (rw_cnt < 0)
		rt = rw_cnt;
	CHECK_DONE(rt);
//    printk("rw_cnt = %d,buf[1] = 0x%x,buf[2] = 0x%x\n",rw_cnt,buf[1],buf[2]);
	*regVal = ((uint16_t)buf[1] << 8) + buf[2];

lbl_done:
	/* terminate transfer */
	ls1x_i2c_send_stop(pIIC, CT75_ADDRESS);

	return rt;
}


//-----------------------------------------------------------------------------
// user api
//-----------------------------------------------------------------------------

/*
 * CT75获取当前温度值
 */
float CT75_Get_Temp(void *bus)
{
    uint16_t tmp;
    float temp;
    int high,low;
    
    if(CT75_read_two_byte(bus, &tmp, CT75_REG_TEMP) < 0){
        printk("CT75_REG_TEMPERATE read fail\n");
        return 0;
    }
    else
    {
        tmp = (tmp >> 4) & 0xFFF;
	    if(tmp > 0x7ff)
        {
	       high = -(0xfff-tmp+1) / 16;
	       low = ((0xfff-tmp+1)%16)*625;
	    }
        else
        {
	       high = tmp/16;
	       low = (tmp%16)*625;
	    }
	    temp = (float)high + (float)low / 10000;
//	    printk("temp = %.02f\n",temp);
	    return temp;
    }
}



#endif
