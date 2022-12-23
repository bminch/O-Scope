#include "parser.h"
#include "cdc.h"
#include "oscope.h"
#include "digout.h"
#include "scope.h"
#include "wavegen.h"

#define CMD_BUFFER_LENGTH   128

STATE_HANDLER_T parser_state, parser_last_state, parser_task;
char cmd_buffer[CMD_BUFFER_LENGTH], *cmd_buffer_pos;
uint16_t cmd_buffer_left;

uint16_t scope_buffer_pos, samples_to_send;

void send_next_val(void);
void send_next_vals(void);
void send_next_val_bin(void);
void send_next_vals_bin(void);

void parser_normal(void);

void ui_handler(char *args);
void dig_handler(char *args);
void scope_handler(char *args);
void wavegen_handler(char *args);
void flash_handler(char *args);

DISPATCH_ENTRY_T root_table[] = {{ "UI", ui_handler }, 
                                 { "DIG", dig_handler }, 
                                 { "SCOPE", scope_handler }, 
                                 { "WAVEGEN", wavegen_handler }, 
                                 { "FLASH", flash_handler }};

#define ROOT_TABLE_ENTRIES      sizeof(root_table) / sizeof(DISPATCH_ENTRY_T)

void led1_handler(char *args);
void led1Q_handler(char *args);
void led2_handler(char *args);
void led2Q_handler(char *args);
void led3_handler(char *args);
void led3Q_handler(char *args);
void sw1Q_handler(char *args);

DISPATCH_ENTRY_T ui_table[] = {{ "LED1", led1_handler },
                               { "LED1?", led1Q_handler },
                               { "LED2", led2_handler }, 
                               { "LED2?", led2Q_handler }, 
                               { "LED3", led3_handler }, 
                               { "LED3?", led3Q_handler }, 
                               { "SW1?", sw1Q_handler }};

#define UI_TABLE_ENTRIES        sizeof(ui_table) / sizeof(DISPATCH_ENTRY_T)

void set_handler(char *args);
void clear_handler(char *args);
void toggle_handler(char *args);
void write_handler(char *args);
void read_handler(char *args);
void od_handler(char *args);
void odQ_handler(char *args);
void mode_handler(char *args);
void modeQ_handler(char *args);
void period_handler(char *args);
void periodQ_handler(char *args);
void duty_handler(char *args);
void dutyQ_handler(char *args);
void width_handler(char *args);
void widthQ_handler(char *args);
void timer1period_handler(char *args);
void timer1periodQ_handler(char *args);

DISPATCH_ENTRY_T dig_table[] = {{ "SET", set_handler }, 
                                { "CLEAR", clear_handler }, 
                                { "TOGGLE", toggle_handler }, 
                                { "WRITE", write_handler }, 
                                { "READ", read_handler }, 
                                { "OD", od_handler }, 
                                { "OD?", odQ_handler }, 
                                { "MODE", mode_handler }, 
                                { "MODE?", modeQ_handler }, 
                                { "PERIOD", period_handler }, 
                                { "PERIOD?", periodQ_handler }, 
                                { "DUTY", duty_handler }, 
                                { "DUTY?", dutyQ_handler }, 
                                { "WIDTH", width_handler }, 
                                { "WIDTH?", widthQ_handler }, 
                                { "T1PERIOD", timer1period_handler }, 
                                { "T1PERIOD?", timer1periodQ_handler }};

#define DIG_TABLE_ENTRIES       sizeof(dig_table) / sizeof(DISPATCH_ENTRY_T)

void ch1gain_handler(char *args);
void ch1gainQ_handler(char *args);
void ch2gain_handler(char *args);
void ch2gainQ_handler(char *args);
void interval_handler(char *args);
void intervalQ_handler(char *args);
void maxavg_handler(char *args);
void maxavgQ_handler(char *args);
void numavgQ_handler(char *args);
void sweepQ_handler(char *args);
void trigger_handler(char *args);
void bufferQ_handler(char *args);
void bufferbinQ_handler(char *args);

DISPATCH_ENTRY_T scope_table[] = {{ "CH1GAIN", ch1gain_handler }, 
                                  { "CH1GAIN?", ch1gainQ_handler }, 
                                  { "CH2GAIN", ch2gain_handler }, 
                                  { "CH2GAIN?", ch2gainQ_handler }, 
                                  { "INTERVAL", interval_handler }, 
                                  { "INTERVAL?", intervalQ_handler }, 
                                  { "MAXAVG", maxavg_handler }, 
                                  { "MAXAVG?", maxavgQ_handler }, 
                                  { "NUMAVG?", numavgQ_handler }, 
                                  { "SWEEP?", sweepQ_handler }, 
                                  { "TRIGGER", trigger_handler }, 
                                  { "BUFFER?", bufferQ_handler }, 
                                  { "BUFFERBIN?", bufferbinQ_handler }};

#define SCOPE_TABLE_ENTRIES     sizeof(scope_table) / sizeof(DISPATCH_ENTRY_T)

