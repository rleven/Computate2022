import numpy as np
import matplotlib.pyplot as plt
import tkinter as tk
import csv
from matplotlib.animation import FuncAnimation
from numpy.random import uniform, seed

''' Initialisierung '''

seed(138)

def Rmat():                                                     #Erzeugt die Startkoordinaten der Teilchen
    pos = np.zeros([2, 16])                                     #Erzeugung einer 2x16 Matrix

    i=0
    for n in range(4):                                          #Berechnet die Positionen
        for m in range(4):
            pos[:, i+m] = [1/8*L*(1+2*n), 1/8*L*(1+2*m)]
        i+=4

    return pos                                                  #Gibt die Startkoordiantenmatrix aus



def Vmat():                                                     #Erzeugt eine zufällige Geschwindigkeitsverteilung der Teilchen
    temp = np.zeros([2, 16])                                    #Erzeugung einer 2x16 matrix

    for i in range(16):                                         #Generiert 32 Zufallszahlen zwischen -1 und 1, abhängig von der Temperatur
        temp[:, i] = [uniform(-1, 1), uniform(-1, 1)]
    
    summe = np.array([np.sum(temp[0, :]), np.sum(temp[1, :])])  #Summiert die Geschwindigkeiten in x und y Richtung
    
    speedx = temp[0, :]/summe[0] - 1/16                         #Korrigiert die Geschwindigkeiten, sodass die Vektoren in der Summe 0 sind
    speedy = temp[1, :]/summe[1] - 1/16
    speed = np.array([speedx, speedy])
    print(speed)

    return speed*np.sqrt(2*k_const*T)                           #Gibt den Geschwindigkeitsvektor aus



''' Äquilibration '''

def Ekin(speed):                                                #Berechnet die kinetische Gesamtenergie aller Teilchen
    E = 0

    for i in range(16):
        E += np.dot(speed[:, i], speed[:, i])
    
    return E/2


  
def SWP_V(speed):                                               #Berechnet die Schwerpunktsgeschwindigkeit
    swp_x = np.sum(speed[0, :])
    swp_y = np.sum(speed[1, :])

    swp = np.array([swp_x, swp_y])

    return swp/16



def hotness(speed):                                             #Berechnet die Temperatur des Systems
    energy = Ekin(speed)
    return energy/k_const



def force(r1, r2):                                              #Berechnet die Teilchen r1 auf Teilchen r2 ausübt
    r = np.linalg.norm(r2 - r1)

    K = 24 * (r**(-7) - 2*r**(-13))

    normal = (r2 - r1)/r

    return np.multiply(K, normal)
    #return np.zeros(2)



def potential(R):                                               #Berechnet die potentielle Energie der Teilchen gemäß der Formel aus b)
    r = np.zeros(16)
    K = np.zeros(16)
    
    for i in range(16):
        j = 0
        success = False
        while not success:
            if i < j - 1:
                while j < 16:
                    r[i] = np.linalg.norm(R[:, i] - R[:, j])
                    K[i] += 4 * (r[i]**(-12) - r[i]**(-6))
                    j+=1
                if j>=16:
                    success = True
            else:
                j+=1
                
    return np.sum(K)



def surrounding(r1, r2):                                      #Gibt die Kraft der zwei Teilchen aufeinander aus, wenn sie näher sind als r_c
    mirror = np.zeros([2, 9])
    distance = np.zeros(9)
    r_c = L/2
    temp = np.zeros(2)
    hor = 3
    ver = 3

    mirror[:, 0] = [-L, L]
    mirror[:, 1] = [0, L]
    mirror[:, 2] = [L, L]
    mirror[:, 3] = [-L, 0]
    mirror[:, 4] = [0, 0]
    mirror[:, 5] = [L, 0]
    mirror[:, 6] = [-L, -L]
    mirror[:, 7] = [0, -L]
    mirror[:, 8] = [L, -L]

    for i in range(9):
        distance[i] = np.linalg.norm(r2 + mirror[:, i] - r1)
    
    min_index = np.argmin(distance)
    r2 = r2 + mirror[:, min_index]

    r = np.linalg.norm(r2 - r1)
    if r <= r_c:
        temp = force(r1, r2)

    return temp
    # if np.abs(r2 - r1)[0] > r_c:
    #     if r2[0] < r1[0]:
    #         r2[0] += L
    #         hor = 0
    #     if r2[0] > r1[0]:
    #         r2[0] -= L
    #         hor = 1
    
    # if np.abs(r2 - r1)[1] > r_c:
    #     if r2[1] < r1[1]:
    #         r2[1] += L
    #         ver = 0
    #     if r2[1] > r1[1]:
    #         r2[1] -= L
    #         ver = 1

    # r = np.linalg.norm(r2 - r1)
    # if r <= r_c:
    #     temp = force(r1, r2)
    
    # if hor == 0:
    #     r2[0] -= L
    # if hor == 1:
    #     r2[0] += L
    # if ver == 0:
    #     r2[1] -= L
    # if ver == 1:
    #     r2[1] += L
    
    # return temp



def darkforce(r1, R, runner):                                   #Zählt die Kraft der umliegenden Teilchen zusammen
    allforce = np.zeros(2)

    for i in range(16):
        if i != runner:
            allforce += surrounding(r1, R[:, i])
    
    return allforce



