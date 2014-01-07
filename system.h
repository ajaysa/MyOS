#ifndef __SYSTEM_H
#define __SYSTEM_H

// from main.c
extern void *memcpy(void *dest, const void *src, int count);
extern void *memset(void *dest, char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern int strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

// screen.c
extern void cls();
extern void putch(unsigned char ch);
extern void puts(const char *str);
extern void move_cursor();
extern void init_video();

#endif
