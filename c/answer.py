#!/usr/bin/python
# -*- coding: utf-8 -*-
from __future__ import division

nu = 1
f = open("./log")
line = f.readline()
while line:
    a = eval(line)
    if a == -497:
        line.replace('\n', '').replace('\r', '')
        print("%s=%d" % (line, a))
    line = f.readline()

