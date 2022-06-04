from math import floor

str_bin = ''
number = 2345678909875.345678909765434567 * 2
print('NUBBER:', number)
number2 = number
while number > 0:
    number = floor(number) / 2
    a = floor(number)
    if (number - a) > 0.001:
        str_bin += '1'
    else:
        str_bin += '0'
print()
print(number2)
str_bin = str_bin[::-1]
print(int(str_bin, base=2))

2345678909875.3457
2345678909875.3457
2345678909875