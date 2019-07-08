#!/usr/bin/python3.7

import numpy as np
from RedisQueue import RedisQueue
#from collections import deque
import sys
import struct

ENERGY_THRESHOLD = 42
WINDOW = 32
ROLLING_WINDOW = 16

def energy(value_list):
    #e = 0
    #for value in value_list:
    #    e += (value[1]-X_OFFSET)**2 + (value[2]-Y_OFFSET)**2 + (value[3]-Z_OFFSET)**2
    #e /= WINDOW*3    
    return np.sum(value_list**2)

if __name__ == '__main__':    
    q = RedisQueue('test')
    counter = 0
    #acc_list = deque(maxlen=WINDOW)
    acc_list = np.zeros((WINDOW, 3))

    print("Starting detecting script")
    while True:
        try:
            data = q.get()
            if data.decode('utf-8')=='finished':
                break
            else:
                values = data.decode('utf-8')
                acc = [float(value) for value in values[:-1].split(',')[1:]]
                #acc_list.append(acc)
                acc_list[:-1] = acc_list[1:]
                acc_list[-1] = acc
                if (counter % ROLLING_WINDOW == 0):
                    counter = 0
                    e = energy(acc_list)
                    #print(e)
                    if (e > ENERGY_THRESHOLD):
                        print('Threshold passed! ', e)
                else:
                    counter += 1
                #acc_list.popleft()
                
        except Exception as e:
            print(e)
