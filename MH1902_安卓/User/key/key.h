#ifndef KEY_H
#define KEY_H
#include "mh523.h"
#include "mhscpu.h"
#include "delay.h"


#define KEY_LONG_DOWN_DELAY 100

typedef enum _KEY_STATUS_LIST
{
    KEY_NULL = 0x00,//无键按下
    KEY_SURE = 0x01,//确认态
    KEY_UP   = 0x02,//抬起
    KEY_DOWN = 0x04,//按下
    KEY_LONG = 0x08,//长按
} KEY_STATUS_LIST;

typedef enum _KEY_LIST
{
    KEY0=0,
    KEY1,
    KEY2,
    KEY3,
    KEY4,
    KEY5,
    KEY_NUM,
} KEY_LIST;

typedef struct _KEY_COMPONENTS
{
    unsigned char KEY_SHIELD;       //按键屏蔽0:屏蔽，1:不屏蔽
    unsigned int  KEY_COUNT;        //按键长按计数
    unsigned char KEY_LEVEL;        //虚拟当前IO电平，按下1，抬起0
    unsigned char KEY_DOWN_LEVEL;   //按下时IO实际的电平
    unsigned char KEY_STATUS;       //按键状态
    unsigned char KEY_EVENT;        //按键事件
    unsigned char (*READ_PIN)(void);//读IO电平函数
} KEY_COMPONENTS;
extern KEY_COMPONENTS Key_Buf[KEY_NUM];


void key_init();//按键IO口初始化
void Task_KEY_Scan(void);
unsigned char GetKey();
#endif



