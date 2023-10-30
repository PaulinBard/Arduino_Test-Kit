# Définir une matrice 8x8 (exemple)
matrice = [
    [1, 2, 3, 4, 5, 6, 7, 8],
    [9, 10, 11, 12, 13, 14, 15, 16],
    [17, 18, 19, 20, 21, 22, 23, 24],
    [25, 26, 27, 28, 29, 30, 31, 32],
    [33, 34, 35, 36, 37, 38, 39, 40],
    [41, 42, 43, 44, 45, 46, 47, 48],
    [49, 50, 51, 52, 53, 54, 55, 56],
    [57, 58, 59, 60, 61, 62, 63, 64]
]

# Parcourir la matrice de  de haut en bas,droite à gauche
for ligne in range(len(matrice)):  # Parcours des lignes
    for colonne in range(len(matrice[0]) - 1, -1, -1):  # Parcours des colonnes de droite à gauche
        print(matrice[ligne][colonne], end=" ")  # Afficher l'élément
    print()  # Aller à la ligne suivante après chaque ligne parcourue

# Parcourir la matrice de haut en bas, de gauche à droite
for ligne in range(len(matrice)):  # Parcours des lignes de haut en bas
    for colonne in range(len(matrice[0])):  # Parcours des colonnes de gauche à droite
        print(matrice[ligne][colonne], end=" ")  # Afficher l'élément
    print()  # Aller à la ligne suivante après chaque ligne parcourue

# Parcourir la matrice de bas en haut, de droite à gauche
for ligne in range(len(matrice) - 1, -1, -1):  # Parcours des lignes de bas en haut
    for colonne in range(len(matrice[0]) - 1, -1, -1):  # Parcours des colonnes de droite à gauche
        print(matrice[ligne][colonne], end=" ")  # Afficher l'élément
    print()  # Aller à la ligne suivante après chaque ligne parcourue

# Parcourir la matrice de bas en haut, de gauche à droite
for ligne in range(len(matrice) - 1, -1, -1):  # Parcours des lignes de bas en haut
    for colonne in range(len(matrice[0])):  # Parcours des colonnes de gauche à droite
        print(matrice[ligne][colonne], end=" ")  # Afficher l'élément
    print()  # Aller à la ligne suivante après chaque ligne parcourue

    # Ajouter une nouvelle ligne de zéros au début de la matrice
nouvelle_ligne = [0] * len(matrice[0])
matrice.insert(0, nouvelle_ligne)
derniere_ligne = matrice.pop()

# Afficher la matrice après la suppression de la dernière ligne
for ligne in matrice:
    print(ligne)

# Afficher la dernière ligne récupérée
print("Dernière ligne supprimée :", derniere_ligne)

def parcourir_matrice(matrice, depart, arrivee):
    lignes = len(matrice)
    colonnes = len(matrice[0])
    
    if depart == "bas":
        lignes_range = range(lignes)
    elif depart == "haut":
        lignes_range = range(lignes - 1, -1, -1)
    elif depart == "gauche":
        lignes_range = range(lignes)
    elif depart == "droite":
        lignes_range = range(lignes)
    
    if arrivee == "bas":
        colonnes_range = range(colonnes)
    elif arrivee == "haut":
        colonnes_range = range(colonnes)
    elif arrivee == "gauche":
        colonnes_range = range(colonnes - 1, -1, -1)
    elif arrivee == "droite":
        colonnes_range = range(colonnes)
    
    for i in lignes_range:
        for j in colonnes_range:
            print(matrice[i][j], end="\t")
        print()

# Exemple d'utilisation
matrice2 = [
    [1, 2, 3, 4],
    [5, 6, 7, 8],
    [9, 10, 11, 12],
    [13, 14, 15, 16]
]

depart = "haut"  # Peut être "bas", "haut", "gauche", ou "droite"
arrivee = "droite"  # Peut être "bas", "haut", "gauche", ou "droite"

parcourir_matrice(matrice2, depart, arrivee)
