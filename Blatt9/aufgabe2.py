import numpy as np
import matplotlib.pyplot as plt

# Zuteilung der zufälligen Positionen
def randpos(N):
    return np.random.uniform(-5, 5, (2, N))

# Zuteilung der zufälligen Geschwindigkeiten
def randvel(N):
    return np.random.uniform(-1, 1, (2, N))

def fun(pos):
    return (pos[0] - 1.9)**2 + (pos[1] - 2.1)**2 + 2*np.cos(4*pos[0] + 2.8) + 3*np.sin(2*pos[1] + 0.6)

# Bestimmung des Minimums in der Funktion
def fkt(pos):
    return np.min((pos[0,:] - 1.9)**2 + (pos[1,:] - 2.1)**2 + 2*np.cos(4*pos[0,:] + 2.8) + 3*np.sin(2*pos[1,:] + 0.6))

# Ermittlung des global besten Minimums
def global_best(pos):
    temp = (pos[0,:] - 1.9)**2 + (pos[1,:] - 2.1)**2 + 2*np.cos(4*pos[0,:] + 2.8) + 3*np.sin(2*pos[1,:] + 0.6)
    return np.argmin(temp)

# Ermittlung des individuell besten Minimums
def local_best(loc, pos):
    pos_temp = (pos[0,:] - 1.9)**2 + (pos[1,:] - 2.1)**2 + 2*np.cos(4*pos[0,:] + 2.8) + 3*np.sin(2*pos[1,:] + 0.6)
    loc_temp = (loc[0,:] - 1.9)**2 + (loc[1,:] - 2.1)**2 + 2*np.cos(4*loc[0,:] + 2.8) + 3*np.sin(2*loc[1,:] + 0.6)

    for i in range(len(loc_temp)):
        if pos_temp[i] < loc_temp[i]:
            loc[:, i] = pos[:, i]

    return loc

# Definitionen
w = 0.8
c = 0.1
N = 10

# Love Death Robots S3 Ep6
def swarm(pos, vel, cycles):

    ultpos = np.zeros([2, N, cycles+1])
    ultvel = np.zeros([2, N, cycles+1])

    ultglobest = np.zeros(cycles+1)
    ultlocbest = np.zeros([N, cycles+1])

    loc_best = pos.copy()

    j = 0
    while j <= cycles:

        loc_best = local_best(loc_best, pos)
        glo_best = pos[:, global_best(pos)]

        for i in range(N):    
            pos[:, i] = pos[:, i] + vel[:, i]
            vel[:, i] = w*vel[:, i] + c*np.random.random()*(loc_best[:, i] - pos[:, i]) + c*np.random.random()*(glo_best - pos[:, i])
            
        ultpos[:, :, j] = pos
        ultvel[:, :, j] = vel

        ultglobest[j] = fun(glo_best)
        for k in range(N):
            ultlocbest[k, j] = fun(loc_best[:, k])

        j+=1
    return ultpos, ultvel, ultglobest, ultlocbest

''' Ausführung des Aufgabenteils a) '''

pos = randpos(N)
vel = randvel(N)

pos1, vel1, glo, loc = swarm(pos, vel, 100)

print("Minimum am Ende:", fkt(pos1[:, :, -1]))

''' Ausführung des Aufgabenteils b) '''

for i in range(N):
    plt.plot(np.arange(101), loc[i,:], linewidth=1, label="Pers. Min Nr."+str(i+1))
plt.plot(np.arange(101), glo, '-r', linewidth=2, label="Global Min")

plt.xlabel("Anzahl an Iterationen") 
plt.ylabel("Wert der Minima")
plt.legend(loc="upper right")

try:
    plt.savefig("plots/a2b.pdf")
except:
    plt.show()

# plt.scatter(pos1[0, :, -1], pos1[1, :, -1])
# plt.xlim((-5, 5))
# plt.ylim((-5, 5))
# plt.xticks(np.arange(-5, 5, step=1))
# plt.yticks(np.arange(-5, 5, step=1))

# plt.grid()
# plt.tight_layout()
# plt.show()