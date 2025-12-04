#include "text.h"

extern void port_out(unsigned short port, unsigned char data);
extern unsigned char port_in(unsigned short port);

static unsigned short x = 0;
static unsigned short y = 0;

static unsigned char fg_color = TXT_WHITE;
static unsigned char bg_color = TXT_BLACK;

static char* vram = (char*)TXT_MEMORY;

static unsigned char attr_byte(unsigned char f, unsigned char b) {
    return (b << 4) | (f & 0x0F);
}

static void sync_cursor(void) {
    unsigned short pos = y * TXT_WIDTH + x;
    port_out(TXT_CTRL_PORT, TXT_HIGH_CMD);
    port_out(TXT_DATA_PORT, (pos >> 8) & 0xFF);
    port_out(TXT_CTRL_PORT, TXT_LOW_CMD);
    port_out(TXT_DATA_PORT, pos & 0xFF);
}

void text_clear(void) {
    unsigned char attr = attr_byte(fg_color, bg_color);
    for (int i = 0; i < TXT_WIDTH * TXT_HEIGHT; i++) {
        vram[i * 2] = ' ';
        vram[i * 2 + 1] = attr;
    }
    x = 0;
    y = 0;
    sync_cursor();
}

void text_goto(unsigned short x_pos, unsigned short y_pos) {
    if (x_pos < TXT_WIDTH) x = x_pos;
    if (y_pos < TXT_HEIGHT) y = y_pos;
    sync_cursor();
}

unsigned short text_x(void) {
    return x;
}

unsigned short text_y(void) {
    return y;
}

void text_set_fg_bg(unsigned char f, unsigned char b) {
    fg_color = f;
    bg_color = b;
}

void text_scroll(void) {
    unsigned char attr = attr_byte(fg_color, bg_color);
    
    for (int i = 0; i < (TXT_HEIGHT - 1) * TXT_WIDTH; i++) {
        vram[i * 2] = vram[(i + TXT_WIDTH) * 2];
        vram[i * 2 + 1] = vram[(i + TXT_WIDTH) * 2 + 1];
    }
    
    for (int i = (TXT_HEIGHT - 1) * TXT_WIDTH; i < TXT_HEIGHT * TXT_WIDTH; i++) {
        vram[i * 2] = ' ';
        vram[i * 2 + 1] = attr;
    }
}

void text_putc(char c) {
    unsigned char attr = attr_byte(fg_color, bg_color);
    
    if (c == '\n') {
        x = 0;
        y++;
    } else if (c == '\r') {
        x = 0;
    } else if (c == '\t') {
        x = (x + 8) & ~7;
    } else {
        unsigned int pos = (y * TXT_WIDTH + x);
        vram[pos * 2] = c;
        vram[pos * 2 + 1] = attr;
        x++;
    }
    
    if (x >= TXT_WIDTH) {
        x = 0;
        y++;
    }
    
    if (y >= TXT_HEIGHT) {
        text_scroll();
        y = TXT_HEIGHT - 1;
    }
    
    sync_cursor();
}

void text_write(const char* s) {
    while (*s) {
        text_putc(*s);
        s++;
    }
}

void text_write_int(int n) {
    char temp[12];
    int len = 0;
    int sign = 0;
    
    if (n == 0) {
        text_putc('0');
        return;
    }
    
    if (n < 0) {
        sign = 1;
        n = -n;
    }
    
    while (n > 0) {
        temp[len++] = '0' + (n % 10);
        n /= 10;
    }
    
    if (sign) {
        text_putc('-');
    }
    
    while (len > 0) {
        text_putc(temp[--len]);
    }
}

void text_write_hex(unsigned int n) {
    char hex[] = "0123456789ABCDEF";
    char temp[9];
    int len = 0;
    
    text_write("0x");
    
    if (n == 0) {
        text_putc('0');
        return;
    }
    
    while (n > 0) {
        temp[len++] = hex[n & 0xF];
        n >>= 4;
    }
    
    while (len > 0) {
        text_putc(temp[--len]);
    }
}

void text_delete(void) {
    if (x > 0) {
        x--;
    } else if (y > 0) {
        y--;
        x = TXT_WIDTH - 1;
    }
    
    unsigned int pos = y * TXT_WIDTH + x;
    vram[pos * 2] = ' ';
    vram[pos * 2 + 1] = attr_byte(fg_color, bg_color);
    sync_cursor();
}

