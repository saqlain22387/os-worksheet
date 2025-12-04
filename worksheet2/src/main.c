#include "../drivers/text.h"
#include "../drivers/kb.h"
#include "../drivers/repl.h"

int sum3(int p, int q, int r) {
    return p + q + r;
}

int mul(int m, int n) {
    return m * n;
}

int fact_calc(int val) {
    if (val <= 1) return 1;
    int result = 1;
    for (int idx = 2; idx <= val; idx++) {
        result *= idx;
    }
    return result;
}

void main_entry(void) {
    text_clear();
    
    text_set_fg_bg(TXT_GREEN, TXT_BLACK);
    text_write("========================================\n");
    text_write("       BasicOS v1.0 - Booting Up         \n");
    text_write("========================================\n\n");
    
    text_set_fg_bg(TXT_WHITE, TXT_BLACK);
    
    text_write("Testing C functions from assembly:\n");
    text_write("----------------------------------\n");
    
    text_write("sum3(10, 20, 30) = ");
    text_write_int(sum3(10, 20, 30));
    text_write("\n");
    
    text_write("mul(6, 7) = ");
    text_write_int(mul(6, 7));
    text_write("\n");
    
    text_write("fact_calc(5) = ");
    text_write_int(fact_calc(5));
    text_write("\n\n");
    
    text_set_fg_bg(TXT_CYAN, TXT_BLACK);
    text_write("Initializing keyboard...\n");
    text_set_fg_bg(TXT_WHITE, TXT_BLACK);
    
    kb_setup();
    
    text_set_fg_bg(TXT_GREEN, TXT_BLACK);
    text_write("\nSystem ready. Starting REPL...\n\n");
    text_set_fg_bg(TXT_WHITE, TXT_BLACK);
    
    repl_loop();
}

