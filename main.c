/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "affichage.h"
#include "combattants.h"

#define NB_COMBATTANTS 8

int main() {
    srand(time(NULL)); // Initialisation de la graine pour rand()
    // Affichage de la bannière
    afficherCY();
    printf("\n\033[1;33mAppuyez sur Entrée pour afficher les règles du jeu...\n\033[0m");
    getchar(); 
    afficherRegles();

    // Message pour continuer
    printf("\n\033[1;33mAppuyez sur Entrée pour commencer à jouer...\n\033[0m");
    getchar();

    // Ici vous pouvez mettre la suite de votre jeu
    printf("\n\033[1;32m========================================\n");
    printf("|                                      |\n");
    printf("|    🎮  LE JEU COMMENCE !  🎮         |\n"); 
    printf("|                                      |\n");
    printf("========================================\033[0m\n\n");
    printf("Choisir le mode de jeu :\n");
    printf("1. Mode Solo\n");
    printf("2. Mode Multijoueur\n");

    int modeJeu;
    do {
        printf("Mode de jeu (1 solo, 2 multijoueur) : ");
        scanf("%d", &modeJeu);
    } while (modeJeu != 1 && modeJeu != 2);

    int nbCombattantsEquipe;
    do {
        printf("Combien de combattants par équipe ? (1 à 3) : ");
        scanf("%d", &nbCombattantsEquipe);
    } while (nbCombattantsEquipe < 1 || nbCombattantsEquipe > 3);

    // Afficher les combattants
    printf("\n\033[1;33mVoici les combattants disponibles :\n\033[0m");
    void afficherCombattants();

    // Charger les combattants
    Combattant* combattants = chargerCombattants("combattants.txt", NB_COMBATTANTS);

    // Afficher les combattants
    for (int i = 0; i < NB_COMBATTANTS; i++) {
        printf("num combattant %d \n", i + 1);
        afficherCombattant(combattants[i]);
    }

    // Choisir les combattants de l'équipe 1
    Combattant* equipe1 = malloc(nbCombattantsEquipe * sizeof(Combattant));
    equipe1 = choisirEquipe(combattants, NB_COMBATTANTS, equipe1, nbCombattantsEquipe);
    printf("Entrez le nom de votre équipe : ");
    char nomEquipe1[50];
    scanf("%49s", nomEquipe1);
    
    // Choisir les combattants de l'équipe 2
    char nomEquipe2[50];
    Combattant* equipe2 = malloc(nbCombattantsEquipe * sizeof(Combattant));
    if (modeJeu == 1) {
        printf("\n\033[1;33mL'IA choisit ses combattants...\n\033[0m");
        for (int i = 0; i < nbCombattantsEquipe; i++) {
            int choixIA = rand() % NB_COMBATTANTS;
            equipe2[i] = combattants[choixIA];
            printf("L'IA a choisi le combattant %s\n", combattants[choixIA].nom);
            strcpy(nomEquipe2, "IA");
        }
    } else {
        equipe2 = choisirEquipe(combattants, NB_COMBATTANTS, equipe2, nbCombattantsEquipe);
        printf("Entrez le nom de votre équipe : ");
        scanf("%49s", nomEquipe2);
    }

    // Libérer la mémoire
    free(combattants);

    // afficher l'équipe 1
    for (int i = 0; i < nbCombattantsEquipe; i++) {
        printf("Combattant %d de l'équipe 1 : \n", i + 1);
        afficherCombattant(equipe1[i]);
    }
    // afficher l'équipe 2
    for (int i = 0; i < nbCombattantsEquipe; i++) {
        printf("Combattant %d de l'équipe 2 : \n", i + 1);
        afficherCombattant(equipe2[i]);
    }

    clearInputBuffer();
    int round = 1;
    int continuer = 1;
    while (continuer) {

        // Vérifier si une équipe a gagné
        for (int i = 0; i < nbCombattantsEquipe; i++) {
            if (equipe1[i].pointvie <= 0) {
                printf("\n\033[1;31m%s est KO !\n\033[0m", equipe1[i].nom);
                printf("L'équipe 2 a gagné !\n");
                continuer = 0;
            }
            if (equipe2[i].pointvie <= 0) {
                printf("\n\033[1;31m%s est KO !\n\033[0m", equipe2[i].nom);
                printf("L'équipe 1 a gagné !\n");
                continuer = 0;
            }
        }

        if (!continuer) {
            break;
        }

        // Ici vous pouvez mettre la logique de combat
        printf("\n\033[1;33mDébut du round %d...\n\033[0m", round);
        printf("\n\033[1;33mAppuyez sur Entrée pour continuer le combat...\n\033[0m");
        getchar();

        // Logique de combat ici

        // Tour de l'équipe 1
        gererCombatParEquipe(equipe1, nomEquipe1, equipe2, nomEquipe2, nbCombattantsEquipe);

        // Tour de l'équipe 2
        if (modeJeu == 1) {
            printf("\n\033[1;33mL'IA attaque...\n\033[0m");
            for (int i = 0; i < nbCombattantsEquipe; i++) {
        
                int choixAttaque = rand() % 2 + 1; // Choix aléatoire entre 1 et 2
        
                if (choixAttaque == 1) {
                    printf("IA avez choisi l'attaque normale ! \n");
                    // Logique de l'attaque normale ici
                    int numCible = rand() % nbCombattantsEquipe + 1; // Choix aléatoire de la cible
                    printf("EQUIPE %s :\n", nomEquipe1);
                    for (int j = 0; j < nbCombattantsEquipe; j++) {
                        printf("%d: %s\n",j+1, equipe1[j].nom);
                    }
            
                    attaqueNormale(equipe2[i], &equipe1[numCible - 1]);
                    afficherCombattant(equipe2[numCible - 1]);
                } else {
                    printf("IA avez choisi la technique spéciale ! \n");
                }
            }
          
        } else if (modeJeu == 2) {
            gererCombatParEquipe(equipe2, nomEquipe2, equipe1, nomEquipe1, nbCombattantsEquipe);
        } else {
            printf("\n\033[1;33mC'est au tour de l'IA...\n\033[0m");
        }
        round++;
    }
    // Libérer la mémoire
    free(equipe1);
    free(equipe2);
    // Afficher le message de fin
    printf("\n\033[1;31mMerci d'avoir joué !\n\033[0m");

    return 0;
}
*/
#include "bibliotheques.h"

