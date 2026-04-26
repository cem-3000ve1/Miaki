#include <psp2kern/kernel/sysmem.h>
#include <psp2kern/io/fcntl.h>
#include <psp2kern/kernel/sysclib.h>
#include <psp2kern/kernel/debug.h> 
#include "config.h"

#define LOG(fmt, ...) ksceDebugPrintf("[LazyLoader      ]:" fmt "\n", ##__VA_ARGS__)
lazyconfig lazyconf = {0};
unsigned int act_date = 0;

static void parse_line(const char *line) {
    // allow commentary
    if (line[0] == '#' || line[0] == '\0' || line[0] == '\n')
        return 0;

    char key[64] = {0};
    char value[64] = {0};

    // K = key V = value
    int k = 0, v = 0;

    while (line[k] && line[k] != '=' && line[k] != '\n') {
        key[v++] = line[k++];
    }
    key[v] = '\0';

    if (line[k] != '=') return 0;
    k++;

    v = 0;
    while(line[k] && line[k] != '\n' && line[k] != '\r') {
        value[v++] = line[k++];
    }
    value[v] = '\0';

    int val = 0;
    if(value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) {
        for (int s = 2; value[s] != '\0'; s++) {
            char c = value[s];
            if (c >= '0' && c <= '9')   val = val * 16 + (c - '0');
            else if (c >= 'a' && c <= 'f')   val = val * 16 + (c - 'a' + 10);
            else if (c >= 'A' && c <= 'F')   val = val * 16 + (c - 'A' + 10);
            else break;
        } 
    } else {
        for (int s = 0; value[s] >= '0' && value[s] <= '9'; s++) {
            val = val * 10 + (value[s] - '0');
        }
    }


    if (strncmp(key, "development_mode", 64) == 0) {
        lazyconf.development_mode = val;
    } 
    
    if (strncmp(key, "platform_emulation_dolce", 64) == 0) {
        lazyconf.platform_emulation_dolce = val;
    }

    if (strncmp(key, "shell_boot_time", 64) == 0) {
        lazyconf.shellbootime = val;
    }

    if (strncmp(key, "memory_switch", 64) == 0) {
        lazyconf.memory_switch = val;
    }

    if (strncmp(key, "activation_date", 64) == 0) {
        lazyconf.activation_date = (unsigned int)val;
        act_date = lazyconf.activation_date;
    }
}

void lazyconf_load(const char *path) {
    SceUID fd = ksceIoOpen(path, SCE_O_RDONLY, 0);
     if (fd < 0) {
        LOG("failed to open config: 0x%08X\n", fd);
        return 0;
    }
    LOG("config Loaded \n");

    char buf[512];
    char line[128];
    int  line_pos = 0;
    int  bytes_read;

    while ((bytes_read = ksceIoRead(fd, buf, sizeof(buf) - 1)) > 0) {
        buf[bytes_read] = '\0';
        for (int i = 0; i < bytes_read; i++) {
            if (buf[i] == '\n') {
                line[line_pos] = '\0';
                parse_line(line);
                line_pos = 0;
            } else {
                if (line_pos < (int)sizeof(line) - 1)
                    line[line_pos++] = buf[i];
            }
        }
    }

    if (line_pos > 0) {
        line[line_pos] = '\0';
        parse_line(line);
    }

    ksceIoClose(fd);
}
