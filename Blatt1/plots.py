import numpy as np
import matplotlib.pyplot as plt


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
plt.show()
plt.close()