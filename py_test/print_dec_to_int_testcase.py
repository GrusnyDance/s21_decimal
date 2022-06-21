from my_decimal import MyDecimal
from sys import argv


def print_dec_to_int_testcase():
    a = MyDecimal()
    a.print()
    g = int(a.decimal)
    if g < 0 and abs(g) < 2**31:
        print(g % 2**31 - 2**31)
    else:
        print(g % 2**31)


if __name__ == '__main__':
    for i in range(int(argv[1]), -1, -1):
        print_dec_to_int_testcase()
