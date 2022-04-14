import numpy as np
import matplotlib.pyplot as plt

########################################################################################################################################################################
### Aufgabe 1a)
h, f = np.genfromtxt("data/teil_a1.txt", comments = "#", delimiter = ',', unpack=True)

plt.plot(h, f, '-k', label="Approximation")
plt.hlines(np.cos(2), 10**(-3), 0.1, colors = 'blue', linestyles = 'dotted', label= 'Wahrer Wert')
plt.xlabel("h")
plt.ylabel(r"f'$_{\mathrm{1,Zweipunkt}}(\pi)$")
plt.xscale('log')
plt.legend(loc="best")
plt.tight_layout()
plt.savefig("plots/aufgabe1_a1.pdf")
# plt.show()
plt.close()

x, y, del_y = np.genfromtxt("data/teil_a2.txt", comments = "#", delimiter = ',', unpack=True)

plt.plot(x, del_y, '-k', label="Fehler der Approximation")
plt.xlabel(r"$x$")
plt.ylabel(r"$\Delta$f'$_{\mathrm{1,Zweipunkt}}(x)$")
plt.legend(loc="best")
plt.tight_layout()
plt.savefig("plots/aufgabe1_a2.pdf")
# plt.show()
plt.close()


########################################################################################################################################################################
### Aufgabe 1b)
h, f = np.genfromtxt("data/teil_b1.txt", comments = "#", delimiter = ',', unpack=True)

plt.plot(h, f, '-k', label="Approximation")
plt.hlines(-np.sin(np.pi/2), 10**(-3), 1, colors = 'blue', linestyles = 'dotted', label= 'Wahrer Wert')
plt.xlabel("h")
plt.ylabel(r"f''$_{\mathrm{1,Zweipunkt}}(\pi/2)$")
plt.xscale('log')
plt.legend(loc="best")
plt.tight_layout()
plt.savefig("plots/aufgabe1_b1.pdf")
# plt.show()
plt.close()

x, y, del_y = np.genfromtxt("data/teil_b2.txt", comments = "#", delimiter = ',', unpack=True)

plt.plot(x, del_y, '-k', label="Fehler der Approximation")
plt.xlabel(r"$x$")
plt.ylabel(r"$\Delta$f''$_{\mathrm{1,Zweipunkt}}(x)$")
plt.ticklabel_format(scilimits=(0,0))
plt.legend(loc="best")
plt.tight_layout()
plt.savefig("plots/aufgabe1_b2.pdf")
# plt.show()
plt.close()


########################################################################################################################################################################
### Aufgabe 1c)
h, f = np.genfromtxt("data/teil_c1.txt", comments = "#", delimiter = ',', unpack=True)

plt.plot(h, f, '-k', label="Approximation")
plt.hlines(np.cos(np.pi), 10**(-5), 1, colors = 'blue', linestyles = 'dotted', label= 'Wahrer Wert')
plt.xlabel("h")
plt.ylabel(r"f'$_{\mathrm{1,Vierpunkt}}(\pi)$")
plt.xscale('log')
plt.legend(loc="best")
plt.tight_layout()
plt.savefig("plots/aufgabe1_c1.pdf")
# plt.show()
plt.close()

x, y, del_y = np.genfromtxt("data/teil_c2.txt", comments = "#", delimiter = ',', unpack=True)

plt.plot(x, del_y, '-k', label="Fehler der Approximation")
plt.xlabel(r"$x$")
plt.ylabel(r"$\Delta$f'$_{\mathrm{1,Vierpunkt}}(x)$")
plt.ticklabel_format(scilimits=(0,0))
plt.legend(loc="best")
plt.tight_layout()
plt.savefig("plots/aufgabe1_c2.pdf")
# plt.show()
plt.close()

########################################################################################################################################################################
### Aufgabe 1d)
h, f = np.genfromtxt("data/teil_d1.txt", comments = "#", delimiter = ',', unpack=True)

plt.plot(h, f, '-k', label="Approximation")
plt.hlines(np.sin(np.pi/2), 10**(-5), 1, colors = 'blue', linestyles = 'dotted', label= 'Wahrer Wert')
plt.xlabel("h")
plt.ylabel(r"f'$_{\mathrm{2,Zweipunkt}}(\pi/2)$")
plt.xscale('log')
plt.legend(loc="best")
plt.tight_layout()
plt.savefig("plots/aufgabe1_d1.pdf")
plt.show()
plt.close()

x, y, del_y = np.genfromtxt("data/teil_d2.txt", comments = "#", delimiter = ',', unpack=True)

plt.plot(x, del_y, '-k', label="Fehler der Approximation")
plt.xlabel(r"$x$")
plt.ylabel(r"$\Delta$f'$_{\mathrm{2,Zweipunkt}}(x)$")
plt.ticklabel_format(scilimits=(0,0))
plt.legend(loc="best")
plt.tight_layout()
plt.savefig("plots/aufgabe1_d2.pdf")
plt.show()
plt.close()

h, f = np.genfromtxt("data/teil_d3.txt", comments = "#", delimiter = ',', unpack=True)

plt.plot(h, f, '-k', label="Approximation")
plt.hlines(np.sin(np.pi/2), 10**(-5), 1, colors = 'blue', linestyles = 'dotted', label= 'Wahrer Wert')
plt.xlabel("h")
plt.ylabel(r"f'$_{\mathrm{2,Vierpunkt}}(\pi/2)$")
plt.xscale('log')
plt.legend(loc="best")
plt.tight_layout()
plt.savefig("plots/aufgabe1_d3.pdf")
plt.show()
plt.close()

x, y, del_y = np.genfromtxt("data/teil_d4.txt", comments = "#", delimiter = ',', unpack=True)

plt.plot(x, del_y, '-k', label="Fehler der Approximation")
plt.xlabel(r"$x$")
plt.ylabel(r"$\Delta$f'$_{\mathrm{2,Vierpunkt}}(x)$")
plt.ticklabel_format(scilimits=(0,0))
plt.legend(loc="best")
plt.tight_layout()
plt.savefig("plots/aufgabe1_d4.pdf")
plt.show()
plt.close()