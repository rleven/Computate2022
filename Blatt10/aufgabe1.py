import numpy as np
import matplotlib.pyplot as plt
from numpy.random import MT19937

''' Aufgabenteil a) '''

def pseudo(r0, a, c, m, N):
    r = np.zeros(N)
    r[0] = r0

    for i in range(N-1):
        r[i+1] = np.mod((a*r[i] + c), m)

    f = r/m

    return f


''' Aufgabenteil b)'''

# Teil (i)
r0 = int(1234)
a = int(20)
c = int(120)
m = int(6075)
N = int(1e5)

randlist = pseudo(r0, a, c, m, N)

MT19937(1234)

rg = np.random.uniform(size=N)

plt.hist(randlist, bins=20, color="orange", alpha=0.7, label="Unser")
plt.hist(rg, bins=20, color="b", alpha=0.5, label="MT19937")
plt.xlabel("Zufallswerte der Generatoren mit Startwerten (i)")
plt.ylabel("Häufigkeit in 20 Bins")
plt.ylim(top=6500)
plt.legend(loc="upper center")
plt.savefig('plots/a1b1.pdf')
plt.close()


# Teil (ii)
r0 = int(123456789)
a = int(65539)
c = int(0)
m = int(2147483648)

randlist = pseudo(r0, a, c, m, N)

MT19937(123456789)

rg = np.random.uniform(size=N)

plt.hist(randlist, bins=20, color="orange", alpha=0.7, label="Unser")
plt.hist(rg, bins=20, color="b", alpha=0.5, label="MT19937")
plt.xlabel("Zufallswerte der Generatoren mit Startwerten (ii)")
plt.ylabel("Häufigkeit in 20 Bins")
plt.ylim(top=6500)
plt.legend(loc="upper center")
plt.savefig('plots/a1b2.pdf')
plt.close()