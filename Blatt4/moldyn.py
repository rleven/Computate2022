import numpy as np
import matplotlib.pyplot as plt
import tkinter as tk

from random import uniform

''' Initialisierung '''

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

    K = 24 * (r**(-7) - r**(-13))

    normal = (r2-r1)/r

    return normal*K



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



def surrounding(r1, r2):                                        #Gibt die Kraft der zwei Teilchen aufeinander aus, wenn sie näher sind als r_c, sonst einen Nullvektor
    r_c = L/2
    r = np.linalg.norm(r2 - r1)

    if r < r_c:
        return force(r1, r2)
    else:
        return [0, 0]



def darkforce(r1, R, runner):                                   #Zählt die Kraft der umliegenden Teilchen zusammen
    allforce = np.zeros(2)

    for i in range(runner):
        allforce += surrounding(r1, R[:, i])
    for i in range(runner+1, 16, 1):
        allforce += surrounding(r1, R[:, i])
    
    return allforce



def Verlett(h, t, R, V):                                        #Hier wird der Verlett-Algorithmus ausgeführt
    N = int(t/h)
    A = np.zeros([2, 16])
    E_kin = np.zeros(N)
    swp = np.zeros([2, N])

    for i in range(N):
        E_kin[i] = Ekin(V)                                      #Sammelt die kinetische Energie des Systems über den Zeitraum t
        swp[:, i] = SWP_V(V)

        for i in range(16):
            A[:, i] = darkforce(R[:, i], R, i)                  #Berechnet die Beschleunigung von den Teilchen
        
        for i in range(16):
            R[:, i] = R[:, i] + V[:, i]*h + 0.5*A[:, i]*h*h     #Bestimmt die neue Position der Teilchen mit der Geschwindigkeit und der Beschleunigung
        
        for i in range(16):
            V[:, i] = V[:, i] + 0.5*(darkforce(R[:, i], R, i) + A[:, i])*h      #Bestimmt die Geschwindigkeit der Teilchen, nach der Beschleunigung durch das LJ-Potential
        
        teleportation(R)                                        #Funktion für die periodische Randbedingung

        for i in range(16):                                     #Plottet das ganze halbwegs flüssig, weil ich keine Ahnung von pyplot animations habe
            plt.plot(R[0, i], R[1, i], '.r')
            plt.xlim(0, L)
            plt.ylim(0, L)
        plt.pause(0.02)
        plt.clf()
    
    return E_kin[15]


def teleportation(R):
    for i in range(16):
        if R[0, i] > L:
            R[0, i] += -L
        if R[1, i] > L:
            R[1, i] += -L
        if R[0, i] < 0:
            R[0, i] += L
        if R[1, i] < 0:
            R[1, i] += L



L = 20 #Größe der Box
T = 5  #Anfangstemperatur
k_const = 1#1.38e-23 #Boltzmann Konstante

R = Rmat()
V = Vmat()

# print("Positionen:\n",R)
# print("Geschwingikeiten:\n",V)
print("Kinetische Energie:\t", Ekin(V))
#print("Schwerpunktsgeschwindigkeit:\t", SWP_V(V))
# print("Temperatur:\t", hotness(V))
# print("Lennart-Jones Potential, jeweils benachbarter Teilchen:\t", potential(R))
# print("Anziehungskraft der ersten beiden Teilchen:\t", force(R[:, 1], R[:, 0]))
# print("Sind zwei Teilchen sich evtl nahe? ;)\t", surrounding(R[:, 0], R[:, 15]))

B = Verlett(0.01, 2, R, V)

print("Nach dem Spuk:\t", B)

plt.show()