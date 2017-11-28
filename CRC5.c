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
  * ���������� ������ ��� ����������� ����� �������� � ��������� USB
  * ���������: http://www.usb.org/developers/docs/whitepapers/crcdes.pdf
  ******************************************************************************
*/

//  Examples (from the USB-standard):
//      data:    length:     	crc5:
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
uint8_t crc5(void *input, uint8_t length)
{
	uint32_t data = *(uint32_t *)input;
	size_t i = length;                   // ��������
 	const uint8_t polynom = POLY;        // ������������� �������� ��������� ���������
	uint8_t crc_reg = INIT_STATE ;       // ������������� �������� ��������� ���������
	
	while(i--)
	{
		if ((crc_reg ^ (data >> (length - POLY))) & 0x10)    // ������������� �������� �������� ���� ��������
		{
			crc_reg <<= 1;
			crc_reg ^= polynom;
		}
		else 
			crc_reg <<= 1;
		
		data <<= 1;
	}

	crc_reg = (crc_reg & INIT_STATE) ^ INIT_STATE;   // ��������� �������� ����� � �������� �������������� ����� 
	
	return crc_reg;
}

/**
  * @brief  ���������� � �������� crc5 �� ������� ������
  * @param  input   -  ��������� �� ������� ������
  * @param  length  -  ����� ������� ������
  * @param  crc5    -  ���������� �������� crc5 ��� ��������
  * @retval 0/1 	-  ��������� ��������, �������/�� �������
  */
bool check_crc5(void *input, uint8_t length, uint8_t taken_crc5)
{
	uint8_t calculated_crc5;
	
	calculated_crc5 = calculate_crc5(input, length, 2);
	
	if(calculated_crc5 == taken_crc5)
		return 1;
	else 
		return 0;
}

/**
  * @brief  ������������ ����� ��� ��������� �������� ������ � ������ �������
  * @param  input   -  ��������� �� ������� ������
  * @param  length  -  ����� ������� ������
  * @param  part    -  ����� ����� crc5 �������, 0 - ������ 4 ����, 1 - ���������, 2 - crc5 ���������
  * @retval crc 	-  ������������ ����� crc5
  */
uint8_t calculate_crc5(void *input, uint8_t length, uint8_t part)
{
	uint32_t data = *(uint32_t *)input; // ���� �� ������ ��� � ������� ������
	uint8_t crc;
	
	// �������������� ���� ������
	data ^= data >> 24 & 0xFF;
	data ^= data << 24 & 0xFF000000;
	data ^= data >> 24 & 0xFF;
	data ^= data >> 8  & 0xFF00;
	data ^= data << 8  & 0xFF0000;
	data ^= data >> 8  & 0xFF00;
	
	data >>= 4; // ������������ CRC-�����
	
	crc = crc5(&data, length);
	
	if(part == 0x0)          // ������� ������ ������ �����
		return crc >> 1 & 0xF;
	if(part == 0x1)    // ������� ���������� ����
		return crc & 0x1;
	else               // ������� ������� �����
		return crc;
}







