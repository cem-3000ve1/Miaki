/* edition.h -- CID Changer
 *
 * Copyright (C) 2025 LazyPreview
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
 
#ifndef BOOT_H
#define BOOT_H

#include <vitasdk.h>

void boot_parameters(void);
extern int release;
extern int devmode;
extern int delete;
extern int back;

#endif