def Verlet(h, t, R, V):                                         #Hier wird der Verlett-Algorithmus ausgeführt
    N = int(t/h)
    A = np.zeros([2, 16])
    E_kin = np.zeros(N)
    swp = np.zeros([2, N])
    E_pot = np.zeros(N)
    RR = np.zeros([2, 16, N])

    for j in range(16):
        A[:, j] = darkforce(R[:, j], R, j) 

    for i in range(N):
        E_kin[i] = Ekin(V)                                      #Sammelt die kinetische Energie des Systems über den Zeitraum t
        swp[:, i] = SWP_V(V)                                    #Sammelt die Schwerpunktsgeschwindigkeit über den Zeitraum t
        E_pot[i] = potential(R)
        
        for j in range(16):
            R[:, j] = R[:, j] + V[:, j]*h + 0.5*A[:, j]*h*h     #Bestimmt die neue Position der Teilchen mit der Geschwindigkeit und der Beschleunigung
        
        A_old = A

        for j in range(16):
            A[:, j] = darkforce(R[:, j], R, j)

        for j in range(16):
            V[:, j] = V[:, j] + 0.5*(A_old[:, j] + A[:, j])*h      #Bestimmt die Geschwindigkeit der Teilchen, nach der Beschleunigung durch das LJ-Potential
        
        teleportation(R)                                        #Funktion für die periodische Randbedingung

        RR[:, :, i] = R
        # for j in range(16):                                     #Plottet das ganze halbwegs flüssig, weil ich keine Ahnung von pyplot animations habe
        #     plt.plot(R[0, j], R[1, j], '.r')                    #Falls die animation nicht gewünscht ist, einfach diese Schleife und die zwei plt Befehle ausklammern
        #     plt.xlim(0, L)
        #     plt.ylim(0, L)
        # plt.pause(0.02)
        # plt.clf()
    
    return E_kin, swp, E_pot, RR


def teleportation(R):                                           #Teleportiert die Teilchen an die andere Seite der Box
    for i in range(16):
        if R[0, i] > L:
            R[0, i] = 0
        if R[1, i] > L:
            R[1, i] = 0
        if R[0, i] < 0:
            R[0, i] = L
        if R[1, i] < 0:
            R[1, i] = L


''' Hier die Parameter einstellen '''

L = 8 #Größe der Box
T = 62  #Anfangstemperatur
k_const = 1#1.38e-23 #Boltzmann Konstante
t = 20  #Zeit
h = 0.01    #Schrittweite

R = Rmat()  #Anfangszustand-Position
V = Vmat()  #Anfangszustand-Geschwindigkeit

print("Kinetische Energie zu Beginn:\t", Ekin(V)) #Zeigt die Kinetische Energie zu Anfang an

B, sw, P, RR = Verlet(h, t, R, V)  #Hier die Zeit t an der zweiten Stelle ändern, für längere beobachtungen

print("Kinetische Energie am Ende:\t", B[-1])     #Zeigt die Kinetische Energie am Ende der Simulation an

#plt.show()  #abwarten bis der plot fertig ist, versucht man ihn vorzeitig zu schließen, geht er wieder auf!

''' Datensätze werden erstellt '''

zeit = np.linspace(0, int(t/h), len(B))

with open("data/kinetic_energy.csv", "w") as f:
    writer= csv.writer(f)
    writer.writerows(zip(np.round(zeit, 3), B))

swparr = np.zeros(len(B))
for i in range(len(B)):
    swparr[i] = np.linalg.norm(sw[:, i])

with open("data/swp_velocity.csv", "w") as f:
    writer= csv.writer(f)
    writer.writerows(zip(np.round(zeit, 3), swparr))

with open("data/temperature.csv", "w") as f:
    writer= csv.writer(f)
    writer.writerows(zip(np.round(zeit, 3), B/k_const))

with open("data/potential_energy.csv", "w") as f:
    writer= csv.writer(f)
    writer.writerows(zip(np.round(zeit, 3), P))

''' Plots werden erstellt '''

plt.plot(zeit, B, '-b')
plt.xlabel("Zeitschritte h")
plt.ylabel("Kinetische Energie in ε")

plt.savefig("plots/kinetic_energy.pdf")
plt.close()

plt.plot(zeit, swparr, '-b')
plt.xlabel("Zeitschritte h")
plt.ylabel("Schwerpunktsgeschwindigkeit")

plt.savefig("plots/swp_velocity.pdf")
plt.close()

plt.plot(zeit, B/k_const, '-b')
plt.xlabel("Zeitschritte h")
plt.ylabel("Temperatur T")

plt.savefig("plots/temperature.pdf")
plt.close()

plt.plot(zeit, P, '-b')
plt.xlabel("Zeitschritte h")
plt.ylabel("Potentielle Energie")

plt.savefig("plots/potential_energy.pdf")
plt.close()

fig, ax = plt.subplots()
line, = ax.plot([], [], linestyle="", marker='o', markersize=4)
ax.set_xlim(0, L)
ax.set_ylim(0, L)
ax.grid()

def animation_func(i):
    x = RR[0, :, i]
    y = RR[1, :, i]
    line.set_data(x, y)
    return line

animation = FuncAnimation(fig, func=animation_func, frames=int(t/h), interval=1, blit=False)
plt.show()