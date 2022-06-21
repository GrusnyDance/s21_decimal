//
// Created by Nana Daughterless on 6/3/22.
//

#ifndef SRC_CORE_CONSTANTS_H_
#define SRC_CORE_CONSTANTS_H_

enum { OK = 0, CONVERTION_ERROR = 1, BIG_VALUE = 1, SMALL_VALUE, DIV_ZERO };

#define BITS_IN_INT 32
#define BITS_COUNT 3
#define ALL_BIT (BITS_IN_INT * BITS_COUNT)

#define DECIMAL_INFO 3
#define START_EXP_BIT 16
#define END_EXP_BIT 23
#define SIGN_BIT 31

#define MAX_EXPONENT 28

#endif  // SRC_CORE_CONSTANTS_H_
