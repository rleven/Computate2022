from mimetypes import init
import matplotlib.pyplot as plt
from matplotlib import colors
from matplotlib.animation import Animation, FuncAnimation
import numpy as np


### Aufgabe 1b): Plotten der analytischen Lösung
phi = np.genfromtxt("data/Potential_b_anal.csv", unpack=True)

fig, ax = plt.subplots(figsize=(6, 6))
quad = ax.imshow(phi, cmap='Reds')

cb = fig.colorbar(quad)
cb.formatter.set_powerlimits((0, 0))
cb.minorticks_on()

ax.set_xlabel(r"Index der Gitterpunkte in x-Richtung")
ax.set_ylabel(r"Index der Gitterpunkte in y-Richtung")

plt.savefig("plots/Potential_b_anal.png")

# plt.show()
plt.close()



### Aufgabe 1 ###
aufgabe = ['a', 'b', 'c', 'd']
cmap_aufgabe = ['Reds' , 'Reds', 'Reds', 'RdBu_r']
L = 21

for temp_aufgabe, temp_cmap in zip(aufgabe, cmap_aufgabe):
    phi = np.transpose(np.genfromtxt("data/Potential_" + temp_aufgabe + ".csv", unpack=True))
    N_steps = int(phi.shape[0] / L)

    # Die Potentialwerte in ein angemessenes Format, hier 3d-Array, (für die Animation) bringen
    phi_3d = np.empty(shape=(0, L, L))
    for i in np.arange(N_steps):
        temp = phi[L*i:L*i+L, :]
        phi_3d = np.append(phi_3d, np.transpose(np.atleast_3d(temp)), axis=0)


    fig, ax = plt.subplots(figsize=(6, 6))
    quad = ax.imshow(phi_3d[N_steps-1], cmap=temp_cmap)

    cb = fig.colorbar(quad)
    cb.formatter.set_powerlimits((0, 0))
    cb.minorticks_on()

    ax.set_xlabel(r"Index der Gitterpunkte in x-Richtung")
    ax.set_ylabel(r"Index der Gitterpunkte in y-Richtung")

    plt.savefig("plots/Potential_" + temp_aufgabe + ".png")

    # plt.show()
    plt.close()



# # Animation der Iterationen von Aufgabe 1 (Animation von d) zeigt nichts an. Wissen nicht wieso.)
# #############################################################################################################################################
#     fig, ax = plt.subplots(figsize=(6, 6))
#     quad = ax.imshow(phi_3d[0], cmap=temp_cmap) #,  norm=colors.LogNorm(vmin=10**(-7), vmax=1))
    
#     fig.colorbar(quad)
#     cb.minorticks_on()

#     ax.set_xlabel(r"Index der Gitterpunkte in x-Richtung")
#     ax.set_ylabel(r"Index der Gitterpunkte in y-Richtung")

#     def animation_function(i):
#         phi_step = phi_3d[i]
#         quad.set_array(phi_step)
#         return quad

#     anim = FuncAnimation(fig
#                         ,func=animation_function
#                         ,frames=N_steps
#                         ,interval=5
#                         ,blit=False)

#     plt.show()
#     plt.close()
# #############################################################################################################################################


