#ifndef GAME_H
#define GAME_H

#include "flags.h"
#include "macro.h"

#ifdef TOSLIKE
int DLL_PUBLIC init();
#else
int DLL_PUBLIC init(init_cfg_t cfg);
#endif
int DLL_PUBLIC check_if_quitting(void);
void DLL_PUBLIC loop(void);
int quit(void);

#endif
