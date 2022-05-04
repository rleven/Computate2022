import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

#Plot für b)
x, y = np.genfromtxt("data/distance.csv", unpack=True)

plt.plot(x, y, label="Werte")
print("Welcher Index hat den max Wert? Dieser: ", np.where(y == np.max(y)))#damit ich weiß welcher index der richtige ist
print("Das ist besagter Wert: ",x[np.where(y == np.max(y))])
plt.xlabel("Winkel [rad]")
plt.ylabel("Flugweite [m]")
plt.legend(loc="best")
plt.tight_layout()
#plt.show()
plt.savefig("plots/distance.pdf")
plt.close()

print("=============")

#Plot für c)
t, x_value , unnötig_für_aufgabe1, unnötig_für_aufgabe2 = np.genfromtxt("data/trajectory.csv", unpack=True)

plt.plot(t, x_value, '.b', label="Trajektorien")
plt.xlabel("Zeit [s]")
plt.ylabel("X Wert der Trajektorie [m]")
plt.legend(loc="best")
plt.title("Trajektorien für fünf verschiedene Windstärken")
plt.tight_layout()
plt.savefig("plots/trajectory.pdf")
plt.close()

#Plot für d)
a = np.genfromtxt("data/goalangle.csv", unpack=True)
b = a*180/np.pi
print("Minimum: ", np.min(b), " und Maximum: ", np.max(b))
for i in range(len(b)-1):
    if np.abs(b[i]-b[i+1]) > 1:
        print("Und diese Grenzen: ", b[i], "    ", b[i+1])

plt.plot(b, a, '.b', label="Winkel bei Treffer")
plt.xlabel("Winkel [°]")
plt.ylabel("Winkel [rad]")
plt.legend(loc="best")
plt.tight_layout()
plt.savefig("plots/goalangle.pdf")
plt.close()

del x, y, t, a, b, x_value, unnötig_für_aufgabe1, unnötig_für_aufgabe2


N, t, x, v = np.genfromtxt("data/aufgabe1_adams_minus1.csv", unpack=True)
plt.figure()
plt.plot(t, x, linewidth=1.5, label=r"$\alpha=-1$")
plt.xlabel(r"$t$")
plt.ylabel(r'$x$')
plt.grid()
plt.legend(loc='best')
# plt.show()
plt.savefig("plots/aufgabe1_adams_minus1.pdf")
plt.close()

alpha_list = [0, 2, 3]
for alpha in alpha_list:
    N, t, x, v = np.genfromtxt("data/aufgabe1_adams_" + str(alpha) + ".csv", unpack=True)
    plt.figure()
    plt.plot(t, x, linewidth=1.5, label=r"$\alpha=$" + str(alpha))
    plt.xlabel(r"$t$")
    plt.ylabel(r'$x$')
    plt.grid()
    plt.legend(loc='best')
    plt.show()
    plt.savefig("plots/aufgabe1_a_" + str(alpha) + ".pdf")
    plt.close()
    
N, t, x, v = np.genfromtxt("data/aufgabe1_adams_energieerhaltung.csv", unpack=True)
plt.figure()
plt.plot(t, x**2 + v**2, linewidth=1.5, label=r"$\alpha=0.1$")
plt.xlabel(r"$t$")
plt.ylabel(r'$E$')
plt.grid()
plt.legend(loc='best')
# plt.show()
plt.savefig("plots/aufgabe1_adams_energieerhaltung.pdf")
plt.close()
