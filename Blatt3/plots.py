import matplotlib.pyplot as plt
import numpy as np

N, t, x, v = np.genfromtxt("data/aufgabe1_adams_minus1.csv", unpack=True)
plt.figure()
plt.plot(t, x, linewidth=1.5, label=r"$\alpha=-1$")
plt.xlabel(r"$t$")
plt.ylabel(r'$x$')
plt.grid()
plt.legend(loc='best')
# plt.show()
plt.savefig("plots/aufgabe1_adams_minus1.pdf")
plt.clf()


for alpha in np.arange(0, 3):
    N, t, x, v = np.genfromtxt("data/aufgabe1_adams_" + str(alpha) + ".csv", unpack=True)
    plt.figure()
    plt.plot(t, x, linewidth=1.5, label=r"$\alpha=$" + str(alpha))
    plt.xlabel(r"$t$")
    plt.ylabel(r'$x$')
    plt.grid()
    plt.legend(loc='best')
    # plt.show()
    plt.savefig("plots/aufgabe1_a_" + str(alpha) + ".pdf")
    plt.clf()
    
N, t, x, v = np.genfromtxt("data/aufgabe1_adams_energieerhaltung.csv", unpack=True)
plt.figure()
plt.plot(t, -x**2 + v**2, linewidth=1.5, label=r"$\alpha=0.1$")
plt.xlabel(r"$t$")
plt.ylabel(r'$E$')
plt.grid()
plt.legend(loc='best')
# plt.show()
plt.savefig("plots/aufgabe1_adams_energieerhaltung.pdf")
plt.clf()
