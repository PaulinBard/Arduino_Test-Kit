import os

# Chemin vers le dossier contenant les fichiers à renommer
dossier_source = "44.1khz16bit"

# Chemin vers le dossier de sortie où les fichiers renommés seront enregistrés
dossier_destination = "piano_samples"




os.makedirs(dossier_destination, exist_ok=True)

correspondance_notes_midi = {
    "C": 60, "C#": 61, "D": 62, "D#": 63, "E": 64, "F": 65, "F#": 66, "G": 67, "G#": 68, "A": 69, "A#": 70, "B": 71
}


for nom_fichier in os.listdir(dossier_source):
    if nom_fichier.endswith(".wav") and nom_fichier.count("v") == 1:
        note, reste = nom_fichier.split("v")
        if note[-1] in correspondance_notes_midi:
            octave = int(note[-1])
            note_sans_octave = note[:-1]
            valeur_midi = correspondance_notes_midi[note_sans_octave] + octave * 12
            nouveau_nom_fichier = f"{valeur_midi}v{reste}.wav"

            chemin_source = os.path.join(dossier_source, nom_fichier)
            chemin_destination = os.path.join(dossier_destination, nouveau_nom_fichier)

            os.rename(chemin_source, chemin_destination)
            print(f"Fichier renommé : {nom_fichier} -> {nouveau_nom_fichier}")
        else:
            print(f"Ignoré : Nom de fichier avec une note invalide : {nom_fichier}")
    else:
        print(f"Ignoré : Format de fichier incorrect : {nom_fichier}")

print("Opération terminée.")
