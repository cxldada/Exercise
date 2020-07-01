#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from hashlib import md5

def Hash(context:str):
    context = context.zfill(8)
    result = md5(bytes(context, 'utf8'))
    for i in range(0, 10000000):
        result = md5(result.digest())
    
    if result.hexdigest() == '5f4654140971c47658de19d62ba472b6':
        return True

def test():
    for i in range(11111111, 99999999):
        if Hash(str(i)):
            break
        print(i)


test()
