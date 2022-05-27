import matplotlib.pyplot as plt
from matplotlib import colors
import matplotlib.cm as cm
from matplotlib.animation import Animation, FuncAnimation
import numpy as np

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

fig_care, ax_care = plt.subplots(2, 3, figsize=(15, 10))
fig_care.tight_layout()

for i in range(6):
    counter = 0
    schnittpunkte_x = np.array([])
    schnittpunkte_y = np.array([])

    x, y, z = np.genfromtxt('data/path'+str(i+1)+'.csv', unpack=True)
    while counter < len(z)-1:
        if z[counter] > 20 and z[counter+1] < 20: 
            m_x = (z[counter+1] - z[counter])/(x[counter+1] - x[counter])
            m_y = (z[counter+1] - z[counter])/(y[counter+1] - y[counter])

            b_x = z[counter] - m_x * x[counter]
            b_y = z[counter] - m_y * y[counter]

            x_20 = (20 - b_x) / m_x
            y_20 = (20 - b_y) / m_y

            schnittpunkte_x = np.append(schnittpunkte_x, x_20)
            schnittpunkte_y = np.append(schnittpunkte_y, y_20)

        counter  = counter + 1

    colors = cm.rainbow(np.linspace(0,1,len(schnittpunkte_x)))
    if i <=2:
        ax_care[0, i].scatter(schnittpunkte_x, schnittpunkte_y, s=5, c=colors)
    else:
        ax_care[1, i-3].scatter(schnittpunkte_x, schnittpunkte_y, s=5, c=colors)

ax_care[0, 0].set_title(r"Start: (1,1,1), r=20")
ax_care[0, 1].set_title(r"Start: (0.1,0.1,0.1), r=20")
ax_care[0, 2].set_title(r"Start: (5,10,15), r=20")
ax_care[1, 0].set_title(r"Start: (1,1,1), r=28")
ax_care[1, 1].set_title(r"Start: (0.1,0.1,0.1), r=28")
ax_care[1, 2].set_title(r"Start: (5,10,15), r=28")

plt.savefig('plots/pointcare.pdf')
plt.close()