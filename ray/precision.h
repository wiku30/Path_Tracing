#pragma once

#define HI_RES 1

#define FULL_RES 600
#define FULL_PRECISION 2000

#if HI_RES == 1
#define RES FULL_RES
#define PRECISION FULL_PRECISION

#elif HI_RES == 0

#define RES 240
#define PRECISION 469

#else
#define RES 200
#define PRECISION 50

#endif

#define ITER_DEPTH 40