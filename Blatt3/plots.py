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