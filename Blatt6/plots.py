from mimetypes import init
import matplotlib.pyplot as plt
from matplotlib import colors
from matplotlib.animation import Animation, FuncAnimation
import numpy as np


### Aufgabe 1: Plotten des Birkfukationsdiagrams für die logistische Abbildung
data = np.transpose(np.genfromtxt("data/fixpoints_logistic.csv", unpack=True))
r = data[:,0]
x_fixpoints = np.ma.masked_where(data[:,1:]==0, data[:,1:])                 # um die nullen in jeder Zeile nicht mitzuplotten

fig, ax = plt.subplots()
ax.plot(r, x_fixpoints, 'k.', markersize=0.05)

ax.set_xlabel(r"r")
ax.set_ylabel(r"x_n")

plt.savefig("plots/fixpoints_logistic.png")

plt.show()
plt.close()


### Aufgabe 1: Plotten des Birkfukationsdiagrams für die kubische Abbildung
data = np.transpose(np.genfromtxt("data/fixpoints_cubic.csv", unpack=True))
r = data[:,0]
x_fixpoints = np.ma.masked_where(data[:,1:]==0, data[:,1:])                 # um die nullen in jeder Zeile nicht mitzuplotten

fig, ax = plt.subplots()
ax.plot(r, x_fixpoints, 'k.', markersize=0.05)

ax.set_xlabel(r"r")
ax.set_ylabel(r"x_n")

plt.savefig("plots/fixpoints_cubic.png")

plt.show()
plt.close()
