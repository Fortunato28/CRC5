#ifndef CRC5
#define CRC5

#include <stdint.h>
#include <stdbool.h>

// FCH ���������
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

// ����������� ������� (������ ��� �� �����������)
#define POLY 0x5
// ��������� ��������� � �������� �������������� �����
#define INIT_STATE 0x1f
// CRC5 ����������� ������ �� ����� ���������� ���
#define LENGTH 28

/**************���������************************/
uint8_t crc5(void *input, uint8_t length);
bool check_crc5(void *input, uint8_t length, uint8_t crc5);
uint8_t calculate_crc5(void *input, uint8_t length);
/***********************************************/
#endif
