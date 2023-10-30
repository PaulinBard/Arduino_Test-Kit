from enum import Enum

dim= 8
Oldcote=4



class cote(Enum):
    DROITE = 1
    GAUCHE = 2
    HAUT = 3
    BAS = 4

# Définition de la taille du verre

def creer_matrice(dimension):
    # Crée une matrice de dimension x dimension remplie de zéros
    matrice = [[0 for _ in range(dimension)] for _ in range(dimension)]
    # Placez un 1 au centre de la matrice
    matrice[dimension // 2][dimension // 2] = 1
    return matrice


# Supposons que votre matrice 8x8 soit représentée comme une liste de listes appelée "matrice"
matrice =[
    [0, 0, 0, 0, 0, 0, 0, 1],
    [0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 1, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0],
    [1, 1, 1, 0, 0, 0, 1, 0],
    [0, 0, 0, 0, 0, 0, 0, 1]
]

# retourne le coté avec le plus de point ou l'ancien depart si il y a égalité
def chercher_depart(matrice,oldD): 
    dim=len(matrice)
    print(dim)
    # Diviser la matrice en 4 zones (A, B, C, D)
    zone_a = [ligne[:int(dim/2)] for ligne in matrice[:int(dim/2)]]#HAUT GAUCHE
    zone_b = [ligne[int(dim/2):] for ligne in matrice[:int(dim/2)]]#HAUT DROITE
    zone_c = [ligne[:int(dim/2)] for ligne in matrice[int(dim/2):]]#BAS G
    zone_d = [ligne[int(dim/2):] for ligne in matrice[int(dim/2):]]#BAS D

    # Compter les 1 dans chaque zone
    nb_1_zone_a = sum(sum(ligne) for ligne in zone_a)
    nb_1_zone_b = sum(sum(ligne) for ligne in zone_b)
    nb_1_zone_c = sum(sum(ligne) for ligne in zone_c)
    nb_1_zone_d = sum(sum(ligne) for ligne in zone_d)

    # Afficher le nombre de 1 dans chaque zone
    D=nb_1_zone_b+nb_1_zone_d
    G=nb_1_zone_a+nb_1_zone_c
    H=nb_1_zone_a+nb_1_zone_b
    B=nb_1_zone_c+nb_1_zone_d

    if D == G or D == H or D == B or G == H or G == B or H == B:
        return oldD
    else:
        # Trouver le plus grand nombre parmi les quatre
        nombre=max(D, G, H, B)
        if D == nombre:
            
            print("La variable Droite est égale au nombre.")
            return cote.DROITE
        elif G == nombre:
            print("La variable Gauche est égale au nombre.")
            return cote.GAUCHE
        elif H == nombre:
            print("La variable Haut est égale au nombre.")
            return cote.HAUT
        elif B == nombre:
            print("La variable Bas est égale au nombre.")
            return cote.BAS






# Utilisation de la fonction pour créer une matrice 8x8
matrice_8x8 = creer_matrice(8)
chercher_depart(matrice,0)