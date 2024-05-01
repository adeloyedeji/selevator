#ifndef __SE_DISPATCH_H__
#define __SE_DISPATCH_H__

#include <stdint.h>
#include "selevator.h"

void dispatch_init(void);
void dispatch_request(uint8_t floor);
void dispatch_shutdown(void);
void dispatch_print_all(void);


#endif //__SE_DISPATCH_H__