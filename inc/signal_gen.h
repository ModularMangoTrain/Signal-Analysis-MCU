#ifndef SIGNAL_GEN_H
#define SIGNAL_GEN_H

#include <stdint.h>

void signal_gen_init(float frequency, float amplitude);
float signal_gen_next_sample(void);

#endif
