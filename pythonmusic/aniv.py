import mido
from mido import MidiFile, MidiTrack, Message
import time

# Créez un nouveau fichier MIDI
mid = MidiFile()
track = MidiTrack()
mid.tracks.append(track)

# Ajoutez les messages MIDI pour jouer "Joyeux Anniversaire"
notes = [60, 60, 62, 60, 65, 64, 60, 60, 62, 60, 67, 65]
duree_note = 480  # Durée d'une note en unités de temps (à ajuster selon votre tempo)

for note in notes:
    # Ajoutez un message de note ON
    note_on = Message('note_on', note=note, velocity=64, time=0)
    track.append(note_on)
    
    # Ajoutez un message de note OFF après la durée de la note
    note_off = Message('note_off', note=note, velocity=64, time=duree_note)
    track.append(note_off)

# Enregistrez le fichier MIDI
mid.save('joyeux_anniversaire.mid')

print("Fichier MIDI 'joyeux_anniversaire.mid' créé.")

# Jouez le fichier MIDI
with mido.MidiFile('joyeux_anniversaire.mid') as midi:
    for msg in midi.play():
        time.sleep(msg.time)
