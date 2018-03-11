#ifndef DEBUG_H
#define DEBUG_H
 
#include "iprintf.h"
#include "directives.h"
 
#define SMART_PLATFORM_DIAG(x)    do {SMART_PRINTF x;} while(0)
#define SMART_HALT(message) do { SMART_PLATFORM_DIAG(message); while(1); } while(0)
 
#define SMART_DEBUG_ON       0x80U
#define SMART_DEBUG_OFF      0x00U
 
#ifdef DEBUGGING
#define SMART_DEBUGF(debug, message) do { \
                               if (debug) { \
                                 SMART_PLATFORM_DIAG(message); \
                               } \
                             } while(0)
 
#else  /* DEBUGGING */
#define SMART_DEBUGF(debug, message)
#endif /* DEBUGGING */
 
#define SMART_DEBUG_ARRAY(debug, prefix, format, data, size, suffix) do {\
    if(debug) { \
        SMART_DEBUGF(debug, ("%s", (prefix))); \
        int _i; \
        for(_i = 0; _i < (int)(size); _i++) { \
            SMART_DEBUGF(debug, (format, (data)[_i])); \
        } \
        SMART_DEBUGF(debug, ("%s", (suffix))); \
    } \
    } while(0)
 
#define SMART_DEBUG_DATA_HEX(debug, prefix, data, size, suffix) SMART_DEBUG_ARRAY(debug, prefix, "%02X ", data, size, suffix)
 
#define SMART_DEBUG_MAC(debug, prefix, mac, suffix) \
    SMART_DEBUGF(debug, ("%s%02x:%02x:%02x:%02x:%02x:%02x%s", \
        (prefix), \
        (unsigned char)(mac)[0], \
        (unsigned char)(mac)[1], \
        (unsigned char)(mac)[2], \
        (unsigned char)(mac)[3], \
        (unsigned char)(mac)[4], \
        (unsigned char)(mac)[5], \
        (suffix) \
        ))
 
#define SMART_DEBUG_IP4(debug, prefix, addr, suffix) \
    SMART_DEBUGF(debug, ("%s%u.%u.%u.%u%s", \
        (prefix), \
        ip4_addr1(addr), \
        ip4_addr2(addr), \
        ip4_addr3(addr), \
        ip4_addr4(addr), \
        (suffix) \
        ))
 
#define SMART_FORCE_DATA_ABORT() do{ *((volatile int *)0x7fe08000) = 10; } while(0)
 
#endif /* DEBUG_H */