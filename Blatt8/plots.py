import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

### Aufgabe 1b): Plotten der Laufzeiten
t = np.genfromtxt("data/Laufzeiten.csv", unpack=True)
N = t[0,:]

fig, axs = plt.subplots(3, 1, sharex=True, figsize=(5, 3*3))

text = [r"Matrixerzeugung", r"QR-Zerlegung", r"Lösung"]

for i, word in enumerate(text):
    axs[i].plot(N, t[i+1,:], ".", markersize=2)
    axs[i].set_xscale("log")
    axs[i].set_yscale("log")
    axs[i].set_ylabel(word)

fig.supylabel(r"Laufzeiten [s]")
axs[2].set_xlabel(r"$N$")

plt.tight_layout()
plt.savefig("plots/Laufzeiten.png")

# plt.show()
plt.close()


### Aufgabe 1c): Plotten und extrapolieren der Gesamtlaufzeit
def fit_function(x, a, b):
    return a*x**b

t_gesamt = t[1,:] + t[2,:] + t[3,:]

fig, ax = plt.subplots()

ax.plot(N, t_gesamt, ".", markersize=2)
ax.set_ylabel(r"Gesamtlaufzeit [s]")
ax.set_xlabel(r"$N$")

unteresLimit = 200
params, cov = curve_fit(fit_function, N[unteresLimit:], t_gesamt[unteresLimit:])
N_fit = np.linspace(0, 10**6, num=10**6)
ax.plot(N_fit[unteresLimit:], fit_function(N_fit[unteresLimit:], *params))
ax.set_xscale("log")
ax.set_yscale("log")

plt.tight_layout()
plt.savefig("plots/Gesamtlaufzeit.png")

plt.show()
plt.close()

laufzeit_million = fit_function(10**6, *params)
print("Parameter des Fits:", params)
print("Laufzeit für N=10**6:", laufzeit_million, "s,   ", (laufzeit_million/3600)/24, "Tage")
