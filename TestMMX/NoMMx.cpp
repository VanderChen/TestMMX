#include "stdafx.h"
#include "NoMMx.h"
#include <exception>
using namespace std;
int NoMMX(LPBYTE Pic1, LPBYTE Pic2, LPBYTE Pic, int intWidth, int intHeight, int RGB_Bit, int i) {
	try {
		int x, y;
		LPBYTE temp1, temp2, temp;
		BYTE fade_Rate = (BYTE)i;												//将fade值扩展为16位，以适应MMX的16位运算
		BYTE fade1, fade2;

		fade1 = 255 - fade_Rate;             //16位带符号数最大为32767
		fade2 = fade_Rate;

		for (y = 0; y < intHeight; y++)
		{
			temp1 = (LPBYTE)(Pic1 + intWidth * RGB_Bit / 8 * y);
			temp2 = (LPBYTE)(Pic2 + intWidth * RGB_Bit / 8 * y);
			temp = (LPBYTE)(Pic + intWidth * RGB_Bit / 8 * y);
			for (x = 0; x < 3*intWidth; x++)
			{
				_asm {
					mov		dh, [fade1]
					mov		dl, [fade2]
					mov		ecx, [temp1]
					mov		bh, [ecx]
					mov		esi, [temp2]
					mov		bl, [esi]
					mov		al, dh
					mul		bh
					mov		edi, [temp]
					mov		[edi], ah
					mov		al, dl
					mul		bl
					add		ah, [edi]
					mov		[edi], ah
				}
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