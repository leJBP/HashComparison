// gcc -Wall -pedantic verifHash.c -o verifHash -lcrypto -lssl

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <openssl/md5.h>

/* Création des variables globales */
int ligne; //Ligne de début analyse fichier
int nbLigne; //Nombre ligne fichier a analyser
char* motTrouve; //Mot trouvé
int ligneTrouve; //Numéro de la ligne ou se situe le mot trouvé
char* hashAnalyse; //Hash a trouvé dans le fichier
FILE* fichier; //Pointeur fichier ouverture
char* fichierAnalyse; //Buffer nom du fichier à analyser
char* contenuFichier; //Buffer de lecture ligne à ligne
struct stat sb;
unsigned char hashMot[MD5_DIGEST_LENGTH]; //Buffer hash fonction md5
char hashConv[2*MD5_DIGEST_LENGTH+1] = ""; //Buffer hash après conversion de uchar en char

/**
 * @brief Display the result of the analysis
 * @param ligne 
 * @param mot 
 */
void affichageResultat(int ligne, char* mot, char* hashTrouve){
    if (ligne == -1){
        printf("Pas de correspondance trouvé dans le fichier");
    }
    else {
        printf("\n=== MOT TROUVE ===\n");
        printf("Hash trouvé : %s\n",hashTrouve);
        printf("Hash d'analyse : %s\n", hashAnalyse);
        printf("Mot associé : %s\n", mot);
        printf("Ligne du mot dans le fichier : %d\n\n", ligne);
    }  
}

/**
 * @brief Display the manual 
 * @param prog 
 */
void afficherNotice(char* prog){
    printf("Les arguments entrés sont invalides\n\n");
    printf("Méthodologie : \n");
    printf("\tAppel : %s fichierAnalyse hashAnalyse typeHash -f/-l\n", prog);
    printf("\t-f : hash du fichier\n");
    printf("\t-l : Hash ligne à ligne du fichier\n");
}

/**
 * @brief Detect which hash type is selected 
 * @param hashType 
 * @param prog
 */
void hashSelect(char* prog, char* hashType){
    afficherNotice(prog);
}

// ./verifhash fichier hash typeHash -f/-l
int main(int argc, char* argv[]){

    /* Test du bon appel du script */
    if (argc != 5){
        afficherNotice(argv[0]);
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
    } else if (strcmp(argv[4], "-l")){
        printf("Mode invalide veuillez suivre la notice : \n");
        afficherNotice(argv[0]);
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
    nbLigne = 1434439;

    ligne = 1;

    int finAnalyse = 0;

    while (fscanf(fichier, "%[^\n] ", contenuFichier) != EOF && !finAnalyse) {        

        //printf("Pere : %s\n", contenuFichier);
        //printf("Ligne %d\n", tier2);
        MD5((const unsigned char *)contenuFichier, strlen(contenuFichier), hashMot);

        /* Conversion unsigned char -> char */
        for (int i=0; i < MD5_DIGEST_LENGTH; i++) {
            sprintf(hashConv + 2*i, "%02x", hashMot[i]);
        }

        if (!strcmp(hashAnalyse, hashConv)){
            finAnalyse = 1;
            affichageResultat(ligne, contenuFichier, hashConv);
        } else {
            ligne++; //Increment ligne
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
