import matplotlib.pyplot as plt
import numpy as np

h, r1_x, v1_x, r1_y, v1_y, r2_x, v2_x, r2_y, v2_y =np.genfromtxt('data/teil_a_euler.txt' ,unpack=True)

plt.figure()
plt.plot(r1_x, r1_y,"r",linewidth=1,label=r'Trajektorie m$_1$')
plt.plot(r2_x, r2_y,"b",linewidth=1,label=r'Trajektorie m$_2$')
plt.plot(0, 1, "x",linewidth=1,label=r'Startpunkt m$_1$')
plt.plot(0, -0.5, "x",linewidth=1,label=r'Startpunkt m$_2$')
plt.xlabel("x")
plt.ylabel(r'y')
plt.grid()
plt.legend(loc='best')
# plt.show()
plt.savefig("plots/flugweg.pdf")
plt.clf()