import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from matplotlib.animation import FuncAnimation

''' Implementierung der FTCS-Funktion '''

#ab hier Aufgabenteil a)

def FTCS(val, taim, taim_step):
    N = int(taim/taim_step) #Anzanhl an Schritten werden bestimmt
    
    L = np.zeros([N, 101]) #Array mit 100 Werten je Zeitschritt
    L[0, :] = val #Befüllung der initialen Werte 

    vorfaktor = taim_step/(0.01**2) #Vorfaktor des FTCS
    print("Der Vorfaktor ist:\t", vorfaktor)

    for n in range(N-1):                                                        #hier ist der eigentliche FTCS-Algorithmus geschrieben
        L[n+1, 0] = L[n, 0] + vorfaktor*(-1*L[n, 0] + L[n, 1])

        L[n+1, -1] = L[n, -1] + vorfaktor*(L[n, -2] - 1*L[n, -1])

        for j in range(1, 100):
            L[n+1, j] = L[n, j] + vorfaktor*(L[n, j-1] - 2*L[n, j] + L[n, j+1])

    return L

def anime(RB, title):                                                                  #eine Funktion für die Animationen
    fig, ax = plt.subplots()
    line, = ax.plot([], [], linestyle="", marker='.', markersize=4)
    ax.set_title(title)
    ax.set_xlim(-0.5, 1.5)
    ax.set_ylim(0, int(t/t_step)+1)
    ax.set_xlabel("Werte der Punkte u")
    ax.set_ylabel("Zeitschritte")


    ymask = np.arange(int(t/t_step))

    def animation_func(i):
        x = RB[i, :]
        y = ymask[i]
        line.set_data(x, y)
        return line

    animation = FuncAnimation(fig, func=animation_func, frames=int(t/t_step), interval=1, blit=False)
    plt.show()

print("Welcher Aufgabenteil soll ausgeführt werden? Wahl aus a, b oder c!")

abfrage = input()


if abfrage == "a":

    init_value = np.full(101, 1.0)
    t = 0.1
    t_step = 0.00004

    RR = FTCS(init_value, t, t_step)
    np.savetxt('data/diffusa.txt', RR)
    print("Saved a)")
    anime(RR, "u(x, 0) = 1")
#bis hierhin Aufgabenteil a)

#ab hier Aufgabenteil b)

if abfrage == "b":

    init_value = np.zeros(101)
    init_value[50] = 1.0
    t = 0.2

    stabilkrit = 0.5*0.01**2
    print("Stabilitätskriterium liegt bei t_step <", stabilkrit)

    t_step = 4e-5

    RR = FTCS(init_value, t, t_step)
    np.savetxt('data/diffusb.txt', RR)
    print("Saved b)")
    anime(RR, "Dirac im Stabilitätskriterium")
    plt.close()

    plt.plot(np.linspace(1, len(RR[:, 50]), len(RR[:, 50])), RR[:, 50], '-b', label="∆t = 4e-5")
    plt.xlabel("Zeitschritte")
    plt.ylabel("Wert des δ(x - 0.5)")
    plt.title("Verlauf des 50sten u's bei Dirac Bedingung")
    plt.legend(loc="best")
    plt.savefig("plots/diracminor.pdf")

    t_step = 6e-5

    RR = FTCS(init_value, t, t_step)
    plt.close()

    plt.plot(np.linspace(1, len(RR[:, 50]), len(RR[:, 50])), RR[:, 50], '-b', label="∆t = 6e-5")
    plt.xlabel("Zeitschritte")
    plt.ylabel("Wert des δ(x - 0.5)")
    plt.title("Verlauf des 50sten u's bei Dirac Bedingung")
    plt.legend(loc="best")
    plt.savefig("plots/diracmaxi.pdf")
    plt.close()

    print("Das hier drüber ist kein Error, sondern was wir für die nicht Einhaltung des Stabilitätskriteriums erwarten!")

#bis hierhin Aufgabenteil b)

#ab hier Aufgabenteil c)

if abfrage == "c":

    ''' Heaviside '''
    init_value = np.zeros(101)
    init_value[50:] = 1.0
    t = 0.2

    stabilkrit = 0.5*0.01**2
    print("Stabilitätskriterium liegt bei t_step <", stabilkrit)

    t_step = 4e-5

    RR = FTCS(init_value, t, t_step)
    np.savetxt('data/diffusheavi.txt', RR)
    print("Saved Heavi")
    anime(RR, "Heaviside")
    plt.close()

    ''' Dirac-Kamm '''
    init_value = np.zeros(101)
    init_value[10] = 1/9
    init_value[20] = 1/9
    init_value[30] = 1/9
    init_value[40] = 1/9
    init_value[50] = 1/9
    init_value[60] = 1/9
    init_value[70] = 1/9
    init_value[80] = 1/9
    init_value[90] = 1/9
    t = 0.2

    t_step = 4e-5

    RR = FTCS(init_value, t, t_step)
    np.savetxt('data/diffuscomb.txt', RR)
    print("Saved Kamm")
    anime(RR, "Dirac-Kamm")
    plt.close()   

if abfrage != "a" and abfrage != "b" and abfrage != "c":
    print("Falsche Eingabe!")