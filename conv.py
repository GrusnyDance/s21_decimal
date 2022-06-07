line = input().replace('-', ':')
line = line.strip("-:")[::-1]

g = line.split(':')
sys = g[0]
sign = -1 if g[0][0] == '1' else 1
exponent = 10 ** int(g[0][1:].replace('X', ''), base=2)
number = int(''.join(g[1:]), base=2)
# print()
print("\tCODE NUMBER:\t\t", sign * number)
print("\tEXPONENT:\t\t\t", exponent)
print("\tFINALY:\t\t\t\t%0.28f"%(sign * number / exponent))
# print()