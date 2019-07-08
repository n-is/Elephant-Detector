#!/usr/bin/python3.7

from RedisQueue import RedisQueue
import sys
import struct
import os

# test.py filename
if __name__ == '__main__':    
    if (len(sys.argv)>1):
        filename = sys.argv[1]
    else:
        with open("/home/anmol/minor/mpu/outputs/next_name", "r+") as name_file:
            name = name_file.readline().split()[0]
            name_file.seek(0)
            name_file.write(str(int(name)+1))
            filename = name+".csv"

    f = open("/home/anmol/minor/mpu/outputs/"+filename, "w+")
    f.write("Timestamp, Accel_x, Accel_y, Accel_z\n")

    q = RedisQueue('test')
    print("Starting saving script")
    try:
        while True:
            data = q.get()
            if data.decode('utf-8')=='finished':
                break
            else:
                f.write(data.decode('utf-8'))
    finally:
        f.close()
        os.system("bzip2 /home/anmol/minor/mpu/outputs/{}".format(filename))
