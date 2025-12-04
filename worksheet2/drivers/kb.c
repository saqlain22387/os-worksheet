#include "kb.h"
#include "text.h"

extern void port_out(unsigned short port, unsigned char data);
extern unsigned char port_in(unsigned short port);

static int shift_on = 0;

static char normal_map[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};

static char shift_map[] = {
    0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0,
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
    0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*', 0, ' '
};

void kb_setup(void) {
    port_out(PIC1_CMD_REG, 0x11);
    port_out(PIC2_CMD_REG, 0x11);
    
    port_out(PIC1_DATA_REG, 0x20);
    port_out(PIC2_DATA_REG, 0x28);
    
    port_out(PIC1_DATA_REG, 0x04);
    port_out(PIC2_DATA_REG, 0x02);
    
    port_out(PIC1_DATA_REG, 0x01);
    port_out(PIC2_DATA_REG, 0x01);
    
    port_out(PIC1_DATA_REG, 0xFD);
    port_out(PIC2_DATA_REG, 0xFF);
}

int kb_has_data(void) {
    return (port_in(KB_STAT_REG) & 0x01);
}

char kb_get_char(void) {
    unsigned char scan;
    char c = 0;
    
    while (1) {
        while (!(port_in(KB_STAT_REG) & 0x01));
        
        scan = port_in(KB_DATA_REG);
        
        if (scan == KB_LSHIFT || scan == KB_RSHIFT) {
            shift_on = 1;
            continue;
        }
        if (scan == KB_LSHIFT_REL || scan == KB_RSHIFT_REL) {
            shift_on = 0;
            continue;
        }
        
        if (scan & 0x80) {
            continue;
        }
        
        if (scan < sizeof(normal_map)) {
            if (shift_on) {
                c = shift_map[scan];
            } else {
                c = normal_map[scan];
            }
            
            if (c != 0) {
                return c;
            }
        }
        
        if (scan == KB_BS) {
            return '\b';
        }
    }
}

void kb_get_line(char* buffer, int size) {
    int idx = 0;
    char c;
    
    while (idx < size - 1) {
        c = kb_get_char();
        
        if (c == '\n') {
            text_putc('\n');
            break;
        } else if (c == '\b') {
            if (idx > 0) {
                idx--;
                text_delete();
            }
        } else if (c >= ' ') {
            buffer[idx++] = c;
            text_putc(c);
        }
    }
    
    buffer[idx] = '\0';
}

