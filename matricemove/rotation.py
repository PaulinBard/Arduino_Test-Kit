
def pivoter_matrice(matrice, direction):
    lignes = len(matrice)
    colonnes = len(matrice[0])
    
    # Effectuer la transposition de la matrice
    matrice_transposee = [[matrice[j][i] for j in range(lignes)] for i in range(colonnes)]
    
    # Inverser les lignes si la direction est "gauche"
    if direction == "gauche":
        matrice_transposee = matrice_transposee[::-1]
    elif direction == "droite":
        matrice_transposee = [ligne[::-1] for ligne in matrice_transposee]
    # Inverser les lignes et les colonnes pour "bas"
    elif direction == "haut":
        matrice_transposee =  [ligne[::-1] for ligne in matrice[::-1]]
    return matrice_transposee

def imprimer_matrice(matrice):
    for ligne in matrice:
        print(" ".join(map(str, ligne)))

# Exemple d'utilisation
matrice =[
    [0, 0, 0, 0, 0, 0, 0, 1],
    [0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 1, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0],
    [1, 1, 1, 0, 1, 1, 1, 0],
    [1, 1, 1, 1, 1, 1, 1, 1]
]

direction = "haut"  # Peut être "droite", "gauche" ou "bas"

nouvelle_matrice = pivoter_matrice(matrice, direction)
imprimer_matrice(nouvelle_matrice)
direction = "gauche"  # Peut être "droite", "gauche" ou "bas"

nouvelle_matrice = pivoter_matrice(matrice, direction)
imprimer_matrice(nouvelle_matrice)
direction = "droite"  # Peut être "droite", "gauche" ou "bas"

nouvelle_matrice = pivoter_matrice(matrice, direction)
imprimer_matrice(nouvelle_matrice)