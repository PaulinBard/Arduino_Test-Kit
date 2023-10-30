import serial
import serial.tools.list_ports
import matplotlib.pyplot as plt
from matplotlib import animation
import time
import numpy as np

# Initialisation des listes pour stocker les données
liste_temps_mesure = []
liste_temps = []
liste_distance = []

# Durée d'acquisition et distance maximale
t_acquisition = 30.0
distancemax = 500

# Fonction d'animation pour mettre à jour le graphe en temps réel
def animate(i):
    line1 = Data.readline()
    listeDonnees = line1.strip().split()

    if len(listeDonnees) != 0:
        distance = float(listeDonnees[0].decode())
        tempsmes = time.time()
        liste_temps_mesure.append(tempsmes)
        tempsreel = tempsmes - liste_temps_mesure[0]
        while tempsreel <= t_acquisition:
            liste_distance.append(distance)
            print("d = %f" % (distance), " mm")
            liste_temps.append(tempsreel)
            print("temps réel= %f" % (tempsreel), " s") 
            line.set_data(liste_temps, liste_distance)
            return line,

# Fonction pour récupérer le port série de l'Arduino
def recup_port_Arduino():
    ports = list(serial.tools.list_ports.comports())
    mData = 0
    for p in ports:
        print(p.description)
        if 'USB2.0-Serial' in p.description:
            mData = serial.Serial(p.device, 9600)
    print(mData.is_open)
    print(mData.name)
    return mData

# Récupération du port série
Data = recup_port_Arduino()

# Création de la figure et du graphe
fig = plt.figure()
line, = plt.plot([], [])
plt.xlim(0, t_acquisition)
plt.ylim(0, distancemax)
plt.xlabel('temps en s')
plt.ylabel('distance en mm')
plt.grid()

# Animation du graphe en temps réel
ani = animation.FuncAnimation(fig, animate, frames=600, interval=20, repeat=False)# 200 frame == 10 sec+  //// 600 frame== 30 sec+

# Affichage du graphe en temps réel
plt.show()
plt.close(fig)
Data.close()

# Écriture des données dans un fichier texte
lines = ["0\t0\n"]
for i in range(len(liste_distance)):
    line = str(liste_temps[i]) + '\t' + str(liste_distance[i]) + '\n'
    lines.append(line)

fichier = open('data_arduino.txt', 'w')
fichier.writelines(lines)
fichier.close()

# Lecture des données à partir du fichier et création du graphe final
data = np.loadtxt('data_arduino.txt')
temps = data[:, 0]
distance = data[:, 1]

# Création du graphe final
plt.figure()
plt.plot(temps, distance, marker='o', linestyle='-', color='b')
plt.xlabel('Temps en secondes')
plt.ylabel('Distance en mm')
plt.title('Graphe de Distance en fonction du Temps')
plt.grid()
plt.savefig('graphique_distance_temps.png')
plt.show()
