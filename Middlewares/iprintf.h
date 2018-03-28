#ifndef IPRINTF_H
#define IPRINTF_H

#include <stdarg.h>

#define SMART_OVERIDE_STD_PRINTF 1

#define smart_iprintf iprintf
#define smart_siprintf siprintf
#define smart_vsiprintf vsiprintf

#if SMART_OVERIDE_STD_PRINTF
#define sprintf smart_siprintf
#define printf smart_iprintf
#endif

#define SMART_PRINTF smart_iprintf
#define SMART_SPRINTF smart_siprintf

int smart_iprintf(const char *format, ...);
int smart_siprintf(char *string, const char *format, ...);
int smart_vsiprintf(char *buf, const char *format, va_list arp);

extern void smart_putchar(int ch);

#endif /* IPRINTF_H */

