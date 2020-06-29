from time import *

def quick_algorithm(a,b,c):
    a=a%c
    ans=1
    while b!=0:
        if b&1:
            ans=(ans*a)%c
        b>>=1
        a=(a*a)%c
    return ans

a=1234567
b=long(12345678901234567890)
c=999999997
print("%d"%(quick_algorithm(a,b,c)))
