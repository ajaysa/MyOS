#include <system.h>

void *memcpy(void *dest, const void *src, int count)
{
    int i;
    const char *sp = (const char *)src;
    char *dp = (char *)dest;

    for(i=0; i<count; i++)
        dp[i] = sp[i];
    return dest;
}

void *memset(void *dest, char val, int count)
{
    int i;
    char *temp = (char *)dest;
    for(i=0; i<count; i++)
        temp[i] = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    int i;
    for(i=0; i<count; i++)
        dest[i] = val;
    return dest;
}

int strlen(const char *str)
{
    int i;
    int len=0;
    for(i=0; str[i]!='\0'; i++)
        len++;
    return len;
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

int main(struct multiboot *mboot_ptr)
{
	init_video();

	puts("Hello World!!");
	return 0xDEADBABA;
}
