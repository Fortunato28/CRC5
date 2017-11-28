#include <stdio.h>
#include "crc5.h"

void main()
{	
	G3PLC_DataFCH DataFCH;
	
	DataFCH.pdc   = 0xFE; 	  // 0b11111110
	DataFCH.fl    = 0x3E; 	  // 0b111110
	DataFCH.mod   = 0x2;  	  // 0b10
	DataFCH.tm    = 0x3E; 	  // 0b111110
	DataFCH.not1  = 0x00;     // 0b00
	DataFCH.fccs3 = 0xB; 	  // 0b1011
	DataFCH.dt    = 0x6;  	  // 0b110
	DataFCH.pms   = 0x1;  	  // 0b1
	DataFCH.not2  = 0x1;  	  // 0b1
	DataFCH.cz    = 0x000000; // 0b000000
	DataFCH.fccs4 = 0x1; 	  // 0b1
	
	uint8_t check_sum;
	
	DataFCH.fccs3 = calculate_crc5(&DataFCH, LENGTH, 0);
 	DataFCH.fccs4 = calculate_crc5(&DataFCH, LENGTH, 1);
	check_sum     = (uint8_t)DataFCH.fccs3 << 1 | (uint8_t)DataFCH.fccs4;
	
	printf("fccs3 = %x\n", DataFCH.fccs3);
	printf("fccs4 = %x\n", DataFCH.fccs4);
	printf("CRC5  = %x\n", check_sum);	
	
	
	printf("Checker = %x\n", check_crc5(&DataFCH, LENGTH, check_sum));
}
