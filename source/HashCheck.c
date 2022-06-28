// gcc -Wall -pedantic verifHash.c -o verifHash -lcrypto -lssl

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <openssl/md5.h>

/* Création des variables globales */
int pidF0, pidF1, pidF2; //PIDs des fils utiles
int tier0, tier1, tier2; //Ligne de début analyse fichier
int nbLigne; //Nombre ligne fichier a analyser
char* motTrouve; //Mot trouvé
int ligneTrouve; //Numéro de la ligne ou se situe le mot trouvé
char* hashAnalyse; //Hash a trouvé dans le fichier
FILE* fichier; //Pointeur fichier ouverture
char* fichierAnalyse; //Buffer nom du fichier à analyser
char* contenuFichier; //Buffer de lecture ligne à ligne
struct stat sb;
unsigned char hashMot[MD5_DIGEST_LENGTH]; //Buffer hash fonction md5
char hash[2*MD5_DIGEST_LENGTH+1] = ""; //Buffer hash après conversion de uchar en char
int filsCree; //Booleen fils cree ou non

/**
 * @brief Afficher le résultat de l'analyse
 * @param ligne 
 * @param mot 
 */
void affichageResultat(int ligne, char* mot){
    if (ligne == -1){
        printf("Pas de correspondance trouvé dans le fichier");
    }
    
}

/**
 * @brief Convertir le hash en string 
 * @param string 
 * @param hash 
 */
void ConversionHash(char *motHasher, char *hashConv){
    /* Conversion unsigned char -> char */
    for (int i=0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(hashConv + 2*i, "%02x", motHasher[i]);
    }
}

// ./verifhash fichier hash typeHash -f/-l
int main(int argc, char* argv[]){

    /* Test du bon appel du script */
    if (argc != 5){
        printf("Les arguments entrés sont invalides\n\n");
        printf("Méthodologie : \n");
        printf("\tAppel : %s fichierAnalyse hashAnalyse typeHash -f/-l\n", argv[0]);
        printf("\t-f : hash du fichier\n");
        printf("\t-l : Hash ligne à ligne du fichier\n");
        exit(0);
    }

    fichierAnalyse = malloc(sizeof(char)*strlen(argv[1]));
    strcpy(fichierAnalyse, argv[1]); //Copie nom du fichier dans une variable
    hashAnalyse = malloc(sizeof(char)*strlen(argv[2]));
    strcpy(hashAnalyse, argv[2]); //Copie hash a trouver dans une variable

    /* Test si calcul hash du fichier */
    if (!strcmp(argv[4], "-f")){
        //Calculer le hash du fichier
        exit(0);
    }

    /* Ouverture du fichier en lecture seule */    
    fichier = fopen(fichierAnalyse, "r");

    /* Verification de la bonne ouverture du fichier */
    if (!fichier) {
        perror("Erreur ouverture de fichier");
        exit(2);
    }

    stat(fichierAnalyse , &sb);
    contenuFichier = malloc(sb.st_size);

    //A faire
    /* Calcul du nombre de ligne du fichier */ 
    nbLigne = 3;

    /* Création de deux fils si nombre de ligne dans le fichier est assez conséquent */
    if (nbLigne > 300){

        tier0 = 0;
        tier1 = nbLigne/3;
        tier2 = 2*nbLigne/3;

        pidF1 = fork(); //Création du premier fils d'analyse
        /* Test bonne création du fils */
        if (pidF1 <0){
            perror("Erreur création fils premier tier");
            exit(1);
        } 
        /* Code du fils */
        else if (pidF1 == 0){
            // Analyse premiere ligne
        }

        pidF2 = fork(); //Création du premier fils d'analyse
        /* Test bonne création du fils */
        if (pidF2 <0){
            perror("Erreur création fils deuxieme tier");
            exit(1);
        } 
        /* Code du fils */
        else if (pidF2 == 0){
            // Analyse premiere ligne
        }

    } 
    /* Code du pere */ 
    else { // Le pere gère le fichier complet
        tier2 = 1; 
    }

    int finAnalyse = 0;

    while (fscanf(fichier, "%[^\n] ", contenuFichier) != EOF && !finAnalyse) {        

        //printf("%s\n", contenuFichier);
        MD5((const unsigned char *)contenuFichier, strlen(contenuFichier), hashMot);

        /* Conversion unsigned char -> char */
        //ConversionHash(hashMot, hash);        
        for (int i=0; i < MD5_DIGEST_LENGTH; i++) {
            sprintf(hash + 2*i, "%02x", hashMot[i]);
        }

        if (!strcmp(hashAnalyse, hash)){
            finAnalyse = 1;
            printf("\n=== MOT TROUVE ===\n");
            printf("Hash trouvé : %s\n",hash);
            printf("Hash d'analyse : %s\n", hashAnalyse);
            printf("Mot associé : %s\n", contenuFichier);
            printf("Ligne du mot dans le fichier : %d\n\n", tier2);
        } else {
            tier2++; //Increment ligne
        }
        
    }  

    /* Libération de la mémoire */
    free(hashAnalyse);
    free(fichierAnalyse);
    hashAnalyse = NULL;
    fichierAnalyse = NULL;

    fclose(fichier); //Fermeture du fichier
    return EXIT_SUCCESS;
}