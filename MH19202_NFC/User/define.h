/**
****************************************************************
* @file define.h
*
* @brief  define宏控制和部分变量定义
*
* @author
*
*
****************************************************************
*/
#ifndef DEFINE_H
#define DEFINE_H


/*
 * VESRION DESCRIPTION
 ****************************************************************
 */

//#define VERSION "1.0.0"
// 1. 完成N12 SDK的编写
// 2. 更新软件，加入LPCD测试和COS指令测试功能
//#define VERSION "1.1.0"
// 1. 优化0x3B寄存器配置
//#define VERSION "1.2.0"
// 1. 优化35/3b上电初始化配置
//#define VERSION "1.3.0"
// 1. 优化SNR
//#define VERSION "1.4.0"
// 1. 优化注释
#define VERSION "1.5.0"
// 1. 优化高速率通信配置

#define MOTHERBOARD_V20	    1	//运行于新底板V2.0
#define SIKAI_V10		    0	//运行于与SIKAI兼容的小板

#define NFC_DEBUG		    0	// printf打印控制开关

#define POWERON_POLLING     1   //上电即开始自动A/B polling
#define INT_USE_CHECK_REG   1	//中断检测使用查询07寄存器的irq bit的方式，而不是使用查询中断管脚


/*********************系统时钟配置************************/
//#define FOSC 11059200ul
#if (MOTHERBOARD_V20)
#define FOSC 22118400ul
#else
#define FOSC 11059200ul
#endif

#if (MOTHERBOARD_V20 + SIKAI_V10 != 1)
#error("multi board selected!")
#endif

/************************PC机软件与下位机软件通信命令字**************************/
#define COM_PKT_CMD_READ_REG 		      1
#define COM_PKT_CMD_WRITE_REG	          2

#define COM_PKT_CMD_QUERY_MODE		      0x0D	//是否是手动模式，而不是自动寻卡模式
#define COM_PKT_CMD_CHIP_RESET            0x0E  //软复位数字芯片
#define COM_PKT_CMD_CARD_TYPE		      0x0F
#define COM_PKT_CMD_REQ_SELECT		      0x10
#define COM_PKT_CMD_HALT			      0x11  //发送Halt指令
#define COM_PKT_CMD_STATISTICS		      0x12  //统计信息
#define COM_PKT_CMD_LPCD			      0x13  //LPCD 功能
#define COM_PKT_CMD_LPCD_CONFIG_TEST      0x16  //测试LPCD功能
#define COM_PKT_CMD_LPCD_CONFIG_TEST_STOP 0x17

#define DATA
#define IDATA
#define XDATA
#define CODE
#define REENTRANT

typedef unsigned int  u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef unsigned char  bool;


#endif
