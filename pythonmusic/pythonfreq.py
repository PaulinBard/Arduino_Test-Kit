import pyaudio
import numpy as np

# Paramètres du signal audio
frequence = 440  # Fréquence en Hz (La note A4)
duree = 3  # Durée en secondes

# Fonction pour générer un signal sinusoidal
def generer_signal_sinusoidal(frequence, duree, echantillonnage=44100):
    t = np.linspace(0, duree, int(duree * echantillonnage), False)  # Crée un tableau de temps
    signal = 0.5 * np.sin(2 * np.pi * frequence * t)  # Signal sinusoidal
    return signal

# Initialise PyAudio
p = pyaudio.PyAudio()

# Paramètres audio
FORMAT = pyaudio.paFloat32
CHANNELS = 1
RATE = 44100

# Ouvre un flux audio en sortie
stream = p.open(format=FORMAT,
                channels=CHANNELS,
                rate=RATE,
                output=True)

# Génère le signal audio
signal = generer_signal_sinusoidal(frequence, duree)

# Lit le signal en continu
while True:
    stream.write(signal.tobytes())

# Arrête le flux audio
stream.stop_stream()
stream.close()

# Termine PyAudio
p.terminate()
