#pragma once
#define PART_TM4C1294NCPDT
#define TARGET_IS_TM4C129_RA2
//Include the annoying TI preamble headers
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/inc/hw_memmap.h"
#include "driverlib/inc/hw_types.h"
#include "driverlib/pin_map.h"
//System clock speed
#include <stddef.h>
extern size_t system_clock;