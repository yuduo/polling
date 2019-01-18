
/*
视频处理单元的接口文件
*/
#pragma once

#ifdef ISDLL

#ifdef VQSMODULE_EXPORTS
#define VQS_API _declspec(dllexport)
#else
#define VQS_API _declspec(dllimport)
#endif // VQSMODULE_EXPORTS

#else
#define VQS_API
#endif

/************************************************************************/
/* 结果值，每项检测结果的值 
		   每项值都是0-100的范围
*/
/************************************************************************/
typedef struct tagResultValue
{
	BYTE bytColorCastValue;   //偏色值，阈值默认50，大于表示有偏色
	BYTE bytClarityValue;     //清晰度值，阈值默认为30，小于表示模糊
	BYTE bytBrightValue;      //亮度值，过亮阈值默认为80，过暗为20
	BYTE bytNoiseValue;		  //噪声值，阈值默认为50，大于表示有噪声干扰
	BYTE bytWaveValue;		  //条纹值，阈值默认为40，大于表示有条纹干扰
	BYTE bytMovedValue;       //运动值，用于云台检测，阈值默认为15大于表示有移动
	BYTE bytFreezeValue;	  //画面冻结，0：正常；1：冻结
	BYTE bytSignalValue;	  //视频信号,  0：正常，1：无信号
}RESULT_VALUE,*LPRESULT_VALUE;

// 图像格式
typedef enum {
	IF_BGR24 = 0,
	IF_UYVY = 1,		// U0-Y0-V0-Y1-U2-Y2-V2-Y3…
	IF_YV12 = 3,		// Y0-Y1…，V0-V1…，U0-U1…
	IF_RGB32 = 7,
	IF_RGB24 = 15,
	IF_YUV422 = 31,
	IF_YUV420 = 63		// Y0-Y1…，U0-U1…, V0-V1…
}ENUM_IMAGE_FORMAT;

typedef struct 
{
	BYTE* data[4];		// data[0]:Y/RGBdata  data[1]:U/V  data[2]:V/U  data[3]:reserved
	int width;			// 图像宽度
	int height;			// 图像高度
	int strideY;		// 行间距
	int strideCRCB;
	int format;			// 图像格式
} IMAGE_INFO, *LPIMAGE_INFO;

//#ifdef __cplusplus
//extern "C" {
//#endif

	/*****************************************************************
	函数：VQS_API_GetVQSResult
		  获取视频质量的结果
	参数：
		 lpszPicPath ：图片路径支持jpg和BMP等各种类型
		 lpResultOut： 检测结果
	返回值：
	     返回不为0则表示失败
	*******************************************************************/
	VQS_API long VQS_API_GetVQSResult(LPCTSTR lpszPicPath, LPRESULT_VALUE lpResultOut);

	/*****************************************************************
	函数：VQS_API_GetVQSResult
	获取视频质量的结果
	参数：
	psImgInfo1 ：图片1信息
	psImgInfo2 ：图片2信息
	lpResultOut：得到的检测结果
	bSaveImg： 是否保存检测图片(JPG)
	lpszPath： 图片保存路径
	nQuality： 图片压缩质量
	返回值：
	返回不为0则表示失败
	*******************************************************************/
	VQS_API long VQS_API_GetVQSResult(IMAGE_INFO* psImgInfo1, IMAGE_INFO* psImgInfo2, LPRESULT_VALUE lpResultOut, BOOL bSaveImg = FALSE, const char *lpszPath=NULL, int nQuality = 85);

//#ifdef __cplusplus
//}
//#endif