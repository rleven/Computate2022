import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit


def gauss2D(x1, x2, mu1, mu2):
    return 1/np.pi * np.exp(-((x1-mu1)**2 + (x2-mu2)**2)/2)


def gauss1D(x, mu, sigma):
    return 1/np.sqrt(2*np.pi*sigma**2) * np.exp(-(x-mu)**2/(2*sigma**2))

################################################################################################################################
### 2d-Gauß-Verteilung mit Box-Müller-Methode
data = np.genfromtxt("data/BoxMueller.csv", unpack=True)
bin_count = 50

fig, axs = plt.subplots(1, 2, figsize=(10,4))
hist = axs[0].hist2d(data[0], data[1], bins=bin_count)
axs[0].set_xlabel(r'$x_1$')
axs[0].set_ylabel(r'$x_2$')
axs[0].set_title('Gauß-Verteilung mit Box-Müller')
cb = fig.colorbar(hist[3], ax=axs[0])
cb.formatter.set_powerlimits((-3, 3))
cb.minorticks_on()

## Analytische 2d-Gauß-Verteilung
x_min = np.min(data[0])
x_max = np.max(data[0])
x1, x2 = np.meshgrid(np.linspace(x_min, x_max, bin_count), np.linspace(x_min, x_max, bin_count))

axs[1].imshow(gauss2D(x1, x2, 0, 0), extent=[x_min, x_max, x_min, x_max], origin='lower')
axs[1].set_xlabel(r'$x_1$')
axs[1].set_ylabel(r'$x_2$')
axs[1].set_title('Analytische Gauß-Verteilung')
cb = fig.colorbar(hist[3], ax=axs[1])
cb.formatter.set_powerlimits((-3, 3))
cb.minorticks_on()

plt.tight_layout()
plt.savefig("plots/BoxMueller.png")

# plt.show()
plt.close()


################################################################################################################################
### 1d-Gauß-Verteilung mit zentralem Grenzwertsatz
data = np.genfromtxt("data/zentralerGrenzwertsatz.csv", unpack=True)
bin_count = 50

fig, ax = plt.subplots(figsize=(6,4))
bin_heights, bin_borders, _ = ax.hist(data, bins=bin_count, density=True, label="Zentr. Grenzwertsatz")
ax.set_xlabel(r'$x$')
ax.set_ylabel(r'$p(x)$')

## Analytische 1d-Gauß-Verteilung
x_min = np.min(data)
x_max = np.max(data)
x_0 = (x_min + x_max) / 2
x = np.linspace(x_min, x_max, bin_count)
bin_widths = np.diff(bin_borders)
bin_centers = bin_borders[:-1] + bin_widths / 2
params, _ = curve_fit(gauss1D, bin_centers, bin_heights)

names = ['Mittelwert', 'Standardabweichung']
for param, name in zip(params, names):
    print('{0}: {1:.3f}'.format(name, param))

ax.plot(bin_centers, gauss1D(bin_centers, *params), '-', ms=7, label='Analytische Verteilung')
plt.legend(loc='best')

plt.tight_layout()
plt.savefig("plots/zentralerGrenzwertsatz.png")

plt.show()
plt.close()
