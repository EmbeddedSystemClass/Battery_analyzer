#ifndef IPRINTF_H
#define IPRINTF_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SMART_OVERIDE_STD_PRINTF 1

#define smart_iprintf iprintf
#define smart_sniprintf sniprintf
#define smart_vsniprintf vsniprintf

#if SMART_OVERIDE_STD_PRINTF
#define snprintf smart_sniprintf
#define printf smart_iprintf
#endif

#define SMART_PRINTF smart_iprintf
#define SMART_SNPRINTF smart_sniprintf

int smart_iprintf(const char *format, ...);
int smart_sniprintf(char *string, unsigned int n, const char *format, ...);
int smart_sniprintf_unterminated(char *string, unsigned int n, const char *format, ...);
int smart_vsniprintf_unterminated(char *buf, unsigned int n, const char *format, va_list arp);

extern void smart_putchar(int ch);

#ifdef __cplusplus
}
#endif

#endif /* IPRINTF_H */
