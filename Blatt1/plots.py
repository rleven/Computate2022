import numpy as np
import matplotlib.pyplot as plt

x2 = np.genfromtxt("build/teil_a.txt", unpack=True, usecols=0, delimiter=",")
y2 = np.genfromtxt("build/teil_a.txt", unpack=True, usecols=1, delimiter=",")

plt.plot(x2, y2, "-k", label="Teil 1")
plt.legend(loc="best")
plt.show()