/* activation.h -- Activator Menu
 *
 * Copyright (C) 2025 LazyPreview
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <vitasdk.h>

void activator(void);
extern int activated;
extern int expired;
void yellowmsg(void);
extern int lowactivation;

#endif
