/*----------------------------------------------------------------------------
/
/  Copyright (C) 2012, ChaN, all right reserved.
/
/ * The FatFs module is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#include "iprintf.h"
#include "uart.h"

typedef unsigned int UINT;
typedef unsigned char BYTE;
typedef unsigned long ULONG;

typedef char TCHAR;

//#define EOF (-1)
#define IsUpper(c)	(((c)>='A')&&((c)<='Z'))
#define IsLower(c)	(((c)>='a')&&((c)<='z'))
#define IsDigit(c)	(((c)>='0')&&((c)<='9'))

static int printchar(char **out, int c) {
    if (out) {
        **out = c;
        ++(*out);
    } else {
        uart_putchar(c);
    }
    return 1;
}

static int prints(char **out, const TCHAR* str) {
    int n;


    for (n = 0; *str; str++, n++) {
        if (printchar(out, *str) == EOF) return EOF;
    }
    return n;
}

/*-----------------------------------------------------------------------*/
/* Put a formatted string to the file                                    */

/*-----------------------------------------------------------------------*/
#define FLAG_0_PADDDING         0x01
#define FLAG_LEFT_JUSTIFIED     0x02
#define FLAG_LONG_INT           0x04
#define FLAG_SIGN               0x08
#define FLAG_ALWAYS_SIGN        0x10

int smart_vsiprintf(char *buf, const char *format, va_list arp) {
    BYTE f, r;
    UINT i, j, w;
    ULONG v;
    TCHAR c, d, s[16], *p;
    int res, chc, cc, res2;
    char ** string = (buf != 0) ? &buf : 0;

    for (cc = res = 0; cc != EOF; res += cc) {
        res2 = 0;
        c = *format++;
        if (c == 0) break; /* End of string */
        if (c != '%') { /* Non escape character */
            cc = printchar(string, c);
            if (cc != EOF) cc = 1;
            continue;
        }
        w = f = 0;
        c = *format++;
        if (c == '-') { /* Flag: left justified */
            f = FLAG_LEFT_JUSTIFIED;
            c = *format++;
        } else if (c == '+') { /* Flag: always sign */
            f = FLAG_ALWAYS_SIGN;
            c = *format++;
        }        
        if (c == '0') { /* Flag: '0' padding */
            f |= FLAG_0_PADDDING;
            c = *format++;
        }
        while (IsDigit(c)) { /* Precision */
            w = w * 10 + c - '0';
            c = *format++;
        }
        if (c == 'l' || c == 'L') { /* Prefix: Size is long int */
            f |= FLAG_LONG_INT;
            c = *format++;
        }
        if (!c) break;
        d = c;
        if (IsLower(d)) d -= 0x20;
        switch (d) { /* Type is... */
            case 'S': /* String */
                p = va_arg(arp, TCHAR*);
                for (j = 0; p[j]; j++);
                chc = 0;
                if (!(f & FLAG_LEFT_JUSTIFIED)) {
                    while (j++ < w) chc += (cc = printchar(string, ' '));
                }
                chc += (cc = prints(string, p));
                while (j++ < w) chc += (cc = printchar(string, ' '));
                if (cc != EOF) cc = chc;
                continue;
            case 'C': /* Character */
                cc = printchar(string, (TCHAR) va_arg(arp, int));
                continue;
            case 'B': /* Binary */
                r = 2;
                break;
            case 'O': /* Octal */
                r = 8;
                break;
            case 'D': /* Signed decimal */
            case 'U': /* Unsigned decimal */
                r = 10;
                break;
            case 'P': /* Hexadecimal pointer */
                res2 += (cc = printchar(string, '0'));
                res2 += (cc = printchar(string, 'x'));
                r = 16;
                break;
            case 'X': /* Hexdecimal */
                r = 16;
                break;
            default: /* Unknown type (pass-through) */
                cc = printchar(string, c);
                continue;
        }

        /* Get an argument and put it in numeral */
        v = (f & FLAG_LONG_INT) ? (ULONG) va_arg(arp, long) : ((d == 'D') ? (ULONG) (long) va_arg(arp, int) : (ULONG) va_arg(arp, unsigned int));
        if (d == 'D' && (v & 0x80000000)) {
            v = 0 - v;
            f |= FLAG_SIGN;
        }
        i = 0;
        do {
            d = (TCHAR) (v % r);
            v /= r;
            if (d > 9) d += (c == 'x') || (c == 'p') ? 0x27 : 0x07;
            s[i++] = d + '0';
        } while (v && i < sizeof s / sizeof s[0]);
        if (f & FLAG_SIGN) s[i++] = '-';
        else if (f & FLAG_ALWAYS_SIGN) s[i++] = '+';
        j = i;
        if (f & (FLAG_SIGN | FLAG_ALWAYS_SIGN)) res2 += printchar(string, s[--i]);
        d = (f & FLAG_0_PADDDING) ? '0' : ' ';
        while (!(f & FLAG_LEFT_JUSTIFIED) && j++ < w) res2 += (cc = printchar(string, d));
        do res2 += (cc = printchar(string, s[--i])); while (i);
        while (j++ < w) res2 += (cc = printchar(string, ' '));
        if (cc != EOF) cc = res2;
    }
    if (string) **string = '\0';
    return (cc == EOF) ? cc : res;
}

int smart_iprintf(const char *format, ...) {
    va_list args;
    int res;

    va_start(args, format);
    res = smart_vsiprintf(0, format, args);
    va_end(args);
    return res;
}

int smart_siprintf(char *string, const char *format, ...) {
    va_list args;
    int res;

    va_start(args, format);
    res = smart_vsiprintf(string, format, args);
    va_end(args);
    return res;
}


