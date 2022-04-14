import numpy as np
import matplotlib.pyplot as plt

#Aufgabe 1

h, f = np.genfromtxt("data/teil_a1.txt",comments = "#",delimiter = ',', unpack=True)

plt.plot(h, f, '-k', label="Approximation")
plt.hlines(np.cos(np.pi),10**(-3),0.1,colors = 'blue',linestyles = 'dotted', label= 'Wahrer Wert')
plt.xlabel("h")
plt.ylabel("f'(0)")
plt.xscale('log')
plt.legend(loc="best")
plt.savefig("plots/aufgabe1_a1.pdf")
#plt.show()
plt.close()

x, y, del_y = np.genfromtxt("data/teil_a2.txt",comments = "#",delimiter = ',', unpack=True)

plt.plot(x, del_y, '-k', label="Fehler der Approximation")
#plt.hlines(np.cos(np.pi),10**(-3),0.1,colors = 'blue',linestyles = 'dotted', label= 'Wahrer Wert')
plt.xlabel("x")
plt.ylabel("del_y")
plt.legend(loc="best")
plt.savefig("plots/aufgabe1_a2.pdf")
#plt.show()
plt.close()

#Aufgabe 3

N0, f_x0 = np.genfromtxt("data/trapez_a.txt", skip_footer=4, unpack=True)
N1, f_x1 = np.genfromtxt("data/midpoint_a.txt", skip_footer=4, unpack=True)
N2, f_x2 = np.genfromtxt("data/simpson_a.txt", skip_footer=4, unpack=True)
plt.plot(N0, f_x0, '-b', label="Trapezregel")
plt.plot(N1, f_x1, '-g', label="Mittelpunktsregel")
plt.plot(N2, f_x2, '-r', label="Simpsonregel")
plt.xlabel("N=(b-a)/h")
plt.ylabel("Integral value")
plt.legend(loc="best")
plt.tight_layout()
plt.savefig("plots/aufgabe3a.pdf")
plt.close()

del N0, N1, N2, f_x0, f_x1, f_x2

N0, f_x0 = np.genfromtxt("data/trapez_b.txt", skip_footer=4, unpack=True)
N1, f_x1 = np.genfromtxt("data/midpoint_b.txt", skip_footer=4, unpack=True)
N2, f_x2 = np.genfromtxt("data/simpson_b.txt", skip_footer=4, unpack=True)
plt.plot(N0, f_x0, '-b', label="Trapezregel")
plt.plot(N1, f_x1, '-g', label="Mittelpunktsregel")
plt.plot(N2, f_x2, '-r', label="Simpsonregel")
plt.xlabel("N=(b-a)/h")
plt.ylabel("Integral value")
plt.legend(loc="best")
plt.tight_layout()
plt.savefig("plots/aufgabe3b.pdf")
plt.close()