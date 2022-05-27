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
ax.set_ylabel(r"x")

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
ax.set_ylabel(r"x")

plt.savefig("plots/fixpoints_cubic.png")

plt.show()
plt.close()



# ### Aufgabe 1 ###
# aufgabe = ['a', 'b', 'c', 'd']
# cmap_aufgabe = ['Reds' , 'Reds', 'Reds', 'RdBu_r']
# L = 21

# for temp_aufgabe, temp_cmap in zip(aufgabe, cmap_aufgabe):
#     phi = np.transpose(np.genfromtxt("data/Potential_" + temp_aufgabe + ".csv", unpack=True))
#     N_steps = int(phi.shape[0] / L)

#     # Die Potentialwerte in ein angemessenes Format, hier 3d-Array, (für die Animation) bringen
#     phi_3d = np.empty(shape=(0, L, L))
#     for i in np.arange(N_steps):
#         temp = phi[L*i:L*i+L, :]
#         phi_3d = np.append(phi_3d, np.transpose(np.atleast_3d(temp)), axis=0)


#     fig, ax = plt.subplots(figsize=(6, 6))
#     quad = ax.imshow(phi_3d[N_steps-1], cmap=temp_cmap)

#     cb = fig.colorbar(quad)
#     cb.formatter.set_powerlimits((0, 0))
#     cb.minorticks_on()

#     ax.set_xlabel(r"Index der Gitterpunkte in x-Richtung")
#     ax.set_ylabel(r"Index der Gitterpunkte in y-Richtung")

#     plt.savefig("plots/Potential_" + temp_aufgabe + ".png")

#     # plt.show()
#     plt.close()



