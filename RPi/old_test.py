#!/usr/bin/python3.7

from mpu6050 import mpu6050
import sys
import struct
import time
import os
import random

# test.py seconds_to_monitor filename
if __name__ == '__main__':
    mpu = mpu6050(0x68)    

    monitor_time = 10
    filename = str(random.random())[2:9]+".csv"
    
    if (len(sys.argv)>2):
        filename = sys.argv[2]    

    if (len(sys.argv)>1):
        monitor_time = int(sys.argv[1])

    f = open("/home/anmol/minor/mpu/outputs/"+filename, "w+")
    f.write("Timestamp, Accel_x, Accel_y, Accel_z\n")
    #f = open(filename, "wb")    

    start = time.time()
    print("Starting sensor readings at {}".format(start))

    previous = start
    try:
        while True:
            
            current = time.time()
            
            acc = mpu.get_accel_data()
            f.write("{:.3f}, {:.3f}, {:.3f}, {:.3f}\n".format(current-start, acc['x'], acc['y'], acc['z']))
            #f.write(struct.pack("<4f", current, acc['x'], acc['y'], acc['z']))

            if ((current-start)>monitor_time):
                f.close()
                os.system("bzip2 /home/anmol/minor/mpu/outputs/{}".format(filename))
                break
            
            current_sensed = time.time()

            #print("Sensed and written in {}".format(current_sensed-current))
            while (current_sensed-previous)<0.005:
                current_sensed = time.time()
                continue
            previous = current_sensed

    except KeyboardInterrupt:
        f.close()

