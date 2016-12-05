#include "stdafx.h"
#include "mmx.h"
#include <exception>
using namespace std;
int Mmx(LPBYTE Pic1, LPBYTE Pic2, LPBYTE Pic, int intWidth, int intHeight, int RGB_Bit, int i) {
	try{
		int x, y;
		LPDWORD temp1, temp2, temp;
		int fade_Rate = i * 128;
		WORD fade1[4], fade2[4];
		fade1[0] = fade2[1] = fade1[2] = fade1[3] = 32767 - fade_Rate;
		fade2[0] = fade2[1] = fade2[2] = fade2[3] = fade_Rate;
	for (y = 0; y < intHeight; y++)
	{
		temp1 = (LPDWORD)(Pic1 + intWidth * RGB_Bit / 8 * y);
		temp2 = (LPDWORD)(Pic2 + intWidth * RGB_Bit / 8 * y);
		temp = (LPDWORD)(Pic + intWidth * RGB_Bit / 8 * y);
		for (x = 0; x < intWidth; x++)
		{
			_asm {
				pxor		mm4, mm4;  //将mm6寄存器清空
				movq		mm2,[fade1]
				movq		mm3,[fade2]
				mov			esi,[temp1]  //取三个文件中的像素指针
				mov			edx,[temp2]
				mov			edi,[temp]
				movd		mm0,[esi]  //将第一张图片的内容加载到mm0寄存器
				movd		mm1,[edx]  //将第二张图片的内容加载到mm1寄存器
				punpcklbw	mm0, mm4
				punpcklbw	mm1, mm4  //将字节解紧缩到16位
				pmulhw		mm0, mm2  //第一张照片乘以fade_rate
				pmulhw		mm1, mm3  //第二张照片乘以1-fade_rate
				paddw		mm0, mm1  //将2张照片加和得到第三张照片
				packuswb	mm0, mm4  //将16位紧缩到一个字节
				movd        [edi], mm0  //送入第三张照片的内存
			}
			/*
			_asm {
				pxor		mm4, mm4;  //将mm4寄存器清空
				movq		mm2,[fade2]
				mov			esi,[temp1]  //取三个文件中的像素指针
				mov			edx,[temp2]
				mov			edi,[temp]
				movd		mm0,[esi]  //将第一张图片的内容加载到mm0寄存器
				movd		mm1,[edx]  //将第二张图片的内容加载到mm1寄存器
				punpcklbw	mm0, mm4
				punpcklbw	mm1, mm4  //将字节解紧缩到16位
				psubw		mm0, mm1
				pmulhw		mm0, mm2  //将差值乘以fade_rate
				paddw		mm0, mm1  //将2张照片加和得到第三张照片
				packuswb	mm0, mm4  //将16位紧缩到一个字节
				movd        [edi], mm0  //送入第三张照片的内存
			}
			*/
			temp1++;
			temp2++;
			temp++;
		}

	}
	_asm EMMS
	}
	catch (exception& e) {

	}
	return 0;
}