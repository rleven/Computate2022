import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib import animation
from random import uniform

#Für Idioten wie mich: m=1 ; o,e=1 ; A=L x L ; rc=L/2 ; h=0.01

#Initialisierung

def randspeed(T):
    temp = np.zeros([2, 16])
    for i in range(16):
        temp[0, i] = np.sqrt(T)*uniform(-1, 1)
        temp[1, i] = np.sqrt(T)*uniform(-1, 1)
    sumx = np.sum(temp[0, :])
    sumy = np.sum(temp[1, :])
    speedx = temp[0, :]/sumx - 1/16
    speedy = temp[1, :]/sumy - 1/16
    speed = np.array([speedx, speedy])
    return speed
    

def posmat(L):
    pos = np.zeros([2, 16])
    i=0
    for n in range(4):
        for m in range(4):
            pos[0, i+m] = 1/8*L*(1+2*n)
        i+=4
    del i
    for i in range(0, 13, 4):
        for m in range(4):
            pos[1, i+m] = 1/8*L*(1+2*m)
    return pos

def motion(pos_t0, speed):

    #pos_t = np.zeros([2, 16])
    for i in range(16):
        pos_t0[:, i] = pos_t0[:, i] + (0.01)*speed[:, i]
    for i in range(16):
        for n in range(16):
            if pos_t0[0, i] == pos_t0[0, n] and pos_t0[1, i] == pos_t0[1, n] and n!=i:
                print("Errör")
    return pos_t0

def boxcheck(L, arr):
    checkhigh = np.amax(arr, axis=1)
    checklow = np.amin(arr, axis=1)
    if (checkhigh.max() > L or checklow.min() < 0):
        print("Out of bounds")
        return False
    else:
        print("Maximum:",checkhigh.max(),"and Minimum:",checklow.min())
        return True

def checkbounce(L, pos, speeda):
    for i in range(16):
        if pos[0, i] > 0 and pos[0, i] < 4 and pos[1, i] > 0 and pos[1, i] < 4:
            switcheroo(2, i, speeda)
            #print("egde1\n")
            continue
        if pos[0, i] < L and pos[0, i] > (L-4) and pos[1, i] < L and pos[1, i] > (L-4):
            switcheroo(2, i, speeda)
            #print("egde2\n")
            continue
        if pos[0, i] > 0 and pos[0, i] < 4:
            switcheroo(0, i, speeda)
            #print(speeda[0, i])
            #print("xpos0\n")
            continue
        if pos[1, i] > 0 and pos[1, i] < 4:
            switcheroo(1, i, speeda)
            #print("ypos0\n")
            continue
        if pos[0, i] < L and pos[0, i] > (L-4):
            switcheroo(0, i, speeda)
            #print("xposL\n")
            continue
        if pos[1, i] < L and pos[1, i] > (L-4):
            switcheroo(1, i, speeda)
            #print("yposL\n")
            continue
    return speeda


def switcheroo(a, b, arr):
    if a!=2:
        arr[a, b] = np.multiply(arr[a, b], -1)
    else:
        arr[:, b] = np.multiply(arr[:, b], -1)
    return arr

pos = posmat(40)
speed = randspeed(1)

#fig = plt.figure()
#ax = fig.add_subplot()

#for i in range(16):
 #   plt.plot(pos[0, i], pos[1, i], '.b')
#points, = ax.plot([], [], 'o')

def moving(n, pos, speed):
    t=0
    while t <= n:
        pos = motion(pos, speed)
        speed = checkbounce(40, pos, speed)
        t+=1
        for i in range(16):
            plt.plot(pos[0, i], pos[1, i], '.b')
        plt.pause(0.02)
    return pos

#ani = animation.FuncAnimation(fig, moving(500,pos=pos, speed=speed), 500)
moving(400, pos, speed)

plt.show()
    