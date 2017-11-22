#include <stdio.h>
#include "crc5.h"
#include <stdbool.h>

void main()
{
	uint32_t check_sum;
	check_sum = crc5(0x2e5, 11);
	printf("CheckSum = %x\n", check_sum);
	
}
