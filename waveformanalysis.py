#!/usr/bin/python
# -*- coding: utf-8 -*-
# ============================================================
# File: waveformanalysis.py
# Description: plots the seads prototype raw data
#              Usage: waveformanalysis.py [source]
# Created by Henry Crute
# 9/16/14
# ============================================================

import sys
import random
import numpy as np
import matplotlib.pyplot as plt

#creates a bar graph from a list of numbers with a random color
def line_graph(v_list, title):
   ind1 = np.arange(len(v_list))    # the x locations for the groups
   #arange usage can be also arange(start, end, stepsize)

   index = random.randint(0, 4) 
   colorstring = 'kbgry'
   
   p1 = plt.plot(ind1, v_list, color=colorstring[index])
   
   plt.ylabel('Normalized Units')
   plt.title('Plotted ' + title)
   
   plt.grid(True)
   
   #plt.xticks(ind1 + 1)
   #maxY = max(v_list)
   #plt.yticks(np.arange(-maxY/10, maxY + maxY/10, maxY/6))

   #plt.legend((p1[0], p2[0]), ('Voltage', 'Amperage'))

   plt.show()

#checks for arguments, given usage
if len(sys.argv) < 2:
   print "Usage: " + sys.argv[0] + " [source]"
   exit(1)

read = open(sys.argv[1], 'r')
#write = open(sys.argv[2], 'w')

signal = []

for line in read:
   signal.append(float(line) * 0.00000523972)

line_graph(signal, 'Signal')

read.close()
#write.close()

