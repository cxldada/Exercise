#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys

print(sys.argv[0]);

for n in range(2,10):
    for x in range(2,n):
        if n % x == 0:
            print(n,'equals',x,'*',n//x)
            break
    else:
        print(n,'is a prime number')

def fib(n):
    a,b = 0,1
    while a < n:
        print(a,end=' ')
        a,b = b,a+b
    print()

fib(2000)

def fib2(n):
    """Do nothing, but document it

    No really, it doesn't do anything.
    """
    result = []
    a,b = 0,1
    while a < n:
        result.append(a)
        a,b = b,a+b
    return result

f100 = fib2(100)

for f in f100:
    print(f,end=' ')

pairs = [(1, 'one'), (2, 'two'), (3, 'three'), (4, 'four')]
pairs.sort(key = lambda pair:pair[1])
print(pairs)


print(fib2.__doc__)


def f(ham: str, eggs: str ='eggs') -> str:
    print("Annotations:", f.__annotations__)
    print("Arguments:",ham,eggs)
    return ham + ' and ' + eggs

f('spam')
