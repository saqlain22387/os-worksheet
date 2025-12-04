#ifndef TEXT_H
#define TEXT_H

#define TXT_MEMORY 0x000B8000
#define TXT_WIDTH 80
#define TXT_HEIGHT 25

#define TXT_CTRL_PORT 0x3D4
#define TXT_DATA_PORT 0x3D5
#define TXT_HIGH_CMD 14
#define TXT_LOW_CMD 15

#define TXT_BLACK 0
#define TXT_BLUE 1
#define TXT_GREEN 2
#define TXT_CYAN 3
#define TXT_RED 4
#define TXT_MAGENTA 5
#define TXT_BROWN 6
#define TXT_LIGHT_GREY 7
#define TXT_DARK_GREY 8
#define TXT_LIGHT_BLUE 9
#define TXT_LIGHT_GREEN 10
#define TXT_LIGHT_CYAN 11
#define TXT_LIGHT_RED 12
#define TXT_LIGHT_MAGENTA 13
#define TXT_YELLOW 14
#define TXT_WHITE 15

void text_clear(void);
void text_goto(unsigned short x, unsigned short y);
unsigned short text_x(void);
unsigned short text_y(void);
void text_set_fg_bg(unsigned char f, unsigned char b);
void text_putc(char c);
void text_write(const char* s);
void text_write_int(int n);
void text_write_hex(unsigned int n);
void text_scroll(void);
void text_delete(void);

#endif

