#!/usr/bin/python3.7

from mpu6050 import mpu6050
from RedisQueue import RedisQueue
import sys
import struct
import time
import os

# test.py seconds_to_monitor time_duration
if __name__ == '__main__':
    mpu = mpu6050(0x68)    
    q = RedisQueue('test')

    monitor_time = 10
    time_duration = 0.0025 # in sec

    if (len(sys.argv)>1):
        monitor_time = int(sys.argv[1])

    if (len(sys.argv)>1):
        time_duration = float(sys.argv[2])

    start = time.time()
    print("Starting sensor readings at {}".format(start))

    previous = start
    try:
        while True:
            
            current = time.time()
            
            acc = mpu.get_accel_data()
            q.put("{:.4f}, {:.3f}, {:.3f}, {:.3f}\n".format(current-start, acc['x'], acc['y'], acc['z']))

            if ((current-start)>monitor_time):
                q.put('finished')
                break
            
            current_sensed = time.time()

            #print("Sensed and written in {}".format(current_sensed-current))
            while (current_sensed-previous)<time_duration:
                current_sensed = time.time()
                continue
            previous = current_sensed

    except KeyboardInterrupt:
        pass
