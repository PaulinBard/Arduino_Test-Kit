def inverser_matrice_vers_le_bas(matrice):
    # Inverser l'ordre des lignes et inverser l'ordre des éléments dans chaque ligne
    matrice_inversee = [ligne[::-1] for ligne in matrice[::-1]]
    return matrice_inversee

# Exemple d'utilisation
matrice = [
    [1, 2, 3, 4],
    [5, 6, 7, 8],
    [9, 10, 11, 12],
    [13, 14, 15, 16]
]

nouvelle_matrice = inverser_matrice_vers_le_bas(matrice)

# Afficher la matrice résultante
for ligne in nouvelle_matrice:
    print(ligne)