#include "affichage.h"
#include "combattants.h"

#define RESET "\033[0m"
#define ROUGE "\033[1;31m"
#define VERT "\033[1;32m"
#define BLEU "\033[1;34m"
#define JAUNE "\033[1;33m"
#define CYAN "\033[1;36m"

#define NB_COMBATTANTS 8

int main() {
    char choixRejouer;
    int rejouer = 1;
    srand(time(NULL)); // Initialisation de la graine pour rand()
    // Affichage de la bannière
    afficherCY();
    printf("\n\033[1;33mAppuyez sur Entrée pour afficher les règles du jeu...\n\033[0m");
    getchar(); 
    afficherRegles();

    // Message pour continuer
    printf("\n\033[1;33mAppuyez sur Entrée pour commencer à jouer...\n\033[0m");
    getchar();

    // Ici vous pouvez mettre la suite de votre jeu
    printf("\n\033[1;32m========================================\n");
    printf("|                                      |\n");
    printf("|    🎮  LE JEU COMMENCE !  🎮           |\n"); 
    printf("|                                      |\n");
    printf("========================================\033[0m\n\n");

    do{
    int modeJeu = 0;
    do {
        afficherBanniere("Choix du Mode de Jeu");
        printf("1. Solo (contre l'IA)\n2. Multijoueur\nVotre choix : ");
        scanf("%d", &modeJeu);
        if (modeJeu != 1 && modeJeu != 2) {
            printf("%s[ERREUR] Choix invalide. Veuillez réessayer.%s\n", ROUGE, RESET);
        }
    } while (modeJeu != 1 && modeJeu != 2);

    int nbCombattantsEquipe = 0;
    do {
        printf("%sCombien de combattants par équipe (1 à 3) ? %s", JAUNE, RESET);
        scanf("%d", &nbCombattantsEquipe);
        if (nbCombattantsEquipe < 1 || nbCombattantsEquipe > 3) {
            printf("%s[ERREUR] Choix invalide. Veuillez choisir entre 1 et 3.%s\n", ROUGE, RESET);
        }
    }while(nbCombattantsEquipe < 1 || nbCombattantsEquipe > 3);
    
    // Afficher les combattants
    printf("%sVoici les combattants disponibles :%s\n", JAUNE, RESET);
    void afficherCombattants();

    // Charger les combattants
    Combattant* combattants = chargerCombattants("combattants.txt", NB_COMBATTANTS);

    // Afficher les combattants
    for (int i = 0; i < NB_COMBATTANTS; i++) {
        printf("num combattant %d \n", i + 1);
        afficherCombattant(combattants[i]);
    }

    // Choisir les combattants de l'équipe 1
    Combattant* equipe1 = malloc(nbCombattantsEquipe * sizeof(Combattant));
    equipe1 = choisirEquipe(combattants, NB_COMBATTANTS, equipe1, nbCombattantsEquipe);
    printf("\n%sJoueur 1, nommez votre équipe : %s", BLEU, RESET);
    char nomEquipe1[50];
    scanf("%49s", nomEquipe1);
    
    // Choisir les combattants de l'équipe 2
    char nomEquipe2[50];
    Combattant* equipe2 = malloc(nbCombattantsEquipe * sizeof(Combattant));
    if (modeJeu == 1) {
        printf("\n\033[1;33mL'IA choisit ses combattants...\n\033[0m");
        for (int i = 0; i < nbCombattantsEquipe; i++) {
            int choixIA = rand() % NB_COMBATTANTS;
            equipe2[i] = combattants[choixIA];
            printf("L'IA a choisi le combattant %s\n", combattants[choixIA].nom);
        }
        strcpy(nomEquipe2, "IA Équipe");
		printf("%sL'IA a choisi le nom de son équipe : %s%s\n", CYAN, nomEquipe2, RESET);
        
    } else {
        equipe2 = choisirEquipe(combattants, NB_COMBATTANTS, equipe2, nbCombattantsEquipe);
        printf("%sJoueur 2, nommez votre équipe : %s", VERT, RESET);
        scanf("%49s", nomEquipe2);
    }

    // Libérer la mémoire
    free(combattants);

    // afficher l'équipe 1
    afficherBanniere("Équipes sélectionnées");
	printf("Équipe 1 : %s\n", nomEquipe1);
	printf("Équipe 2 : %s\n", nomEquipe2);
	/*
    for (int i = 0; i < nbCombattantsEquipe; i++) {
        printf("Combattant %d de l'équipe 1 : \n", i + 1);
        afficherCombattant(equipe1[i]);
    }
    // afficher l'équipe 2
    for (int i = 0; i < nbCombattantsEquipe; i++) {
        printf("Combattant %d de l'équipe 2 : \n", i + 1);
        afficherCombattant(equipe2[i]);
    }
*/

    // Affichage du VS avec les équipes et combattants
    afficherEquipeVS(equipe1, equipe2, nbCombattantsEquipe, nomEquipe1, nomEquipe2);

 
    // ===== COMBAT ======
    clearInputBuffer();
    int tour = 1;
    int continuer = 1;
    while (continuer) {
        
        // Ici vous pouvez mettre la logique de combat
        afficherBanniere("DEBUT DU COMBAT");
        printf("%s vs %s\n", nomEquipe1, nomEquipe2);
        printf("\n%s=== TOUR %d ===%s\n", JAUNE, tour++, RESET);
        printf("\n\033[1;33mAppuyez sur Entrée pour continuer le combat...\n\033[0m");
        getchar();

        // Logique de combat ici

        // Tour de l'équipe 1
        gererCombatParEquipe(equipe1, nomEquipe1, equipe2, nomEquipe2, nbCombattantsEquipe);

        // Tour de l'équipe 2
        if (modeJeu == 1) {
            printf("\n\033[1;33mL'IA attaque...\n\033[0m");
            for (int i = 0; i < nbCombattantsEquipe; i++) {
        
                int choixAttaque = rand() % 2 + 1; // Choix aléatoire entre 1 et 2
        
                if (choixAttaque == 1) {
                    printf("IA avez choisi l'attaque normale ! \n");
                    // Logique de l'attaque normale ici
                    int numCible = rand() % nbCombattantsEquipe + 1; // Choix aléatoire de la cible
                    printf("EQUIPE %s :\n", nomEquipe1);
                    for (int j = 0; j < nbCombattantsEquipe; j++) {
                        printf("%d: %s\n",j+1, equipe1[j].nom);
                    }
            
                    attaqueNormale(equipe2[i], &equipe1[numCible - 1]);
                    afficherCombattant(equipe2[numCible - 1]);
                } else {
                    printf("IA avez choisi la technique spéciale ! \n");
                }
            }
          
        } else if (modeJeu == 2) {
            gererCombatParEquipe(equipe2, nomEquipe2, equipe1, nomEquipe1, nbCombattantsEquipe);
        } else {
            printf("\n\033[1;33mC'est au tour de l'IA...\n\033[0m");
        }
        tour++;

        // Vérifier si une équipe a gagné
        for (int i = 0; i < nbCombattantsEquipe; i++) {
            if (equipe1[i].pointvie <= 0) {
                printf("\n\033[1;31m%s est KO !\n\033[0m", equipe1[i].nom);
                printf("L'équipe 2 a gagné !\n");
                continuer = 0;
            }
            if (equipe2[i].pointvie <= 0) {
                printf("\n\033[1;31m%s est KO !\n\033[0m", equipe2[i].nom);
                printf("L'équipe 1 a gagné !\n");
                continuer = 0;
            }
        }

        if (!continuer) {
            afficherGameOver();
            break;
        }

    }
    // Libérer la mémoire
    free(equipe1);
    free(equipe2);
    
    do {
    printf("Voulez-vous rejouer ? (o/n) : ");
    scanf(" %c", &choixRejouer);
    clearInputBuffer(); // vide le reste de la ligne
 
    if (choixRejouer == 'o' || choixRejouer == 'O') {
        rejouer = 1;
    } else if (choixRejouer == 'n' || choixRejouer == 'N') {
        rejouer = 0;
    } else {
        printf("Entrée invalide. Tapez 'o' pour oui ou 'n' pour non.\n");
    }
} while (choixRejouer != 'o' && choixRejouer != 'O' && choixRejouer != 'n' && choixRejouer != 'N');

 
    
} while (rejouer == 1);
    // Afficher le message de fin
    printf("\n\033[1;31mMerci d'avoir joué !\n\033[0m");

    return 0;
}
