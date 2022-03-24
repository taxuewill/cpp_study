#ifndef __CRC_16_H
#define __CRC_16_H

#include "stdint.h"

/*

typedef struct CommDataPackTypeDef_{
	uint8_t len;
	uint8_t src_id;
	uint8_t dst_id;
	uint8_t cmd;
	uint8_t index;
	uint8_t data_p[DATA_LEN];
}CommDataPackTypeDef;

*/


#ifdef __cplusplus
 extern "C" {
#endif


extern uint8_t CheckCrc16OrCheckSum16(uint8_t *p_data,uint16_t length , uint16_t check_data) ;
//extern uint8_t CheckCrc16OrCheckSum16ByPack(CommDataPackTypeDef *pack, uint16_t check_data) ;
//extern uint16_t GetCrc16ByPack(CommDataPackTypeDef *pack) ;
extern uint16_t GetCrc16(uint8_t *p_data,uint16_t length);

#ifdef __cplusplus
}
#endif
#endif
