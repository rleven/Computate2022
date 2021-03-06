import matplotlib.pyplot as plt
from matplotlib import colors
import matplotlib.cm as cm
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

#plt.show()
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

#plt.show()
plt.close()

### Aufgabe 2: Plotten der verschiedenen Darstellungen der DGLs

### XY-Darstellung
fig, ax = plt.subplots(2, 3, figsize=(15, 10))
fig.tight_layout()

ax[0, 0].plot(np.genfromtxt('data/path1.csv', usecols=0, unpack=True), np.genfromtxt('data/path1.csv', usecols=1, unpack=True))
ax[0, 0].set_title(r"Start: (1,1,1), r=20")

ax[0, 1].plot(np.genfromtxt('data/path2.csv', usecols=0, unpack=True), np.genfromtxt('data/path2.csv', usecols=1, unpack=True))
ax[0, 1].set_title(r"Start: (0.1,0.1,0.1), r=20")

ax[0, 2].plot(np.genfromtxt('data/path3.csv', usecols=0, unpack=True), np.genfromtxt('data/path3.csv', usecols=1, unpack=True))
ax[0, 2].set_title(r"Start: (5,10,15), r=20")

ax[1, 0].plot(np.genfromtxt('data/path4.csv', usecols=0, unpack=True), np.genfromtxt('data/path4.csv', usecols=1, unpack=True))
ax[1, 0].set_title(r"Start: (1,1,1), r=28")

ax[1, 1].plot(np.genfromtxt('data/path5.csv', usecols=0, unpack=True), np.genfromtxt('data/path5.csv', usecols=1, unpack=True))
ax[1, 1].set_title(r"Start: (0.1,0.1,0.1), r=28")

ax[1, 2].plot(np.genfromtxt('data/path6.csv', usecols=0, unpack=True), np.genfromtxt('data/path6.csv', usecols=1, unpack=True))
ax[1, 2].set_title(r"Start: (5,10,15), r=28")

plt.savefig('plots/2Dlorenz.pdf')
plt.close()

### 3D-Darstellung
fig3d = plt.figure(figsize=(15, 10))
fig3d.tight_layout()

ax3d0 = fig3d.add_subplot(2, 3, 1, projection='3d')
ax3d0.plot(np.genfromtxt('data/path1.csv', usecols=0, unpack=True), np.genfromtxt('data/path1.csv', usecols=1, unpack=True), np.genfromtxt('data/path1.csv', usecols=2, unpack=True))
ax3d0.set_title(r"Start: (1,1,1), r=20")

ax3d1 = fig3d.add_subplot(2, 3 , 2, projection='3d')
ax3d1.plot(np.genfromtxt('data/path2.csv', usecols=0, unpack=True), np.genfromtxt('data/path2.csv', usecols=1, unpack=True), np.genfromtxt('data/path2.csv', usecols=2, unpack=True))
ax3d1.set_title(r"Start: (0.1,0.1,0.1), r=20")

ax3d2 = fig3d.add_subplot(2, 3, 3, projection='3d')
ax3d2.plot(np.genfromtxt('data/path3.csv', usecols=0, unpack=True), np.genfromtxt('data/path3.csv', usecols=1, unpack=True), np.genfromtxt('data/path3.csv', usecols=2, unpack=True))
ax3d2.set_title(r"Start: (5,10,15), r=20")

ax3d3 = fig3d.add_subplot(2, 3, 4, projection='3d')
ax3d3.plot(np.genfromtxt('data/path4.csv', usecols=0, unpack=True), np.genfromtxt('data/path4.csv', usecols=1, unpack=True), np.genfromtxt('data/path4.csv', usecols=2, unpack=True))
ax3d3.set_title(r"Start: (1,1,1), r=28")

ax3d4 = fig3d.add_subplot(2, 3 , 5, projection='3d')
ax3d4.plot(np.genfromtxt('data/path5.csv', usecols=0, unpack=True), np.genfromtxt('data/path5.csv', usecols=1, unpack=True), np.genfromtxt('data/path5.csv', usecols=2, unpack=True))
ax3d4.set_title(r"Start: (0.1,0.1,0.1), r=28")

ax3d5 = fig3d.add_subplot(2, 3, 6, projection='3d')
ax3d5.plot(np.genfromtxt('data/path6.csv', usecols=0, unpack=True), np.genfromtxt('data/path6.csv', usecols=1, unpack=True), np.genfromtxt('data/path6.csv', usecols=2, unpack=True))
ax3d5.set_title(r"Start: (5,10,15), r=28")

plt.savefig('plots/3Dlorenz.pdf')
plt.close()

### Pointcare-Schnitte
fig_care, ax_care = plt.subplots(2, 3, figsize=(15, 10))
fig_care.tight_layout()

for i in range(6):
    count = 0
    crosspoints_x = np.array([])
    crosspoints_y = np.array([])

    x, y, z = np.genfromtxt('data/path'+str(i+1)+'.csv', unpack=True)
    while count < len(z)-1:
        if z[count] > 20 and z[count+1] < 20: 
            m_x = (z[count+1] - z[count])/(x[count+1] - x[count])
            m_y = (z[count+1] - z[count])/(y[count+1] - y[count])

            b_x = z[count] - m_x * x[count]
            b_y = z[count] - m_y * y[count]

            x_20 = (20 - b_x) / m_x
            y_20 = (20 - b_y) / m_y

            crosspoints_x = np.append(crosspoints_x, x_20)
            crosspoints_y = np.append(crosspoints_y, y_20)

        count  = count + 1

    colors = cm.rainbow(np.linspace(0,1,len(crosspoints_x)))
    if i <=2:
        ax_care[0, i].scatter(crosspoints_x, crosspoints_y, s=5, c=colors)
    else:
        ax_care[1, i-3].scatter(crosspoints_x, crosspoints_y, s=5, c=colors)

ax_care[0, 0].set_title(r"Start: (1,1,1), r=20")
ax_care[0, 1].set_title(r"Start: (0.1,0.1,0.1), r=20")
ax_care[0, 2].set_title(r"Start: (5,10,15), r=20")
ax_care[1, 0].set_title(r"Start: (1,1,1), r=28")
ax_care[1, 1].set_title(r"Start: (0.1,0.1,0.1), r=28")
ax_care[1, 2].set_title(r"Start: (5,10,15), r=28")

plt.savefig('plots/pointcare.pdf')
plt.close()