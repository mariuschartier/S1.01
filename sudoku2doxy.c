#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

/**
 * \file sudoku2doxy.c
 * \brief programme de jeu de sudoku ou  l'on peut jouer 
 * \author Chartie--Le Goff Marius
 * \version 1.7
 * \date 26/11/2023
*/

#define N  3
/**
 * \def N
 * \brief longeur d'un block de sudoku 
*/

#define TAILLE  N*N
/** 
 * \def TAILLE
 * \brief longeur d'un coté de la grille de sudoku
 * \see N : TAILLE est égale à N*N
*/


/** 
* \brief tableau qui représente la grille de sudoku
* \see TAILLE :longueur d'un coté de la grille
*
* tableau de 9 par 9 qui représentec la grille de sudoku il ne sera rempli que de chiffre de 0 à 9
*
*/
typedef int tGrille[TAILLE][TAILLE];

/** 
* \brief procedure qui modifie la valeur prise en entré selon certaine condition
* \param valeur la valeur modifié
*/
void saisir(int *valeur);


/**
 * @brief Vérifie si une valeur donnée peut être placée dans la grille de sudoku à une position spécifiée.
 *
 * @param sudoku : La grille de jeu représentée par un tableau bidimensionnel.
 * @param x : La coordonnée x de la position dans la grille.
 * @param y : La coordonnée y de la position dans la grille.
 * @param valeur : La valeur à vérifier pour son placement dans la grille.
 *
 * @return renvoie true si la valeur peut être placée à la position spécifiée, sinon false.
 *
 */
bool possible(tGrille,int x, int y, int valeur);

/** 
 * \brief procedure qui remplit le tableau sudoku avecdes chiffre à partir d'un fichier .sud
 * \param sudoku : la grille du  sudoku
*/
void chargerGrille(tGrille sudoku );

/** 
 * \brief procedure qui affiche la grille de sudoku
 * \param sudoku : la grille du sudoku
*/
void affiche_grille(tGrille sudoku);

/**
 * \brief Fonction qui compte le nombre de zero
 *
 * \param sudoku : la grille de sudoku
 * \return renvoie un entier positif qui est le nombre de zero.
 */
int compte_zero(tGrille sudoku) ;




/** 
 * \brief programme principale 
*/
int main(){
    int nbcol=TAILLE, nblig=TAILLE,valeur,nb_zero=0,i,j;
    tGrille sudoku;

  chargerGrille(sudoku);

    printf("règles: ")  
    
    for ( i = 0; i < TAILLE; i++){
        for ( j = 0; j < TAILLE; j++){
            if (sudoku[i][j] == 0){
                nb_zero = nb_zero + 1;
            }
        }
    }
    //on compte le nombre de zero dans la grille car quand il n'y en aura plus la grille sera complete

    if(nb_zero == 0){
        printf("ERREUR: la grille de depart est complete");
    }
    else{
        do{ 
            affiche_grille(sudoku);

            printf("Indices de la case ? \n");
            printf("numero ligne:  ");
            saisir(&nblig);
            printf("numero colonne");
            saisir(&nbcol);
            
            nbcol--;
            nblig--;
            // on decrémente nblig et nbcol car pour l'utilisateur les
            // coordonnées sont de 1 à 9 alors que le programme les compte de 0 à 8

            if (sudoku[nblig][nbcol] != 0)
            {
                printf("IMPOSSIBLE, la case n'est pas libre.\n");
            }
            else{
                printf("Valeur à insérer ? \n");
                saisir(&valeur);
                if (possible(sudoku, nblig, nbcol, valeur)){
                    sudoku[nblig][nbcol] = valeur;
                    nb_zero -= 1;
                    }
            }     
        }while (nb_zero > 0);
        //le boucle continu tant qu'il y a des cases vides
        printf("fin de la partie");
    }

    return EXIT_SUCCESS;
}



/*****************************************************
* déclaration des fonctions / procedures *
*****************************************************/

void affiche_grille(tGrille sudoku){

   
   int ligne,colonne;

   printf("     1 2 3   4 5 6   7 8 9 \n");
    printf("   +-------+-------+-------+");
    for (ligne = 0; ligne < TAILLE; ligne++){
        printf("\n%d  | ", ligne+1);
        for (colonne = 0; colonne < TAILLE; colonne++){
            if (sudoku[ligne][colonne] == 0){
            printf(". ");
            }
            //les zeros / cases vides sont remplacées des points
        
            else{
                printf("%d ", sudoku[ligne][colonne]);
            }
            if (colonne % N == 2){
                printf("| ");
                }
        }
        if (ligne % N == 2){printf("\n   +-------+-------+-------+");}
    }
           
    printf("\n");
 }
/*-----------------------------------------------------------------------------------------------------------*/
void chargerGrille(tGrille g){
    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } else {
        fread(g, sizeof(int), TAILLE*TAILLE, f);
    }
    fclose(f);
    }
/*-----------------------------------------------------------------------------------------------------------*/
void saisir(int *valeur){   

    int r;
    char appel[55];
    do
    {
        scanf("%s", appel);
    if ((sscanf(appel, "%d", &r) != 0) && ((r < 10) && (r > 0))){
        *valeur = r;} 
        else {
            printf("erreur vous devez donner un entier entre 1 et 9\n");
    }

    } while ((r == 0) || ((r > 9) || (r < 1)));
    }
/*-----------------------------------------------------------------------------------------------------------*/
bool possible(tGrille sudoku, int x, int y, int valeur){
    bool possible = true;
    int indice, case_x, case_y, ligne,colonne;
    
    
      
        for ( indice = 0; indice < TAILLE; indice++){
            if ((valeur == sudoku[x][indice]) &&  (indice != y)){
                possible = false;
                printf("impossible de poser la valeur car il y a une valeur identique dans la ligne\n");
            }
            //verification qu'il n'y pas la meme valeur dans la ligne

            if ((valeur == sudoku[indice][y]) && (indice != x)) {
                possible = false;
                printf("impossible de poser la valeur car il y a une valeur identique dans la colonne\n");
            }
            //verification qu'il n'y pas la meme valeur dans la colonne
        }
        
        case_x = x - (x % N);
        case_y = y - (y % N);
        //on calcul les coordonnées de la case en haut à gauche d'un block
        for ( ligne = case_x; ligne <= case_x + 2; ligne++){
            for ( colonne = case_y; colonne <= case_y + 2; colonne++){
                
                if (valeur == sudoku[ligne][colonne]){
                possible = false;
                printf("impossible de poser la valeur car il y a une valeur identique dans le block\n");
                }
            }
        }
        //verification qu'il n'y pas la meme valeur dans le block
    
    return possible;
    }
/*-----------------------------------------------------------------------------------------------------------*/




