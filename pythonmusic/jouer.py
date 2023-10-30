import pygame.mixer
import time

# Initialiser pygame
pygame.mixer.init()
import serial
import serial.tools.list_ports
import time


#32 caractere max car ecran 16*2
char_ecran=32


# Fonction pour récupérer le port série de l'Arduino
def recup_port_Arduino():
    ports = list(serial.tools.list_ports.comports())
    mData = 0
    for p in ports:
        print(p.description)
        if 'USB Serial' in p.description:
            mData = serial.Serial(p.device, 9600)
    print(mData)
    return mData

# Charger les fichiers audio depuis le répertoire /doremi
dossier_doremi = "newdosi"
format="mp3"
do_sound = pygame.mixer.Sound(f"{dossier_doremi}/do.{format}")
re_sound = pygame.mixer.Sound(f"{dossier_doremi}/re.{format}")
mi_sound = pygame.mixer.Sound(f"{dossier_doremi}/mi.{format}")
fa_sound = pygame.mixer.Sound(f"{dossier_doremi}/fa.{format}")
sol_sound = pygame.mixer.Sound(f"{dossier_doremi}/sol.{format}")
la_sound = pygame.mixer.Sound(f"{dossier_doremi}/la.{format}")
si_sound = pygame.mixer.Sound(f"{dossier_doremi}/si.{format}")


Data = recup_port_Arduino()
while(True):
    if Data is not None and Data!=0 and Data.is_open :
        note = Data.readline().decode('utf-8').strip()
        print("Données reçues depuis l'Arduino :", note)
       
        if note == "12":
            do_sound.play()
        elif note == "24":
            re_sound.play()
        elif note == "94":
            mi_sound.play()
        elif note == "8":
            fa_sound.play()
        elif note == "28":
            sol_sound.play()
        elif note == "90":
            la_sound.play()
        elif note == "66":
            si_sound.play()

    # Pause entre les notes (ajustez selon votre préférence)
    

# # Attendre la fin de la mélodie
# pygame.time.wait(int(1000 * len(melodie) * 0.5))

# # Quitter pygame
# pygame.mixer.quit()