void gain_handler(char *args);
void gainQ_handler(char *args);
void shape_handler(char *args);
void shapeQ_handler(char *args);
void freq_handler(char *args);
void freqQ_handler(char *args);
void phase_handler(char *args);
void phaseQ_handler(char *args);
void amp_handler(char *args);
void ampQ_handler(char *args);
void offset_handler(char *args);
void offsetQ_handler(char *args);
void sqadj_handler(char *args);
void sqadjQ_handler(char *args);
void nsqadj_handler(char *args);
void nsqadjQ_handler(char *args);

DISPATCH_ENTRY_T wavegen_table[] = {{ "GAIN", gain_handler }, 
                                    { "GAIN?", gainQ_handler }, 
                                    { "SHAPE", shape_handler }, 
                                    { "SHAPE?", shapeQ_handler }, 
                                    { "FREQ", freq_handler }, 
                                    { "FREQ?", freqQ_handler }, 
                                    { "PHASE", phase_handler }, 
                                    { "PHASE?", phaseQ_handler }, 
                                    { "AMPLITUDE", amp_handler }, 
                                    { "AMPLITUDE?", ampQ_handler }, 
                                    { "OFFSET", offset_handler }, 
                                    { "OFFSET?", offsetQ_handler }, 
                                    { "SQADJ", sqadj_handler }, 
                                    { "SQADJ?", sqadjQ_handler }, 
                                    { "NSQADJ", nsqadj_handler }, 
                                    { "NSQADJ?", nsqadjQ_handler }};

#define WAVEGEN_TABLE_ENTRIES   sizeof(wavegen_table) / sizeof(DISPATCH_ENTRY_T)

void wavegen_offset_interval_handler(char *args);
void wavegen_offset_intervalQ_handler(char *args);
void wavegen_offset_mode_handler(char *args);
void wavegen_offset_modeQ_handler(char *args);
void wavegen_offset_start_handler(char *args);
void wavegen_offset_stop_handler(char *args);
void wavegen_offset_sweepQ_handler(char *args);

DISPATCH_ENTRY_T wavegen_offset_table[] = {{ "INTERVAL", wavegen_offset_interval_handler }, 
                                           { "INTERVAL?", wavegen_offset_intervalQ_handler }, 
                                           { "MODE", wavegen_offset_mode_handler }, 
                                           { "MODE?", wavegen_offset_modeQ_handler }, 
                                           { "START", wavegen_offset_start_handler }, 
                                           { "STOP", wavegen_offset_stop_handler }, 
                                           { "SWEEP?", wavegen_offset_sweepQ_handler }};

#define WAVEGEN_OFFSET_TABLE_ENTRIES    sizeof(wavegen_offset_table) / sizeof(DISPATCH_ENTRY_T)

void flash_erase_handler(char *args);
void flash_read_handler(char *args);
void flash_write_handler(char *args);

DISPATCH_ENTRY_T flash_table[] = {{ "ERASE", flash_erase_handler },
                                  { "READ", flash_read_handler },
                                  { "WRITE", flash_write_handler }};

#define FLASH_TABLE_ENTRIES     sizeof(flash_table) / sizeof(DISPATCH_ENTRY_T)

int16_t str2hex(char *str, uint16_t *num) {
    if (!str)
        return -1;

    while ((*str == ' ') || (*str == '\t'))
        str++;

    *num = 0;
    while (*str) {
        if ((*str >= '0') && (*str <= '9'))
            *num = (*num << 4) + (*str - '0');
        else if ((*str >= 'a') && (*str <= 'f'))
            *num = (*num << 4) + 10 + (*str - 'a');
        else if ((*str >= 'A') && (*str <= 'F'))
            *num = (*num << 4) + 10 + (*str - 'A');
        else
            return -1;
        str++;
    }
    return 0;
}

int16_t str2num(char *str, uint16_t *num) {
    if (!str)
        return -1;

    while ((*str == ' ') || (*str == '\t'))
        str++;

    *num = 0;
    while (*str) {
        if ((*str >= '0') && (*str <= '9'))
            *num = *num * 10 + (*str - '0');
        else
            return -1;
        str++;
    }
    return 0;
}

void hex2str(uint16_t num, char *str) {
    uint16_t digit, i;

    for (i = 0; i < 4; i++) {
        digit = num >> 12;
        if (digit < 10)
            *str = '0' + (uint8_t)digit;
        else
            *str = 'A' + (uint8_t)digit - 10;
        str++;
        num = (num & 0x0FFF) << 4;
    }
    *str = '\0';
}

void hex2str_alt(uint16_t num, char *str) {
    uint16_t digit, i, hit_nonzero_digit = FALSE;

    for (i = 0; i < 4; i++) {
        digit = num >> 12;
        if (digit)
            hit_nonzero_digit = TRUE;
        if ((hit_nonzero_digit) || (i == 3)) {
            if (digit < 10)
                *str = '0' + (uint8_t)digit;
            else
                *str = 'A' + (uint8_t)digit - 10;
            str++;
        }
        num = (num & 0x0FFF) << 4;
    }
    *str = '\0';
}

