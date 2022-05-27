import os
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation

# Funktion zur Definierung unseres DGL-Systems
def func(xyz, param):   #xyz ist die jeweilige Variable und params ist ein array mit den Vorfaktoren
    velo = np.zeros(3)

    velo[0] = param[0] * (xyz[1] - xyz[0])
    velo[1] = -xyz[0]*xyz[2] + param[2]*xyz[0] - xyz[1]
    velo[2] = xyz[0]*xyz[1] - param[1]*xyz[2]

    return velo

# Hier der bereits bekannte RK4 Algorithmus
def quadruple_kutta(h, t_end, var, param, flname):
    t = 0 
    while t < t_end:
        kutta1 = h * func(var, param)
        kutta2 = h * func(var + kutta1/2, param)
        kutta3 = h * func(var + kutta2/2, param)
        kutta4 = h * func(var + kutta3, param)

        var = var + (kutta1 +2*kutta2 + 2*kutta3 + kutta4)/6
        
        with open(flname, 'a') as fname:
            np.savetxt(fname, np.vstack(var).T)
        t += h

# Die Bahnen 0 bis 3 sind Anfangsbedingungen
path0 = np.array([0,0,0])
path1 = np.array([1,1,1])
path2 = np.array([0.1,0.1,0.1])
path3 = np.array([5,10,15])

parameters0 = np.array([10, 8/3, 20])
parameters1 = np.array([10, 8/3, 28])
t_end = 100
h = 0.005

# Hier wird geschaut, ob die Datei bereits existiert und gelöscht werden muss, da sonst das Programm die neuen Werte einfach dranhängen würde
try:
    os.remove("data/path0.csv")
    os.remove("data/path1.csv")
    os.remove("data/path2.csv")
    os.remove("data/path3.csv")
    os.remove("data/path5.csv")
    os.remove("data/path6.csv")
    os.remove("data/path7.csv")
except:
    FileNotFoundError()

# Ausführung der RK4 für verschiedene Anfangsbedingungen
print("Status: 0 out of 7 complete")
quadruple_kutta(h, t_end, path0, parameters0, "data/path0.csv")
print("Status: 1 out of 7 complete")
quadruple_kutta(h, t_end, path1, parameters0, "data/path1.csv")
print("Status: 2 out of 7 complete")
quadruple_kutta(h, t_end, path2, parameters0, "data/path2.csv")
print("Status: 3 out of 7 complete")
quadruple_kutta(h, t_end, path3, parameters0, "data/path3.csv")
print("Status: 4 out of 7 complete")
quadruple_kutta(h, t_end, path1, parameters1, "data/path4.csv")
print("Status: 5 out of 7 complete")
quadruple_kutta(h, t_end, path2, parameters1, "data/path5.csv")
print("Status: 6 out of 7 complete")
quadruple_kutta(h, t_end, path3, parameters1, "data/path6.csv")
print("Status: complete")