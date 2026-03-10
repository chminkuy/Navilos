// memio.h

#define SET_BIT(value, bit) ((value) |= (1U << (bit)))
#define CLEAR_BIT(value, bit) ((value) &= ~(1U << (bit)))