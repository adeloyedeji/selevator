#ifndef __SE_DISPATCH_H__
#define __SE_DISPATCH_H__

#if defined(__cplusplus)
extern "C" {
#endif

void dispatch_init(void);
void dispatch_request(uint8_t floor);
void dispatch_shutdown(void);
void dispatch_print_all(void);

#if defined(__cplusplus)
}
#endif

#endif //__SE_DISPATCH_H__