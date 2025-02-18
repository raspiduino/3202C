/*****************************************************************************

File Name  : GYAD_Interface.h

Description: geeya advertisement interface.

Copyright (C) 2009 Chengdu Geeya Technology Co.,Ltd

Author: Archer 

Create Date:2010.09.09

* Date				Name			    Modification
* ---------		-----------			------------
* 2010.09.09		      Archer			     Created
* 2010.09.16		      Archer			     Modified
*  
*****************************************************************************/

#ifndef __GYAD_INTERFACE_H__
#define __GYAD_INTERFACE_H__

#ifdef  __cplusplus
extern "C" {
#endif

#define	NULL 	((void*)0)

typedef	signed char	GYADS8;
typedef	signed short	GYAD16;
typedef	int			GYADS32;
typedef	unsigned char	GYADU8;
typedef	unsigned short	GYADU16;
typedef	unsigned int	GYADU32;
typedef	unsigned char	GYADBOOL;       
typedef	void			GYADVOID;

/*函数返回值*/
typedef enum
{
	GYAD_ERROR_SUCCESS 	= 0, /*成功*/
	GYAD_ERROR_PARA		= 1, /*参数错误*/
	GYAD_ERROR_INVALID 	= 2, /*无效指针*/
	GYAD_ERROR_UNLOCK 	= 3, /*广告频点未锁定*/
	GYAD_ERROR_FAIL 		= 4, /*读/写NVRAM失败，内存分配失败*/
	GYAD_ERROR_UNKNOWN 	= 5, /*未知错误*/
}GYADErrorType_e;

/*广告类型*/
typedef enum
{
	GYAD_RESRC_TYPE_IFRAME 	= 0, /*I帧*/
	GYAD_RESRC_TYPE_JPG		= 1, /*JPG*/
	GYAD_RESRC_TYPE_GIF 		= 2, /*GIF*/
	GYAD_RESRC_TYPE_BMP 		= 3, /*BMP*/
	GYAD_RESRC_TYPE_TXT 		= 4, /*文字广告*/
}GYADResrcType_e;

typedef struct{
	GYADU8 cAdIndx;	/*广告位编号*/
	GYADU16 wSvcId;	/*服务号ID*/
	GYADU16 wTsId;	/*传输流ID*/
	GYADU32 wCurTime;	/*当前时间*/
}sGYADRelativeInfo_t;

/*广告信息*/
typedef struct{
	GYADU32 dwAdDisTime;/*显示时长*/
	GYADU32 dwAdStartTime;/*开始时间*/
	GYADU32 dwAdEndTime;	/*结束时间*/
	GYADU32 dwTxtColor;	/*文本颜色*/
	GYADU32 dwBgColor;	/*背景颜色*/
	GYADU32 dwAdLen; 	/*长度*/
	GYADU16 wAdX0;	/*广告坐标信息*/
	GYADU16 wAdY0;
	GYADU16 wAdX1;
	GYADU16 wAdY1;
	GYADU8 cAdType;	/*类型*/
	GYADU8* cAdData;	/*数据*/
}sGYAdInfo_t;

/**************************************************************
* Function: GYSTBAD_Malloc(GY_U32 dwMemSize)
* Descripe: Called by GYAD
* Para:
	dwMemSize: 需要分配的内存的大小
* Return: None
* Note: 
* Author: Archer
***************************************************************/
GYADVOID *GYSTBAD_Malloc(GYADU32 dwMemSize);


/**************************************************************
* Function: GYSTBAD_Free(GY_VOID* buffer)
* Descripe: Called by GYAD
* Para:
	buffer: 内存地址
* Return: None
* Note: 
* Author: Archer
***************************************************************/
GYADVOID GYSTBAD_Free(GYADVOID *buffer);


/**************************************************************
* Function: GYSTBAD_Memset(GY_VOID* pDestBuf, GY_U8 c, GY_U32 dwSize)
* Descripe: Called by GYAD
* Para:
	pDestBuf: 填充地址
	cData: 填充的数据
	dwSize: 填充的长度
* Return: None
* Note: 
* Author: Archer
***************************************************************/
GYADVOID GYSTBAD_Memset(GYADVOID *pDestBuf, GYADU32 c, GYADU32 dwSize);


/**************************************************************
* Function: GYSTBAD_Memcpy(GY_VOID* pDestBuf, GY_VOID* pSrcBuf, GY_U32 dwSize)
* Descripe: Called by GYAD
* Para:
	pDestBuf: 
	pSrcBuf: 
	dwSize: 
* Return: None
* Note: 
* Author: Archer
***************************************************************/
GYADVOID GYSTBAD_Memcpy(GYADVOID *pDestBuf, GYADVOID *pSrcBuf, GYADU32 dwSize);


GYADVOID GYSTBAD_Print(const GYADU8 *fmt, ...);


/**************************************************************
* Function: GYSTBAD_RequestPrivateData(GYADU8 cReqID, const GYADU8 *pcFilter, const GYADU8* pcMask, 
									GYADU8 cLen, GYADU16 wPid, GYADU8 byWaitSeconds);
* Descripe: Called by GYAD
* Para:
	cReqID: 收取私有表的请求号，与GYADSTB_PrivateDataCallback中的cReqID相同
	pcFilter: 当前过滤器的值，8字节
	pcFilter: 当前过滤器的掩码，8字节
	wLen: 取到的私有数据的长度
	wPid: 数据流的PID，，与GYADSTB_PrivateDataCallback中的wPid相同
	byWaitSeconds: 超时等待时间，单位为秒，为0则一直等待
* Return: Refer to GYADErrorType_e
* Note: 只要调用了本函数，就必须调用GYADSTB_PrivateDataGot，它们是一一对应的
* Author: Archer
***************************************************************/
GYADErrorType_e GYSTBAD_RequestPrivateData(GYADU8 cReqID, const GYADU8 *pcFilter, 
											const GYADU8 *pcMask, GYADU8 cLen, 
											GYADU16 wPid, GYADU8 byWaitSeconds);


/**************************************************************
* Function: GYSTBAD_RequestFree(GYADU8 cReqID)
* Descripe: Called by GYAD
* Para:
	cReqID: 
* Return: None
* Note: 释放filter
* Author: Archer
***************************************************************/
GYADVOID GYSTBAD_RequestFree(GYADU8 cReqID);

/**************************************************************
* Function: GYADSTB_SetTS(GYADVOID)
* Descripe: Called by GYAD
* Para:
	None
* Return: Refer to GYADErrorType_e
* Note: 锁定所在频点
* Author: Archer
***************************************************************/
GYADErrorType_e GYSTBAD_SetTS(GYADVOID);


/**************************************************************
* Function: GYSTBAD_SemaphoreLock(GYADVOID)
* Descripe: Called by GYAD
* Para:
	None
* Return: None
* Note: 
* Author: Archer
***************************************************************/
GYADVOID GYSTBAD_SemaphoreLock(GYADVOID);


/**************************************************************
* Function: GYSTBAD_SemaphoreUnlock(GYADVOID)
* Descripe: Called by GYAD
* Para:
	None
* Return: None
* Note: 
* Author: Archer
***************************************************************/
GYADVOID GYSTBAD_SemaphoreUnlock(GYADVOID);


/**************************************************************
* Function: GYSTBAD_SaveBootAd(sGYAdInfo_t *bootADInfo, GYADU8 bootADNum, GYADU8 bootADVer)
* Descripe: Called by GYAD
* Para:
	bootADInfo: 开机广告信息，需要保存
	bootADNum:   开机广告的个数
	bootADVer:   开机广告版本，需要保存
* Return: Refer to GYADErrorType_e
* Note:STB自行保存
* Author: Archer
***************************************************************/
GYADErrorType_e GYSTBAD_SaveBootAd(sGYAdInfo_t *bootADInfo, GYADU8 bootADNum, GYADU8 bootADVer);


/**************************************************************
* Function: GYSTBAD_GetBootVer(GYADU8 *ver)
* Descripe: Called by GYAD
* Para:
	version: 开机广告的版本
* Return: Refer to GYADErrorType_e
* Note: 
* Author: Archer
***************************************************************/
GYADErrorType_e GYSTBAD_GetBootVer(GYADU8 *version);


/**************************************************************
* Function: GYSTBAD_GetNvram(GYADU32 *pdwAddr, GYADU32 *len)
* Descripe: Called by GYAD
* Para:
	pdwAddr: NVRAM的起始地址
	len:   NVRAM的大小
* Return: Refer to GYADErrorType_e
* Note: �
* Author: Archer
***************************************************************/
GYADVOID GYSTBAD_GetNvram(GYADU32 *pdwAddr, GYADU32 *len);


/**************************************************************
* Function: GYSTBAD_ReadNvram(GYADU32 dwAddr, GYADU8 *data, GYADU32 len)
* Descripe: Called by GYAD
* Para:
       dwAddr: 起始地址
	data: 需要读取的数据
	len:   数据长度
* Return: Refer to GYADErrorType_e
* Note: 
* Author: Archer
***************************************************************/
GYADErrorType_e GYSTBAD_ReadNvram(GYADU32 dwAddr, GYADU8 *data, GYADU32 len);


/**************************************************************
* Function: GYSTBAD_WriteNvram(GYADU32 dwAddr, GYADU8 *data, GYADU32 len)
* Descripe: Called by GYAD
* Para:
       dwAddr: 起始地址
	data: 需要保存的数据
	len:   数据长度
* Return: Refer to GYADErrorType_e
* Note: 
* Author: Archer
***************************************************************/
GYADErrorType_e GYSTBAD_WriteNvram(GYADU32 dwAddr, GYADU8 *data, GYADU32 len);


/**************************************************************
* Function: GYSTBAD_ADExit(GYADVOID)
* Descripe: Called by GYAD
* Para:
	None
* Return: None
* Note: GYAD通知STB广告接收完毕
* Author: Archer
***************************************************************/
GYADVOID GYSTBAD_ADExit(GYADVOID);


/**************************************************************
* Function: GYADSTB_ADStart(GYADU16 wPid)
* Descripe: Called by STB
* Para:
	wPid: GYAD的PID
* Return: refer to GYADErrorType_e
* Note: STB通知GYAD开始接收广告
* Author: Archer
***************************************************************/
GYADErrorType_e GYADSTB_ADStart(GYADU16 wPid);


/**************************************************************
* Function: GYADSTB_PrivateDataGot(GYADU8 cReqID, GYADU8 bOK, GYADU16 wPid, const GYADU8 *pcReceiveData, GYADU32 dwLen)
* Descripe: Called by STB
* Para:
	cReqID: 收取私有表的请求号，与GYSTBAD_RequestPrivateData中的cReqID相同
	bOK: 收取数据是否成功,   1:成功   0:失败
	wPid: 数据流的PID，，与GYADSTB_PrivateDataCallback中的wPid相同
	pcReceiveData: 取到的私有数据
	dwLen: 取到的私有数据的长度
* Return: Refer to GYADErrorType_e
* Note: 只要调用了GYSTBAD_RequestPrivateData，就必须调用本函数，它们是一一对应的
* Author: Archer
***************************************************************/
GYADErrorType_e GYADSTB_PrivateDataGot(GYADU8 cReqID, GYADU8 bOK, GYADU16 wPid, const GYADU8 *pcReceiveData, GYADU32 dwLen);


/**************************************************************
* Function: GYADSTB_GetAdInfo(sGYADRelativeInfo_t sAdRelInfo, sGYAdInfo_t *sAdInfo)
* Descripe: Called by STB
* Para:
	sAdRelInfo: 广告关联信息
	sAdInfo: 广告信息
* Return: Refer to GYADErrorType_e
* Note: 
* Author: Archer
***************************************************************/
GYADErrorType_e GYADSTB_GetAdInfo(sGYADRelativeInfo_t sAdRelInfo, sGYAdInfo_t *sAdInfo);

#ifdef  __cplusplus
}
#endif

#endif

