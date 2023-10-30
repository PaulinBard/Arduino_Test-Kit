import mido
import pygame
import time

# Spécifiez le chemin du fichier MIDI que vous voulez jouer
midi_file_path = "joyeux_anniversaire.mid"

# Initialisez Pygame mixer (pour jouer des sons)
pygame.mixer.init()

# Ouvrez le fichier MIDI en lecture
mid = mido.MidiFile(midi_file_path)

# Parcourez tous les messages MIDI dans le fichier et jouez-les
for msg in mid.play():
    # Vérifiez si le message est de type "note_on"
    if msg.type == "note_on":
        # Jouez la note MIDI avec le son par défaut (channel=0)
        pygame.mixer.Sound(f"piano_samples/note{msg.note}.wav").play()

    # Attendez avant de jouer le prochain message MIDI (ajustez le temps si nécessaire)
    time.sleep(msg.time)

# Fermez le fichier MIDI
mid.close()
