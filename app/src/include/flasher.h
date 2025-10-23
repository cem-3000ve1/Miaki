#ifndef FLASHER_H
#define FLASHER_H
#include <vitasdk.h>

void cleanup(void);
void lock(void);
void extract(void);
void vercheck(void);
void decrypt(void);
void join(void);
void restore(void);
void backup(void);
void flash(void);
void upgrade(void);
void uninstall(void);
void install(void);
void config(void);

#endif
