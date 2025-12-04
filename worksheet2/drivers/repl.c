#include "repl.h"
#include "text.h"
#include "kb.h"

static int eq(const char* a, const char* b) {
    while (*a && *b) {
        if (*a != *b) return 0;
        a++;
        b++;
    }
    return *a == *b;
}

static int begins(const char* str, const char* prefix) {
    while (*prefix) {
        if (*str != *prefix) return 0;
        str++;
        prefix++;
    }
    return 1;
}

static const char* trim(const char* s) {
    while (*s == ' ') s++;
    return s;
}

static void do_menu(void) {
    text_set_fg_bg(TXT_CYAN, TXT_BLACK);
    text_write("\nAvailable commands:\n");
    text_set_fg_bg(TXT_WHITE, TXT_BLACK);
    text_write("  menu     - Show this help message\n");
    text_write("  reset    - Clear the screen\n");
    text_write("  show     - Display the provided text\n");
    text_write("  ver      - Display OS version\n");
    text_write("  quit     - Prepare system for shutdown\n");
    text_write("  shade    - Change text color (0-15)\n");
    text_write("  exec     - Run test functions\n");
    text_write("\n");
}

static void do_ver(void) {
    text_set_fg_bg(TXT_GREEN, TXT_BLACK);
    text_write("\nBasicOS v1.0\n");
    text_set_fg_bg(TXT_LIGHT_GREY, TXT_BLACK);
    text_write("A simple operating system for learning\n");
    text_write("Developed for OS Development Course\n\n");
    text_set_fg_bg(TXT_WHITE, TXT_BLACK);
}

static void do_reset(void) {
    text_clear();
}

static void do_show(const char* arg) {
    arg = trim(arg);
    text_write(arg);
    text_write("\n");
}

static void do_quit(void) {
    text_set_fg_bg(TXT_YELLOW, TXT_BLACK);
    text_write("\nPreparing system for shutdown...\n");
    text_write("It is now safe to turn off your computer.\n");
    text_set_fg_bg(TXT_WHITE, TXT_BLACK);
    
    while(1) {
        __asm__ __volatile__("cli; hlt");
    }
}

static void do_shade(const char* arg) {
    arg = trim(arg);
    if (*arg >= '0' && *arg <= '9') {
        int clr = *arg - '0';
        if (*(arg+1) >= '0' && *(arg+1) <= '5') {
            clr = clr * 10 + (*(arg+1) - '0');
        }
        if (clr >= 0 && clr <= 15) {
            text_set_fg_bg(clr, TXT_BLACK);
            text_write("Color changed.\n");
            return;
        }
    }
    text_write("Usage: shade <0-15>\n");
}

extern int sum3(int a, int b, int c);
extern int mul(int a, int b);
extern int fact_calc(int n);

static void do_exec(void) {
    text_set_fg_bg(TXT_CYAN, TXT_BLACK);
    text_write("\nRunning C function tests:\n");
    text_set_fg_bg(TXT_WHITE, TXT_BLACK);
    
    text_write("sum3(5, 10, 15) = ");
    text_write_int(sum3(5, 10, 15));
    text_write("\n");
    
    text_write("mul(8, 9) = ");
    text_write_int(mul(8, 9));
    text_write("\n");
    
    text_write("fact_calc(6) = ");
    text_write_int(fact_calc(6));
    text_write("\n\n");
}

static void execute(const char* line) {
    line = trim(line);
    
    if (*line == '\0') {
        return;
    } else if (eq(line, "menu")) {
        do_menu();
    } else if (eq(line, "reset")) {
        do_reset();
    } else if (eq(line, "ver")) {
        do_ver();
    } else if (eq(line, "quit")) {
        do_quit();
    } else if (eq(line, "exec")) {
        do_exec();
    } else if (begins(line, "show ")) {
        do_show(line + 5);
    } else if (begins(line, "shade ")) {
        do_shade(line + 6);
    } else if (eq(line, "show")) {
        text_write("\n");
    } else {
        text_set_fg_bg(TXT_RED, TXT_BLACK);
        text_write("Unknown command: ");
        text_write(line);
        text_write("\nType 'menu' for available commands.\n");
        text_set_fg_bg(TXT_WHITE, TXT_BLACK);
    }
}

void repl_loop(void) {
    char input_buf[MAX_INPUT];
    
    while (1) {
        text_set_fg_bg(TXT_GREEN, TXT_BLACK);
        text_write("básicos");
        text_set_fg_bg(TXT_WHITE, TXT_BLACK);
        text_write("> ");
        
        kb_get_line(input_buf, MAX_INPUT);
        
        execute(input_buf);
    }
}

