#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    int development_mode;
    int platform_emulation_dolce;
    int shellbootime;
    int memory_switch;
    unsigned int activation_date;
} lazyconfig;

extern lazyconfig lazyconf;
extern unsigned int act_date;

void act_sm_start(void);
void act_sm_stop(void);

void lazyconf_load(const char *path);

#endif