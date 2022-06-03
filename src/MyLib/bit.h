//
// Created by Nana Daughterless on 6/3/22.
//

#ifndef S21_DECIMAL_BIT_H
#define S21_DECIMAL_BIT_H

#define _2(i) (1 << i)

#define ON_BIT(int, bit) (int |= _2(bit))
#define OFF_BIT(int, bit) (int &= (~_2(bit)))
#define SET_BIT(int, bit, new_bit) (OFF_BIT(int, bit) + 1 && new_bit && ON_BIT(int, bit))

#define GET_BIT(int, bit) (int & _2(bit))

#endif //S21_DECIMAL_BIT_H
