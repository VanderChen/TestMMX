// TestMMX.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mmx.h"
#include "NoMMx.h"
#include <iostream>

using namespace std;


void Test_MMX(int intWidth, int intHeight, int RGB_Bit);
void Test_NoMMX(int intWidth, int intHeight, int RGB_Bit);
int main()
{
	DWORD start_time = GetTickCount();

	Test_MMX(640, 480, 24);

	DWORD end_time = GetTickCount();

	cout << "ʹ��MMX��ʱ��" << (end_time - start_time) << "ms!" << endl;//�������ʱ��

	start_time = GetTickCount();

	Test_NoMMX(640, 480, 24);

	end_time = GetTickCount();

	cout << "��ʹ��MMX��ʱ��" << (end_time - start_time) << "ms!" << endl;
	return 0;
}

void Test_MMX(int intWidth, int intHeight, int RGB_Bit)
{
	_try{
		_asm EMMS
	}
		_except(EXCEPTION_EXECUTE_HANDLER) {
	}
	HDC hDC;
	LPBITMAPINFO lpInfo;                   //ָ��ͼƬ����ĳ�ָ������
	int intSize, i;
	LPBYTE  lpBuf1, lpBuf2, lpBuf;              //ָ���ֽ�(��)��ָ��
	HFILE Picture1, Picture2;
	Picture1 = _lopen("D:\\XJTU\\ComputerOrganization\\MMX\\TestMMX\\TestMMX\\test_24.bmp", OF_READ);          //���ش��ļ��ľ��
	Picture2 = _lopen("D:\\XJTU\\ComputerOrganization\\MMX\\TestMMX\\TestMMX\\test2_24.bmp", OF_READ);
	intSize = GetFileSize((HANDLE)Picture1, NULL);//�����ļ�����		
	lpBuf1 = (LPBYTE)LocalAlloc(LPTR, intSize);//�����·�����ڴ��ַ,,�Ӷ��з���ָ����С���ֽ���
	lpBuf2 = (LPBYTE)LocalAlloc(LPTR, intSize);
	lpBuf = (LPBYTE)LocalAlloc(LPTR, intSize);

	_lread(Picture1, lpBuf1, intSize);      //ָ��һ���ڴ���ָ�룬���ݽ���������ڴ��
	_lread(Picture2, lpBuf2, intSize);
	_lclose(Picture1);  //�ͷ��ļ����
	_lclose(Picture2);
	memcpy(lpBuf, lpBuf1, intSize);
	lpInfo = (LPBITMAPINFO)(lpBuf + 0x0e);
	hDC = GetDC(NULL);
	for (i = 0; i<255; i++)    //Ĭ����ͼ��255�׽��䣬�� ��fade��ֵ�仯255��			
	{
		Mmx(lpBuf1 + 0x60, lpBuf2 + 0x60, lpBuf + 0x60, intWidth, intHeight, RGB_Bit, i);					//ָ����lpBuf+0x60��һ�п�ʼɨ��
		SetDIBitsToDevice(hDC, 300, 150, intWidth, intHeight, 0, 0, 0, 480, lpBuf + 0x60, lpInfo, DIB_RGB_COLORS);//�ú���ʹ��DIBλͼ����ɫ���ݶ���Ŀ���豸������ص��豸�ϵ�ָ�������е����ؽ������á�
	}
	LocalFree(lpBuf1);

	LocalFree(lpBuf2);

	ReleaseDC(NULL, hDC);
}


void Test_NoMMX(int intWidth, int intHeight, int RGB_Bit)
{
	_try{
		_asm EMMS
	}
		_except(EXCEPTION_EXECUTE_HANDLER) {
	}
	HDC hDC;
	LPBITMAPINFO lpInfo;                   //ָ��ͼƬ����ĳ�ָ������
	int intSize, i;
	LPBYTE  lpBuf1, lpBuf2, lpBuf;              //ָ���ֽ�(��)��ָ��
	HFILE Picture1, Picture2;
	Picture1 = _lopen("D:\\XJTU\\ComputerOrganization\\MMX\\TestMMX\\TestMMX\\test_24.bmp", OF_READ);          //���ش��ļ��ľ��
	Picture2 = _lopen("D:\\XJTU\\ComputerOrganization\\MMX\\TestMMX\\TestMMX\\test2_24.bmp", OF_READ);
	intSize = GetFileSize((HANDLE)Picture1, NULL);//�����ļ�����		
	lpBuf1 = (LPBYTE)LocalAlloc(LPTR, intSize);//�����·�����ڴ��ַ,,�Ӷ��з���ָ����С���ֽ���
	lpBuf2 = (LPBYTE)LocalAlloc(LPTR, intSize);
	lpBuf = (LPBYTE)LocalAlloc(LPTR, intSize);

	_lread(Picture1, lpBuf1, intSize);      //ָ��һ���ڴ���ָ�룬���ݽ���������ڴ��
	_lread(Picture2, lpBuf2, intSize);
	_lclose(Picture1);  //�ͷ��ļ����
	_lclose(Picture2);
	memcpy(lpBuf, lpBuf1, intSize);
	lpInfo = (LPBITMAPINFO)(lpBuf + 0x0e);
	hDC = GetDC(NULL);
	for (i = 0; i<255; i++)    //Ĭ����ͼ��255�׽��䣬�� ��fade��ֵ�仯255��			
	{
		NoMMX(lpBuf1 + 0x60, lpBuf2 + 0x60, lpBuf + 0x60, intWidth, intHeight, RGB_Bit, i);
				//ָ����lpBuf+0x60��һ�п�ʼɨ��
		SetDIBitsToDevice(hDC, 300, 150, intWidth, intHeight, 0, 0, 0, 480, lpBuf + 0x60, lpInfo, DIB_RGB_COLORS);//�ú���ʹ��DIBλͼ����ɫ���ݶ���Ŀ���豸������ص��豸�ϵ�ָ�������е����ؽ������á�
	}
	LocalFree(lpBuf1);

	LocalFree(lpBuf2);

	ReleaseDC(NULL, hDC);
}
