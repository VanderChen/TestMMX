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
				pxor		mm4, mm4;  //��mm6�Ĵ������
				movq		mm2,[fade1]
				movq		mm3,[fade2]
				mov			esi,[temp1]  //ȡ�����ļ��е�����ָ��
				mov			edx,[temp2]
				mov			edi,[temp]
				movd		mm0,[esi]  //����һ��ͼƬ�����ݼ��ص�mm0�Ĵ���
				movd		mm1,[edx]  //���ڶ���ͼƬ�����ݼ��ص�mm1�Ĵ���
				punpcklbw	mm0, mm4
				punpcklbw	mm1, mm4  //���ֽڽ������16λ
				pmulhw		mm0, mm2  //��һ����Ƭ����fade_rate
				pmulhw		mm1, mm3  //�ڶ�����Ƭ����1-fade_rate
				paddw		mm0, mm1  //��2����Ƭ�Ӻ͵õ���������Ƭ
				packuswb	mm0, mm4  //��16λ������һ���ֽ�
				movd        [edi], mm0  //�����������Ƭ���ڴ�
			}
			/*
			_asm {
				pxor		mm4, mm4;  //��mm4�Ĵ������
				movq		mm2,[fade2]
				mov			esi,[temp1]  //ȡ�����ļ��е�����ָ��
				mov			edx,[temp2]
				mov			edi,[temp]
				movd		mm0,[esi]  //����һ��ͼƬ�����ݼ��ص�mm0�Ĵ���
				movd		mm1,[edx]  //���ڶ���ͼƬ�����ݼ��ص�mm1�Ĵ���
				punpcklbw	mm0, mm4
				punpcklbw	mm1, mm4  //���ֽڽ������16λ
				psubw		mm0, mm1
				pmulhw		mm0, mm2  //����ֵ����fade_rate
				paddw		mm0, mm1  //��2����Ƭ�Ӻ͵õ���������Ƭ
				packuswb	mm0, mm4  //��16λ������һ���ֽ�
				movd        [edi], mm0  //�����������Ƭ���ڴ�
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