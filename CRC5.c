/********************************************************************************
* @file    CRC5.c
* @author  Sapunov
* @version V1.0.0
* @date    November-2017
  ******************************************************************************
  * @attention
  *	�������� CRC5 ������������ ��� ���������� ����������� ����� �� FCH
  * �������-�������� �������� � ITU-T G.9903:
  * GP = x^5 + x^2 + 1 (0b100101)
  ******************************************************************************
*/

//  Examples (from the USB-standard):
//      input:    length:     	crc5:
//      0x547       11          0x17
//      0x2e5       11          0x1C
//      0x072       11          0x0E
//      0x400       11          0x17
#include "crc5.h"
#include <stdio.h>


/**
  * @brief  ���������� crc5 �� ������� ������
  * @param  input   -  ������� ������
  * @param  length  -  ����� ������� ������
  * @retval crc_reg -  �������� ���������� ��������, ������� � �������� ��������� crc5 
  */
int crc5(uint32_t data, size_t length)
{
	size_t i = length;
	const uint8_t polynom = 0x5;   
	uint8_t crc_reg = 0x1f ;       // ������������� �������� ��������� ���������
	
	
	while(i--)
	{
		if ((crc_reg ^ (data >> (length - 5))) & 0x10)    // ������������� �������� �������� ���� ��������
		{
			crc_reg <<= 1;
			crc_reg ^= polynom;
		}
		else 
			crc_reg <<= 1;
		
				data <<= 1;
	
	}
	
	crc_reg = (crc_reg & 0x1f) ^ 0x1f;
	
	return crc_reg;
}


























