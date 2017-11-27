#ifndef CRC5
#define CRC5

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// FCH структура
typedef struct {
	uint8_t	 pdc;     	//(B_0)Phase detection counter
	unsigned fl   :6;	//(B_1)PHY frame length in PHY symbols, FL = Number of symbols/4	
	unsigned mod  :2; 	//(B_1)Modulation type
  	unsigned tm   :6;	//(B_2)Tone map 	
	unsigned not1 :2; 	//(B_2)Reserved by ITU-T 
	unsigned fccs3:4; 	//(B_3)Frame control check sequence (CRC5)
	unsigned dt   :3; 	//(B_3)Delimiter type 
	unsigned pms  :1;	//(B_3)Payload modulation scheme
	unsigned not2 :1; 	//(B_4)	
	unsigned cz   :6; 	//(B_4)6 zeros for convolutional encoder
	unsigned fccs4:1; 	//(B_4)Frame control check sequence (CRC5)
} G3PLC_DataFCH;  

// ѕорождающий полином (первый бит не учитываетс€)
#define POLY 0x5
// Ќачальное состо€ние и итоговое инвертирование битов
#define INIT_STATE 0x1f

/**
  * @brief  ¬ычисление crc5 по входным данным
  * @param  input   -  указатель на входные данные
  * @param  length  -  длина входных данных
  * @retval crc_reg -  итоговое содержимое регистра, которое и €вл€етс€ значением crc5 
  */
uint8_t crc5(uint32_t input, size_t length);

/**
  * @brief  ¬ычисление и проверка crc5 по входным данным
  * @param  input   -  указатель на входные данные
  * @param  length  -  длина входных данных
  * @param  crc5    -  полученное значение crc5 дл€ проверки
  * @retval 0/1 	-  результат проверки, совпало/не совпало
  */
bool check_crc5(void *input, size_t length, uint8_t crc5);

/**
  * @brief  ѕерестановка битов дл€ выделени€ полезных данных в нужном формате
  * @param  input   -  указатель на входные данные
  * @param  length  -  длина входных данных
  * @param  byte    -  какую часть crc5 вернуть, первые 4 бита или последний
  * @retval crc5_part 	-  возвращаема€ часть crc5
  */
uint8_t get_crc5(void *input, size_t length, uint8_t part);
#endif