int16_t str_cmp(char *str1, char *str2) {
    while ((*str1) && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    if (*str1 == *str2)
        return 0;
    else if (*str1 < *str2)
        return -1;
    else
        return 1;
}

int16_t str_ncmp(char *str1, char *str2, uint16_t n) {
    if (n == 0)
        return 0;

    while ((*str1) && (*str2) && (*str1 == *str2) && (--n)) {
        str1++;
        str2++;
    }

    if (*str1 == *str2)
        return 0;
    else if (*str1 < *str2)
        return -1;
    else
        return 1;
}

char *str_tok_r(char *str, char *delim, char **save_str) {
    char *spos, *dpos, *token_start;

    if (!(str) && !(*save_str)) 
        return (char *)NULL;

    // Find the first non-delimiter character in the string
    for (spos = (str) ? str : *save_str; *spos; spos++) {
        for (dpos = delim; *dpos; dpos++) {
            if (*spos == *dpos)
                break;
        }
        if (*dpos == '\0')
            break;
    }
    if (*spos)
        token_start = spos;
    else {
        *save_str = (char *)NULL;
        return (char *)NULL;
    }

    // Find the first delimiter character in the string
    for (; *spos; spos++) {
        for (dpos = delim; *dpos; dpos++) {
            if (*spos == *dpos)
                break;
        }
        if (*spos == *dpos)
            break;
    }
    if (*spos) {
        *spos = '\0';
        *save_str = spos + 1;
    } else {
        *save_str = (char *)NULL;
    }

    return token_start;
}

// UI commands
void ui_handler(char *args) {
    uint16_t i;
    char *command, *remainder;

    remainder = (char *)NULL;
    command = str_tok_r(args, ":, ", &remainder);
    if (command) {
        for (i = 0; i < UI_TABLE_ENTRIES; i++) {
            if (str_cmp(command, ui_table[i].command) == 0) {
                ui_table[i].handler(remainder);
                break;
            }
        }
    }
}

void led1_handler(char *args) {
    char *token, *remainder;
    uint16_t val;

    remainder = (char *)NULL;
    token = str_tok_r(args, ":, ", &remainder);
    if (token) {
        if (str_cmp(token, "ON") == 0) {
            LED1 = ON;
        } else if (str_cmp(token, "OFF") == 0) {
            LED1 = OFF;
        } else if (str_cmp(token, "TOGGLE") == 0) {
            LED1 = !LED1;
        } else if (str2hex(token, &val) == 0) {
            LED1 = (val) ? 1 : 0;
        }
    }
}

void led1Q_handler(char *args) {
    if (LED1 == ON)
        cdc_puts("1\r\n");
    else
        cdc_puts("0\r\n");
}

void led2_handler(char *args) {
    char *token, *remainder;
    uint16_t val;

    remainder = (char *)NULL;
    token = str_tok_r(args, ":, ", &remainder);
    if (token) {
        if (str_cmp(token, "ON") == 0) {
            LED2 = ON;
        } else if (str_cmp(token, "OFF") == 0) {
            LED2 = OFF;
        } else if (str_cmp(token, "TOGGLE") == 0) {
            LED2 = !LED2;
        } else if (str2hex(token, &val) == 0) {
            LED2 = (val) ? 1 : 0;
        }
    }
}

void led2Q_handler(char *args) {
    if (LED2 == ON)
        cdc_puts("1\r\n");
    else
        cdc_puts("0\r\n");
}

void led3_handler(char *args) {
    char *token, *remainder;
    uint16_t val;

    remainder = (char *)NULL;
    token = str_tok_r(args, ":, ", &remainder);
    if (token) {
        if (str_cmp(token, "ON") == 0) {
            LED3 = ON;
        } else if (str_cmp(token, "OFF") == 0) {
            LED3 = OFF;
        } else if (str_cmp(token, "TOGGLE") == 0) {
            LED3 = !LED3;
        } else if (str2hex(token, &val) == 0) {
            LED3 = (val) ? 1 : 0;
        }
    }
}

void led3Q_handler(char *args) {
    if (LED3 == ON)
        cdc_puts("1\r\n");
    else
        cdc_puts("0\r\n");
}

void sw1Q_handler(char *args) {
    if (SW1 == 1)
        cdc_puts("1\r\n");
    else
        cdc_puts("0\r\n");
}

// DIG commands
void dig_handler(char *args) {
    uint16_t i;
    char *command, *remainder;

    remainder = (char *)NULL;
    command = str_tok_r(args, ":, ", &remainder);
    if (command) {
        for (i = 0; i < DIG_TABLE_ENTRIES; i++) {
            if (str_cmp(command, dig_table[i].command) == 0) {
                dig_table[i].handler(remainder);
                break;
            }
        }
    }
}

void set_handler(char *args) {
    uint16_t ch;

    if (args && (str2hex(args, &ch) == 0))
        digout_set(ch);
}

void clear_handler(char *args) {
    uint16_t ch;

    if (args && (str2hex(args, &ch) == 0))
        digout_clear(ch);
}

void toggle_handler(char *args) {
    uint16_t ch;

    if (args && (str2hex(args, &ch) == 0))
        digout_toggle(ch);
}

void write_handler(char *args) {
    uint16_t ch, val;
    char *arg1, *arg2;

    arg2 = (char *)NULL;
    arg1 = str_tok_r(args, ", ", &arg2);
    if (arg1 && arg2) {
        if ((str2hex(arg1, &ch) == 0) && (str2hex(arg2, &val) == 0)) {
            digout_write(ch, val);
        }
    }
}

void read_handler(char *args) {
    uint16_t ch;
    char str[5];

    if (args && (str2hex(args, &ch) == 0)) {
        hex2str_alt(digout_read(ch), str);
        cdc_puts(str);
        cdc_puts("\r\n");
    }
}

void od_handler(char *args) {
    uint16_t ch, val;
    char *arg1, *arg2;

    arg2 = (char *)NULL;
    arg1 = str_tok_r(args, ", ", &arg2);
    if (arg1 && arg2) {
        if ((str2hex(arg1, &ch) == 0) && (str2hex(arg2, &val) == 0)) {
            digout_set_od(ch, val);
        }
    }
}

void odQ_handler(char *args) {
    uint16_t ch;
    char str[5];

    if (args && (str2hex(args, &ch) == 0)) {
        hex2str_alt(digout_get_od(ch), str);
        cdc_puts(str);
        cdc_puts("\r\n");
    }
}

void mode_handler(char *args) {
    uint16_t ch, mode;
    char *arg1, *arg2;

    arg2 = (char *)NULL;
    arg1 = str_tok_r(args, ", ", &arg2);
    if (arg1 && arg2) {
        if ((str2hex(arg1, &ch) == 0) && (str2hex(arg2, &mode) == 0)) {
            digout_set_mode(ch, mode);
        }
    }
}

void modeQ_handler(char *args) {
    uint16_t ch;
    char str[5];

    if (args && (str2hex(args, &ch) == 0)) {
        hex2str_alt(digout_get_mode(ch), str);
        cdc_puts(str);
        cdc_puts("\r\n");
    }
}

void period_handler(char *args) {
    uint16_t ch, period;
    char *arg1, *arg2;

    arg2 = (char *)NULL;
    arg1 = str_tok_r(args, ", ", &arg2);
    if (arg1 && arg2) {
        if ((str2hex(arg1, &ch) == 0) && (str2hex(arg2, &period) == 0)) {
            digout_set_period(ch, period);
        }
    }
}

void periodQ_handler(char *args) {
    uint16_t ch;
    char str[5];

    if (args && (str2hex(args, &ch) == 0)) {
        hex2str_alt(digout_get_period(ch), str);
        cdc_puts(str);
        cdc_puts("\r\n");
    }
}

void duty_handler(char *args) {
    uint16_t ch, duty;
    char *arg1, *arg2;

    arg2 = (char *)NULL;
    arg1 = str_tok_r(args, ", ", &arg2);
    if (arg1 && arg2) {
        if ((str2hex(arg1, &ch) == 0) && (str2hex(arg2, &duty) == 0)) {
            digout_set_duty(ch, duty);
        }
    }
}

void dutyQ_handler(char *args) {
    uint16_t ch;
    char str[5];

    if (args && (str2hex(args, &ch) == 0)) {
        hex2str_alt(digout_get_duty(ch), str);
        cdc_puts(str);
        cdc_puts("\r\n");
    }
}

void width_handler(char *args) {
    uint16_t ch, width;
    char *arg1, *arg2;

    arg2 = (char *)NULL;
    arg1 = str_tok_r(args, ", ", &arg2);
    if (arg1 && arg2) {
        if ((str2hex(arg1, &ch) == 0) && (str2hex(arg2, &width) == 0)) {
            digout_set_width(ch, width);
        }
    }
}

void widthQ_handler(char *args) {
    uint16_t ch;
    char str[5];

    if (args && (str2hex(args, &ch) == 0)) {
        hex2str_alt(digout_get_width(ch), str);
        cdc_puts(str);
        cdc_puts("\r\n");
    }
}

void timer1period_handler(char *args) {
    uint16_t val1, val2;
    char *arg1, *arg2;

    arg2 = (char *)NULL;
    arg1 = str_tok_r(args, ", ", &arg2);
    if (arg1 && arg2) {
        if ((str2hex(arg1, &val1) == 0) && (str2hex(arg2, &val2) == 0)) {
            digout_set_timer1_period(val1, val2);
        }
    }
}

void timer1periodQ_handler(char *args) {
    char str[5];

    hex2str_alt(PR1, str);
    cdc_puts(str);
    cdc_putc(',');
    hex2str_alt(T1CON, str);
    cdc_puts(str);
    cdc_puts("\r\n");
}

// SCOPE commands
void scope_handler(char *args) {
    uint16_t i;
    char *command, *remainder;

    remainder = (char *)NULL;
    command = str_tok_r(args, ":, ", &remainder);
    if (command) {
        for (i = 0; i < SCOPE_TABLE_ENTRIES; i++) {
            if (str_cmp(command, scope_table[i].command) == 0) {
                scope_table[i].handler(remainder);
                break;
            }
        }
    }
}

void ch1gain_handler(char *args) {
    char *token, *remainder;
    uint16_t val;

    remainder = (char *)NULL;
    token = str_tok_r(args, ", ", &remainder);
    if (token && (str2hex(token, &val) == 0))
        CH1_GAIN = (val) ? 1 : 0;
}

void ch1gainQ_handler(char *args) {
    if (CH1_GAIN == 1)
        cdc_puts("1\r\n");
    else
        cdc_puts("0\r\n");
}

void ch2gain_handler(char *args) {
    char *token, *remainder;
    uint16_t val;

    remainder = (char *)NULL;
    token = str_tok_r(args, ", ", &remainder);
    if (token && (str2hex(token, &val) == 0))
        CH2_GAIN = (val) ? 1 : 0;
}

void ch2gainQ_handler(char *args) {
    if (CH2_GAIN == 1)
        cdc_puts("1\r\n");
    else
        cdc_puts("0\r\n");
}

void interval_handler(char *args) {
    uint16_t val1, val2;
    char *arg1, *arg2;

    arg2 = (char *)NULL;
    arg1 = str_tok_r(args, ", ", &arg2);
    if (arg1 && arg2) {
        if ((str2hex(arg1, &val1) == 0) && (str2hex(arg2, &val2) == 0)) {
            set_period(val1, val2);
        }
    }
}

void intervalQ_handler(char *args) {
    char str[5];

    hex2str_alt(PR2, str);
    cdc_puts(str);
    cdc_putc(',');
    hex2str_alt(T2CON, str);
    cdc_puts(str);
    cdc_puts("\r\n");
}

void maxavg_handler(char *args) {
    char *token, *remainder;
    uint16_t val;

    remainder = (char *)NULL;
    token = str_tok_r(args, ", ", &remainder);
    if (token && (str2hex(token, &val) == 0)) {
        if (val < 5)
            set_max_avg(val);
    }
}

void maxavgQ_handler(char *args) {
    char str[5];

    hex2str_alt(get_max_avg(), str);
    cdc_puts(str);
    cdc_puts("\r\n");
}

void numavgQ_handler(char *args) {
    char str[5];

    hex2str_alt(get_num_avg(), str);
    cdc_puts(str);
    cdc_puts("\r\n");
}

void sweepQ_handler(char *args) {
    char str[5];

    hex2str_alt(get_sweep_in_progress(), str);
    cdc_puts(str);
    cdc_putc(',');
    hex2str_alt(get_samples_left(), str);
    cdc_puts(str);
    cdc_puts("\r\n");
}

void trigger_handler(char *args) {
    trigger_sweep();
    set_samples_left(DMACNT1);
}

void bufferQ_handler(char *args) {
    uint16_t val1, val2;
    char *arg1, *arg2;

    arg2 = (char *)NULL;
    arg1 = str_tok_r(args, ", ", &arg2);
    if (arg1 && arg2) {
        if ((str2hex(arg1, &val1) == 0) && (str2hex(arg2, &val2) == 0)) {
            set_samples_left(DMACNT1);
            if (val1 < SCOPE_BUFFER_SIZE) {
                scope_buffer_pos = val1;
                samples_to_send = ((val1 + val2) <= SCOPE_BUFFER_SIZE) ? val2 : SCOPE_BUFFER_SIZE - val1;
                parser_task = send_next_vals;
            }
        }
    }
}

void bufferbinQ_handler(char *args) {
    uint16_t val1, val2;
    char *arg1, *arg2;

    arg2 = (char *)NULL;
    arg1 = str_tok_r(args, ", ", &arg2);
    if (arg1 && arg2) {
        if ((str2hex(arg1, &val1) == 0) && (str2hex(arg2, &val2) == 0)) {
            set_samples_left(DMACNT1);
            if (val1 < SCOPE_BUFFER_SIZE) {
                scope_buffer_pos = val1;
                samples_to_send = ((val1 + val2) <= SCOPE_BUFFER_SIZE) ? val2 : SCOPE_BUFFER_SIZE - val1;
                parser_task = send_next_vals_bin;
            }
        }
    }
}

void send_next_val(void) {
    char str[5];

    if (cdc_tx_buffer_space() > 5) {
        hex2str_alt(scope_buffer[scope_buffer_pos++], str);
        cdc_puts(str);
        samples_to_send--;
        if (samples_to_send > 0)
            cdc_puts(",");
        else {
            cdc_puts("\r\n");
            parser_task = (STATE_HANDLER_T)NULL;
        }
    }
}

void send_next_vals(void) {
    char str[5];

    while (cdc_tx_buffer_space() > 5) {
        hex2str_alt(scope_buffer[scope_buffer_pos++], str);
        cdc_puts(str);
        samples_to_send--;
        if (samples_to_send > 0)
            cdc_puts(",");
        else {
            cdc_puts("\r\n");
            parser_task = (STATE_HANDLER_T)NULL;
            break;
        }
    }
}

void send_next_val_bin(void) {
    WORD val;

    if (cdc_tx_buffer_space() > 2) {
        val.w = scope_buffer[scope_buffer_pos++];
        cdc_putc(val.b[0]);
        cdc_putc(val.b[1]);
        samples_to_send--;
        if (samples_to_send == 0) {
            parser_task = (STATE_HANDLER_T)NULL;
        }
    }
}

void send_next_vals_bin(void) {
    WORD val;

    while (cdc_tx_buffer_space() > 2) {
        val.w = scope_buffer[scope_buffer_pos++];
        cdc_putc(val.b[0]);
        cdc_putc(val.b[1]);
        samples_to_send--;
        if (samples_to_send == 0) {
            parser_task = (STATE_HANDLER_T)NULL;
            break;
        }
    }
}

// WAVEGEN commands
void wavegen_handler(char *args) {
    uint16_t i;
    char *command, *remainder;

    remainder = (char *)NULL;
    command = str_tok_r(args, ":, ", &remainder);
    if (command) {
        for (i = 0; i < WAVEGEN_TABLE_ENTRIES; i++) {
            if (str_cmp(command, wavegen_table[i].command) == 0) {
                wavegen_table[i].handler(remainder);
                break;
            }
        }
    }
}

void gain_handler(char *args) {
    char *token, *remainder;
    uint16_t val;

    remainder = (char *)NULL;
    token = str_tok_r(args, ", ", &remainder);
    if (token && (str2hex(token, &val) == 0))
        WG_GAIN = (val) ? 1 : 0;
}

void gainQ_handler(char *args) {
    if (WG_GAIN == 1)
        cdc_puts("1\r\n");
    else
        cdc_puts("0\r\n");
}

void shape_handler(char *args) {
    char *token, *remainder;
    uint16_t val;

    remainder = (char *)NULL;
    token = str_tok_r(args, ":, ", &remainder);
    if (token) {
        if (str_cmp(token, "DC") == 0) {
            set_shape(DC);
        } else if (str_cmp(token, "SIN") == 0) {
            set_shape(SIN);
        } else if (str_cmp(token, "SQUARE") == 0) {
            set_shape(SQUARE);
        } else if (str_cmp(token, "TRIANGLE") == 0) {
            set_shape(TRIANGLE);
        } else if (str2hex(token, &val) == 0) {
            set_shape(val);
        }
    }
}

void shapeQ_handler(char *args) {
    char str[5];

    hex2str_alt(get_shape(), str);
    cdc_puts(str);
    cdc_puts("\r\n");
}

void freq_handler(char *args) {
    uint16_t val_l, val_h;
    char *arg1, *arg2;

    arg2 = (char *)NULL;
    arg1 = str_tok_r(args, ", ", &arg2);
    if (arg1 && arg2) {
        if ((str2hex(arg1, &val_l) == 0) && (str2hex(arg2, &val_h) == 0)) {
            set_freq(val_l, val_h);
        }
    }
}

void freqQ_handler(char *args) {
    char str[5];

    hex2str_alt(get_freq_l(), str);
    cdc_puts(str);
    cdc_putc(',');
    hex2str_alt(get_freq_h(), str);
    cdc_puts(str);
    cdc_puts("\r\n");
}

void phase_handler(char *args) {
    char *token, *remainder;
    uint16_t val;

    remainder = (char *)NULL;
    token = str_tok_r(args, ", ", &remainder);
    if (token && (str2hex(token, &val) == 0)) {
        set_phase(val);
    }
}

void phaseQ_handler(char *args) {
    char str[5];

    hex2str_alt(get_phase(), str);
    cdc_puts(str);
    cdc_puts("\r\n");
}

void amp_handler(char *args) {
    char *token, *remainder;
    uint16_t val;

    remainder = (char *)NULL;
    token = str_tok_r(args, ", ", &remainder);
    if (token && (str2hex(token, &val) == 0)) {
        set_amplitude(val);
    }
}

void ampQ_handler(char *args) {
    char str[5];

    hex2str_alt(get_amplitude(), str);
    cdc_puts(str);
    cdc_puts("\r\n");
}

void offset_handler(char *args) {
    uint16_t i, val;
    char *command, *remainder;

    remainder = (char *)NULL;
    command = str_tok_r(args, ":, ", &remainder);
    if (command) {
        for (i = 0; i < WAVEGEN_OFFSET_TABLE_ENTRIES; i++) {
            if (str_cmp(command, wavegen_offset_table[i].command) == 0) {
                wavegen_offset_table[i].handler(remainder);
                break;
            }
        }
        if ((i == WAVEGEN_OFFSET_TABLE_ENTRIES) && (str2hex(command, &val) == 0)) {
            set_offset(val);
        }
    }
}

void offsetQ_handler(char *args) {
    char str[5];

    hex2str_alt(get_offset(), str);
    cdc_puts(str);
    cdc_puts("\r\n");
}

void sqadj_handler(char *args) {
    char *token, *remainder;
    uint16_t val;

    remainder = (char *)NULL;
    token = str_tok_r(args, ", ", &remainder);
    if (token && (str2hex(token, &val) == 0)) {
        set_sq_offset_adj(val);
    }
}

void sqadjQ_handler(char *args) {
    char str[5];

    hex2str_alt(get_sq_offset_adj(), str);
    cdc_puts(str);
    cdc_puts("\r\n");
}

void nsqadj_handler(char *args) {
    char *token, *remainder;
    uint16_t val;

    remainder = (char *)NULL;
    token = str_tok_r(args, ", ", &remainder);
    if (token && (str2hex(token, &val) == 0)) {
        set_nsq_offset_adj(val);
    }
}

void nsqadjQ_handler(char *args) {
    char str[5];

    hex2str_alt(get_nsq_offset_adj(), str);
    cdc_puts(str);
    cdc_puts("\r\n");
}

// WAVEGEN:OFFSET commands
void wavegen_offset_interval_handler(char *args) {
    uint16_t val1, val2;
    char *arg1, *arg2;

    arg2 = (char *)NULL;
    arg1 = str_tok_r(args, ", ", &arg2);
    if (arg1 && arg2) {
        if ((str2hex(arg1, &val1) == 0) && (str2hex(arg2, &val2) == 0)) {
            wavegen_offset_set_interval(val1, val2);
        }
    }
}

void wavegen_offset_intervalQ_handler(char *args) {
    char str[5];

    hex2str_alt(PR3, str);
    cdc_puts(str);
    cdc_putc(',');
    hex2str_alt(T3CON, str);
    cdc_puts(str);
    cdc_puts("\r\n");
}

void wavegen_offset_mode_handler(char *args) {
    char *token, *remainder;
    uint16_t val;

    remainder = (char *)NULL;
    token = str_tok_r(args, ":, ", &remainder);
    if (token) {
        if (str_cmp(token, "SINGLE") == 0) {
            wavegen_offset_set_mode(0);
        } else if (str_cmp(token, "REPEAT") == 0) {
            wavegen_offset_set_mode(1);
        } else if (str2hex(token, &val) == 0) {
            wavegen_offset_set_mode((val) ? 1 : 0);
        }
    }
}

void wavegen_offset_modeQ_handler(char *args) {
    if (wavegen_offset_get_mode() == 1)
        cdc_puts("1\r\n");
    else
        cdc_puts("0\r\n");
}

void wavegen_offset_start_handler(char *args) {
    wavegen_offset_start();
}

void wavegen_offset_stop_handler(char *args) {
    wavegen_offset_stop();
}

void wavegen_offset_sweepQ_handler(char *args) {
    char str[5];

    if (T3CONbits.TON == 1)
        cdc_puts("1,");
    else
        cdc_puts("0,");
    hex2str_alt(wavegen_offset_get_samples_left(), str);
    cdc_puts(str);
    cdc_puts("\r\n");
}

// FLASH commands
void flash_handler(char *args) {
    uint16_t i;
    char *command, *remainder;

    remainder = (char *)NULL;
    command = str_tok_r(args, ":, ", &remainder);
    if (command) {
        for (i = 0; i < FLASH_TABLE_ENTRIES; i++) {
            if (str_cmp(command, flash_table[i].command) == 0) {
                flash_table[i].handler(remainder);
                break;
            }
        }
    }
}

void flash_erase_handler(char *args) {
    uint16_t val1, val2;
    char *arg1, *arg2;

    arg2 = (char *)NULL;
    arg1 = str_tok_r(args, ", ", &arg2);
    if (arg1 && arg2) {
        if ((str2hex(arg1, &val1) == 0) && (str2hex(arg2, &val2) == 0)) {
            NVMCON = 0x4042;                // set up NVMCON to erase a page of program memory
            __asm__("push _TBLPAG");
            TBLPAG = val1;
            __builtin_tblwtl(val2, 0x0000);
            __asm__("disi #16");            // disable interrupts for 16 cycles
            __builtin_write_NVM();          // issue the unlock sequence and perform the write
            while (NVMCONbits.WR == 1) {}   // wait until the write is complete
            NVMCONbits.WREN = 0;            // disable further writes to program memory
            __asm__("pop _TBLPAG");
        }
    }
}

void flash_read_handler(char *args) {
    uint16_t val1, val2, val3;
    char *arg, *remainder;
    char str[5];
    WORD temp;

    remainder = (char *)NULL;
    arg = str_tok_r(args, ", ", &remainder);
    if (str2hex(arg, &val1) != 0)
        return;
    arg = str_tok_r((char *)NULL, ", ", &remainder);
    if (str2hex(arg, &val2) != 0)
        return;
    arg = str_tok_r((char *)NULL, ", ", &remainder);
    if (str2hex(arg, &val3) != 0)
        return;

    __asm__("push _TBLPAG");
    TBLPAG = val1;
    for (val1 = 0; val1 < val3; val2 += 2) {
        temp.w = __builtin_tblrdl(val2);
        hex2str_alt(temp.b[0], str);
        cdc_puts(str);
        cdc_putc(',');
        hex2str_alt(temp.b[1], str);
        cdc_puts(str);
        cdc_putc(',');
        temp.w = __builtin_tblrdh(val2);
        hex2str_alt(temp.b[0], str);
        cdc_puts(str);
        cdc_putc(',');
        hex2str_alt(temp.b[1], str);
        cdc_puts(str);
        val1 += 4;
        if (val1 < val3)
            cdc_putc(',');
        else
            cdc_puts("\r\n");
    }
    __asm__("pop _TBLPAG");                
}

void flash_write_handler(char *args) {
    uint16_t val1, val2, i;
    char *arg, *remainder;
    WORD temp;

    remainder = (char *)NULL;
    arg = str_tok_r(args, ", ", &remainder);
    if (str2hex(arg, &val1) != 0)
        return;

    arg = str_tok_r((char *)NULL, ", ", &remainder);
    if (str2hex(arg, &val2) != 0)
        return;

    NVMCON = 0x4001;                // set up NVMCON to program a row of program memory
    __asm__("push _TBLPAG");        // save the value of TBLPAG
    TBLPAG = val1;
    val1 = val2 & 0xFFF8;
    for (i = 0; i < 128; i += 2) {
        __builtin_tblwtl(val1 + i, 0xFFFF);
        __builtin_tblwth(val1 + i + 1, 0x00FF);
    }

    for (;; val2 += 2) {
        arg = str_tok_r((char *)NULL, ", ", &remainder);
        if (!arg) 
            break;
        temp.b[0] = (str2hex(arg, &val1) == 0) ? (uint8_t)val1 : 0xFF;

        arg = str_tok_r((char *)NULL, ", ", &remainder);
        if (!arg) 
            break;
        temp.b[1] = (str2hex(arg, &val1) == 0) ? (uint8_t)val1 : 0xFF;

        __builtin_tblwtl(val2, temp.w);

        arg = str_tok_r((char *)NULL, ", ", &remainder);
        if (!arg) 
            break;
        temp.b[0] = (str2hex(arg, &val1) == 0) ? (uint8_t)val1 : 0xFF;

        arg = str_tok_r((char *)NULL, ", ", &remainder);
        if (!arg) 
            break;
        temp.b[1] = (str2hex(arg, &val1) == 0) ? (uint8_t)val1 : 0x00;

        __builtin_tblwth(val2, temp.w);
    }

    __asm__("disi #16");            // disable interrupts for 16 cycles
    __builtin_write_NVM();          // issue the unlock sequence and perform the write
    while (NVMCONbits.WR == 1) {}   // wait until the write is done
    NVMCONbits.WREN = 0;            // disable further writes to program memory
    __asm__("pop _TBLPAG");         // restore original value to TBLPAG
}

void init_parser(void) {
    cmd_buffer_pos = cmd_buffer;
    cmd_buffer_left = CMD_BUFFER_LENGTH;

    parser_state = parser_normal;
    parser_last_state = (STATE_HANDLER_T)NULL;
    parser_task = (STATE_HANDLER_T)NULL;
}

void parser_normal(void) {
    uint8_t ch;
    uint16_t i;
    char *command, *remainder;

    if (parser_state != parser_last_state) {
        parser_last_state = parser_state;
        cmd_buffer_pos = cmd_buffer;
        cmd_buffer_left = CMD_BUFFER_LENGTH;
    }

    if (parser_task)
        parser_task();

    if (cdc_in_waiting() > 0) {
        ch = cdc_getc();
        if (cmd_buffer_left == 1) {
            cmd_buffer_pos = cmd_buffer;
            cmd_buffer_left = CMD_BUFFER_LENGTH;

            *cmd_buffer_pos++ = ch;
            cmd_buffer_left--;
        } else if (ch == '\r') {
            *cmd_buffer_pos = '\0';

//            cdc_putc('[');
//            cdc_puts(cmd_buffer);
//            cdc_puts("]\r\n");

            remainder = (char *)NULL;
            command = str_tok_r(cmd_buffer, ":, ", &remainder);
            if (command) {
                for (i = 0; i < ROOT_TABLE_ENTRIES; i++) {
                    if (str_cmp(command, root_table[i].command) == 0) {
                        root_table[i].handler(remainder);
                        break;
                    }
                }
            }

            cmd_buffer_pos = cmd_buffer;
            cmd_buffer_left = CMD_BUFFER_LENGTH;
        } else {
            *cmd_buffer_pos++ = ch;
            cmd_buffer_left--;
        }
    }

    if (parser_state != parser_last_state) {
        parser_task = (STATE_HANDLER_T)NULL;
    }
}

