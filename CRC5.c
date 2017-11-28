/********************************************************************************
* @file    CRC5.c
* @author  Sapunov
* @version V1.0.0
* @date    November-2017
  ******************************************************************************
  * @attention
  *	Алгоритм CRC5 используется для вычисления контрольной суммы от FCH
  * Полином-делитель определён в ITU-T G.9903:
  * GP = x^5 + x^2 + 1 (0b100101)
  * Изначально данный вид контрольной суммы определён в стандарте USB
  * Подробнее: http://www.usb.org/developers/docs/whitepapers/crcdes.pdf
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
  * @brief  Вычисление crc5 по входным данным
  * @param  input   -  входные данные
  * @param  length  -  длина входных данных
  * @retval crc_reg -  итоговое содержимое регистра, которое и является значением crc5 
  */
uint8_t crc5(void *input, uint8_t length)
{
	uint32_t data = *(uint32_t *)input;
	size_t i = length;                   // Итератор
 	const uint8_t polynom = POLY;        // Инициализация полинома начальным значением
	uint8_t crc_reg = INIT_STATE ;       // Инициализация регистра начальным значением
	
	while(i--)
	{
		if ((crc_reg ^ (data >> (length - POLY))) & 0x10)    // Специфическая проверка старшего бита регистра
		{
			crc_reg <<= 1;
			crc_reg ^= polynom;
		}
		else 
			crc_reg <<= 1;
		
		data <<= 1;
	}

	crc_reg = (crc_reg & INIT_STATE) ^ INIT_STATE;   // Выделение значащих битов и итоговое инвертирование битов 
	
	return crc_reg;
}

/**
  * @brief  Вычисление и проверка crc5 по входным данным
  * @param  input   -  указатель на входные данные
  * @param  length  -  длина входных данных
  * @param  crc5    -  полученное значение crc5 для проверки
  * @retval 0/1 	-  результат проверки, совпало/не совпало
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
  * @brief  Перестановка битов для выделения полезных данных в нужном формате
  * @param  input   -  указатель на входные данные
  * @param  length  -  длина входных данных
  * @param  part    -  какую часть crc5 вернуть, 0 - первые 4 бита, 1 - последний, 2 - crc5 полностью
  * @retval crc 	-  возвращаемая часть crc5
  */
uint8_t calculate_crc5(void *input, uint8_t length, uint8_t part)
{
	uint32_t data = *(uint32_t *)input; // Каст на работу как с обычным числом
	uint8_t crc;
	
	// Инвертирование байт данных
	data ^= data >> 24 & 0xFF;
	data ^= data << 24 & 0xFF000000;
	data ^= data >> 24 & 0xFF;
	data ^= data >> 8  & 0xFF00;
	data ^= data << 8  & 0xFF0000;
	data ^= data >> 8  & 0xFF00;
	
	data >>= 4; // Выталкивание CRC-битов
	
	crc = crc5(&data, length);
	
	if(part == 0x0)          // Возврат первых четырёх битов
		return crc >> 1 & 0xF;
	if(part == 0x1)    // Возврат последнего бита
		return crc & 0x1;
	else               // Возврат полного числа
		return crc;
}







