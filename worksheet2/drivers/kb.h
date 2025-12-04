#ifndef KB_H
#define KB_H

#define KB_DATA_REG 0x60
#define KB_STAT_REG 0x64

#define PIC1_CMD_REG 0x20
#define PIC1_DATA_REG 0x21
#define PIC2_CMD_REG 0xA0
#define PIC2_DATA_REG 0xA1

#define PIC_EOI 0x20

#define KB_BS 0x0E
#define KB_ENTER 0x1C
#define KB_LSHIFT 0x2A
#define KB_RSHIFT 0x36
#define KB_LSHIFT_REL 0xAA
#define KB_RSHIFT_REL 0xB6

void kb_setup(void);
char kb_get_char(void);
void kb_get_line(char* buffer, int size);
int kb_has_data(void);

#endif

