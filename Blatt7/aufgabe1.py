import numpy as np
import matplotlib.pyplot as plt

# Berechnung der Abbruchbedingung
def off(A):
    ol_reliable = 0
    for i in range(4):
        for j in range(4):
            if i != j:
                ol_reliable = ol_reliable + A[i, j]*A[i, j]
            else:
                continue
    return ol_reliable

# Berechnung der Position des Maximalwertes ohne Diagonale
def apq(A):
    triag = np.abs(np.triu(A, k=1))
    return np.unravel_index(np.argmax(triag), triag.shape)

# Berechnung der Komponenten der Orthogonalmatrix P
def calc(A):
    r = apq(A)
    i = r[0]
    j = r[1]

    theta = (A[j, j] - A[i, i])/(2*A[i, j])
    t = np.sign(theta)/(np.abs(theta) + np.sqrt(theta**2 + 1))
    c = 1/np.sqrt(1 + t**2)
    s = t*c

    return theta, t, c, s, r

# Berechnung der Ähnlichkeitstransformation
def newA(A):
    P = np.eye(4)

    theta, t, c, s, r = calc(A)
    P[r[0], r[0]] = c
    P[r[0], r[1]] = s
    P[r[1], r[0]] = -s
    P[r[1], r[1]] = c

    return np.multiply(np.multiply(P.T, A), P)

# Berechnung der Eigenwerte mittels jacobi-Rotation
def jacobi(A, eps):
    counter = 0
    while True:
        A = newA(A)
        counter += 1
        if off(A) < eps:
            break
    return A, counter

mat = np.matrix([[1, -2, 2, 4],[-2, 3, -1, 0],[2, -1, 6, 3],[4, 0, 3, 5]])  #Anfangsmatrix
eps = 1e-6  #Abbruchbedingung

print("Anfangsmatrix:\n",mat)

a, d = jacobi(mat, eps)
print("Matrix nach",d,"Schritten:\n",a)

eigen = np.array([a[0, 0], a[1, 1], a[2, 2], a[3, 3]])
print("Die Eigenwerte nach Jacobi sind:", eigen)

w, v = np.linalg.eig(a)
print("Die Eigenwerte nach numpy.linalg.eig sind:", w)
