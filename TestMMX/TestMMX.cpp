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

	cout << "使用MMX用时：" << (end_time - start_time) << "ms!" << endl;//输出运行时间

	start_time = GetTickCount();

	Test_NoMMX(640, 480, 24);

	end_time = GetTickCount();

	cout << "不使用MMX用时：" << (end_time - start_time) << "ms!" << endl;
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
	LPBITMAPINFO lpInfo;                   //指向图片对象的长指针类型
	int intSize, i;
	LPBYTE  lpBuf1, lpBuf2, lpBuf;              //指向字节(串)的指针
	HFILE Picture1, Picture2;
	Picture1 = _lopen("D:\\XJTU\\ComputerOrganization\\MMX\\TestMMX\\TestMMX\\test_24.bmp", OF_READ);          //返回打开文件的句柄
	Picture2 = _lopen("D:\\XJTU\\ComputerOrganization\\MMX\\TestMMX\\TestMMX\\test2_24.bmp", OF_READ);
	intSize = GetFileSize((HANDLE)Picture1, NULL);//返回文件长度		
	lpBuf1 = (LPBYTE)LocalAlloc(LPTR, intSize);//返回新分配的内存地址,,从堆中分配指定大小的字节数
	lpBuf2 = (LPBYTE)LocalAlloc(LPTR, intSize);
	lpBuf = (LPBYTE)LocalAlloc(LPTR, intSize);

	_lread(Picture1, lpBuf1, intSize);      //指定一个内存块的指针，数据将读入这个内存块
	_lread(Picture2, lpBuf2, intSize);
	_lclose(Picture1);  //释放文件句柄
	_lclose(Picture2);
	memcpy(lpBuf, lpBuf1, intSize);
	lpInfo = (LPBITMAPINFO)(lpBuf + 0x0e);
	hDC = GetDC(NULL);
	for (i = 0; i<255; i++)    //默认是图像按255阶渐变，即 让fade的值变化255次			
	{
		Mmx(lpBuf1 + 0x60, lpBuf2 + 0x60, lpBuf + 0x60, intWidth, intHeight, RGB_Bit, i);					//指定从lpBuf+0x60这一行开始扫描
		SetDIBitsToDevice(hDC, 300, 150, intWidth, intHeight, 0, 0, 0, 480, lpBuf + 0x60, lpInfo, DIB_RGB_COLORS);//该函数使用DIB位图和颜色数据对与目标设备环境相关的设备上的指定矩形中的像素进行设置。
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
	LPBITMAPINFO lpInfo;                   //指向图片对象的长指针类型
	int intSize, i;
	LPBYTE  lpBuf1, lpBuf2, lpBuf;              //指向字节(串)的指针
	HFILE Picture1, Picture2;
	Picture1 = _lopen("D:\\XJTU\\ComputerOrganization\\MMX\\TestMMX\\TestMMX\\test_24.bmp", OF_READ);          //返回打开文件的句柄
	Picture2 = _lopen("D:\\XJTU\\ComputerOrganization\\MMX\\TestMMX\\TestMMX\\test2_24.bmp", OF_READ);
	intSize = GetFileSize((HANDLE)Picture1, NULL);//返回文件长度		
	lpBuf1 = (LPBYTE)LocalAlloc(LPTR, intSize);//返回新分配的内存地址,,从堆中分配指定大小的字节数
	lpBuf2 = (LPBYTE)LocalAlloc(LPTR, intSize);
	lpBuf = (LPBYTE)LocalAlloc(LPTR, intSize);

	_lread(Picture1, lpBuf1, intSize);      //指定一个内存块的指针，数据将读入这个内存块
	_lread(Picture2, lpBuf2, intSize);
	_lclose(Picture1);  //释放文件句柄
	_lclose(Picture2);
	memcpy(lpBuf, lpBuf1, intSize);
	lpInfo = (LPBITMAPINFO)(lpBuf + 0x0e);
	hDC = GetDC(NULL);
	for (i = 0; i<255; i++)    //默认是图像按255阶渐变，即 让fade的值变化255次			
	{
		NoMMX(lpBuf1 + 0x60, lpBuf2 + 0x60, lpBuf + 0x60, intWidth, intHeight, RGB_Bit, i);
				//指定从lpBuf+0x60这一行开始扫描
		SetDIBitsToDevice(hDC, 300, 150, intWidth, intHeight, 0, 0, 0, 480, lpBuf + 0x60, lpInfo, DIB_RGB_COLORS);//该函数使用DIB位图和颜色数据对与目标设备环境相关的设备上的指定矩形中的像素进行设置。
	}
	LocalFree(lpBuf1);

	LocalFree(lpBuf2);

	ReleaseDC(NULL, hDC);
}
