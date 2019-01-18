
/*
��Ƶ����Ԫ�Ľӿ��ļ�
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
/* ���ֵ��ÿ��������ֵ 
		   ÿ��ֵ����0-100�ķ�Χ
*/
/************************************************************************/
typedef struct tagResultValue
{
	BYTE bytColorCastValue;   //ƫɫֵ����ֵĬ��50�����ڱ�ʾ��ƫɫ
	BYTE bytClarityValue;     //������ֵ����ֵĬ��Ϊ30��С�ڱ�ʾģ��
	BYTE bytBrightValue;      //����ֵ��������ֵĬ��Ϊ80������Ϊ20
	BYTE bytNoiseValue;		  //����ֵ����ֵĬ��Ϊ50�����ڱ�ʾ����������
	BYTE bytWaveValue;		  //����ֵ����ֵĬ��Ϊ40�����ڱ�ʾ�����Ƹ���
	BYTE bytMovedValue;       //�˶�ֵ��������̨��⣬��ֵĬ��Ϊ15���ڱ�ʾ���ƶ�
	BYTE bytFreezeValue;	  //���涳�ᣬ0��������1������
	BYTE bytSignalValue;	  //��Ƶ�ź�,  0��������1�����ź�
}RESULT_VALUE,*LPRESULT_VALUE;

// ͼ���ʽ
typedef enum {
	IF_BGR24 = 0,
	IF_UYVY = 1,		// U0-Y0-V0-Y1-U2-Y2-V2-Y3��
	IF_YV12 = 3,		// Y0-Y1����V0-V1����U0-U1��
	IF_RGB32 = 7,
	IF_RGB24 = 15,
	IF_YUV422 = 31,
	IF_YUV420 = 63		// Y0-Y1����U0-U1��, V0-V1��
}ENUM_IMAGE_FORMAT;

typedef struct 
{
	BYTE* data[4];		// data[0]:Y/RGBdata  data[1]:U/V  data[2]:V/U  data[3]:reserved
	int width;			// ͼ����
	int height;			// ͼ��߶�
	int strideY;		// �м��
	int strideCRCB;
	int format;			// ͼ���ʽ
} IMAGE_INFO, *LPIMAGE_INFO;

//#ifdef __cplusplus
//extern "C" {
//#endif

	/*****************************************************************
	������VQS_API_GetVQSResult
		  ��ȡ��Ƶ�����Ľ��
	������
		 lpszPicPath ��ͼƬ·��֧��jpg��BMP�ȸ�������
		 lpResultOut�� �����
	����ֵ��
	     ���ز�Ϊ0���ʾʧ��
	*******************************************************************/
	VQS_API long VQS_API_GetVQSResult(LPCTSTR lpszPicPath, LPRESULT_VALUE lpResultOut);

	/*****************************************************************
	������VQS_API_GetVQSResult
	��ȡ��Ƶ�����Ľ��
	������
	psImgInfo1 ��ͼƬ1��Ϣ
	psImgInfo2 ��ͼƬ2��Ϣ
	lpResultOut���õ��ļ����
	bSaveImg�� �Ƿ񱣴���ͼƬ(JPG)
	lpszPath�� ͼƬ����·��
	nQuality�� ͼƬѹ������
	����ֵ��
	���ز�Ϊ0���ʾʧ��
	*******************************************************************/
	VQS_API long VQS_API_GetVQSResult(IMAGE_INFO* psImgInfo1, IMAGE_INFO* psImgInfo2, LPRESULT_VALUE lpResultOut, BOOL bSaveImg = FALSE, const char *lpszPath=NULL, int nQuality = 85);

//#ifdef __cplusplus
//}
//#endif