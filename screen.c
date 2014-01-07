#include <system.h>

unsigned short *textmemptr;
int csr_x=0, csr_y=0;
int back_fore = 0x0F;

void scroll()
{
	unsigned temp;
	unsigned blank;

	blank = 0x20 | (back_fore << 8);
	if ( csr_y >= 25 )
	{
		temp = csr_y -25 + 1;
		memcpy(textmemptr, textmemptr + temp*80, (25-temp)*80*2);

		memsetw(textmemptr+(25-temp)*80, blank, 80);
		csr_y = 25 - 1;
	}
}

void move_cursor()
{
	unsigned temp;

	temp = csr_y*80 + csr_x;
	/* This sends a command to indicies 14 and 15 in the
	*  CRT Control Register of the VGA controller. These
	*  are the high and low bytes of the index that show
	*  where the hardware cursor is to be 'blinking'. To
	*  learn more, you should look up some VGA specific
	*  programming documents. A great start to graphics:
	*  http://www.brackeen.com/home/vga */
	outportb(0x3D4,14);
	outportb(0x3D5,temp>>8);
	outportb(0x3D4,15);
	outportb(0x3D5,temp);
}

void cls()
{
	unsigned blank;
	int i;

	blank = 0x20 | (back_fore << 8);
	for(i=0; i<25; i++)
		memsetw(textmemptr + i*80, blank, 80);

	csr_x = 0;
	csr_y = 0;
	move_cursor();
}

void putch(unsigned char ch)
{
	unsigned short *where;
	int attrib = back_fore << 8;

	// backspace
	if ( ch == 0x08 )
	{
		if ( csr_x == 0 )
			csr_x--;
	}

	//Tab
	if ( ch == 0x09 )
		csr_x = (csr_x + 8) & ~(8-1);

	//Carriage return
	if ( ch == '\r' )
		csr_x = 0;

	// new line
	if ( ch == '\n' )
	{
		csr_x = 0;
		csr_y++;
	}

	// all other values
	if ( ch >= ' ' )
	{
		where = textmemptr + (csr_y*80 + csr_x);
		*where = attrib | ch;
		csr_x++;
	}

	if ( csr_x >= 80 )
	{
		csr_x = 0;
		csr_y++;
	}

	scroll();
	move_cursor();
}

void puts(const char *str)
{
	int i;
	for(i=0; i<strlen(str); i++)
		putch(str[i]);
}

void init_video()
{
    textmemptr = (unsigned short *)0xB8000;
    cls();
}
