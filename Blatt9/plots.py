import matplotlib.pyplot as plt
import numpy as np
from matplotlib import colors
from mpl_toolkits import mplot3d


# def function(x, y):
#     return x**2 + y**2 + (x**2)*(y**2)

def function(x, y):
    return 1/(1 + (np.exp(-10*(x*y-3)**2))/(x**2 + y**2))


x = np.linspace(-6, 6, 500)
y = np.linspace(-6, 6, 500)
X, Y = np.meshgrid(x, y)
z = function(x, y)
Z = function(X, Y)

rows, cols = (len(y), len(x))
M = [[0 for i in range(cols)] for j in range(rows)]

for i in range(len(x)):
    for j in np.arange(len(y)):
        M[i][j] = function(x[i], y[j])
# M[19][0] = 10**10
# print(Z)


# fig, ax = plt.subplots()
# quad = ax.imshow(M)#, norm=colors.LogNorm())

# cb = fig.colorbar(quad)
# cb.formatter.set_powerlimits((-2, 2))
# cb.minorticks_on()

# plt.show()
# plt.close()


fig = plt.figure()
ax = plt.axes(projection='3d')
ax.scatter(X, Y, Z, s=0.2, alpha=0.6)
# ax.plot_surface(X, Y, Z, cmap ='viridis')


# plt.show()
plt.close()

