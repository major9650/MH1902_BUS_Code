#include "mh523.h"
#include "iso14443_4.h"
#include "iso14443a.h"
#include "iso14443b.h"
#include "mifare.h"//射频卡相关头文件

#include "string.h"//C库函数 头文件

#include "gpio.h"

#include "ContactlessAPI.h"

//////////////////////////////////////////////////////////////////////
//获取卡号  从卡获取的所有数据存放在MH523结构体中
//pCardSn：卡号存放首地址
//返回：读卡状态码  0=成功  其他=失败
///////////////////////////////////////////////////////////////////////
unsigned char pro_GetCardID(unsigned char *pCardSn) // no indenped file
{
    signed char status = -1;

    status = pcd_request( 0x26, MH523.CardTypebuf);
	  //printf("req = %d\r\n",status);
    if(MI_OK==status)
    {
        status=pcd_cascaded_anticoll(PICC_ANTICOLL1, MH523.coll_position, MH523.UIDbuf);
        if(status == MI_OK)
        {
            status=pcd_cascaded_select(PICC_ANTICOLL1, MH523.UIDbuf,&MH523.SAK);
            if(status == MI_OK) //选卡成功
            {
                memcpy(pCardSn,MH523.UIDbuf,sizeof(MH523.UIDbuf));//拷贝卡号
                if(MH523.SAK == 0x08)//如果是M1 直接返回
                {
                    beep();
                    pcd_hlta();
                    return status;
                }
                else
                {
                    
                    status = pcd_rats_a(0, MH523.ATS,&MH523.ATSLength);	//发送RATS
                    if(status == MI_OK)
                    {
                        beep();
                        return status;
                    }

                    return status;
                }
            }
        }
    }
    return status;
}


//////////////////////////////////////////////////////////////////////
//获取卡类型  从卡获取的所有数据存放在MH523结构体中
//根据卡返回的SAK为依据判断卡类型
//返回：卡类
///////////////////////////////////////////////////////////////////////
unsigned char CaptureCardType(void) //返回卡类
{
    unsigned char status;
    unsigned char CardType = 0xFF;
    //memset(&MH523,0,sizeof(MH523));//清空缓存
    //status = pro_GetCardID(MH523.Block);
    if(1)
    {
        //printf("SAK:%02X\r\n",MH523.SAK);
        switch(MH523.SAK)
        {
        case 0x08:
            CardType = M1_CARD;
            break;
        case 0x25:
            CardType = CPUAPP;
            break;
        case 0x20:
            CardType = UNION_PAY;
            break;
        case 0x28:
            CardType = UNIONPAYCPU;
            break;
        default:
            CardType = 0xFF;
        }
    }
    return CardType;
}

//////////////////////////////////////////////////////////////////////
//APDU交互接口函数
//非接卡APDU交互接口
//
//返回：通信状态码
///////////////////////////////////////////////////////////////////////
unsigned char pro_APDU(unsigned char *sendbuf,unsigned short sendlen,unsigned char *recebuf,unsigned short *recelen)
{
    int status;

    status = ISO14443_4_HalfDuplexExchange(&g_pcd_module_info, sendbuf, sendlen, recebuf, (unsigned int *)recelen);

    //printf("sta= %d\r\n",status);
    return status;
}






