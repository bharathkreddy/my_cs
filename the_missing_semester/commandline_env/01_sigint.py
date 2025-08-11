#! /usr/bin/env python

import signal, time

def handler(signum, time):
    print("\nSIGINT detected, but im not stopping.")

signal.signal(signal.SIGINT, handler)

i=0
print("starting the program, ^+c : SIGINT and ^+\ : to kill the program.")
while True:
    time.sleep(.1)
    print(f"\r{i}",end="") 
    #\r moves the cursor to the start of the line again after priting.
    i += 1

# use ^ \ to kill the program , 
# ^ c is going to send sigint but program is not going to stop for it.