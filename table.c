#include "table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

long long cle_hash(char* mot){
    long long hash = 0;
    long long p_pow = 1;
    int taille_mot = strlen(mot);
    for(int i = 0; i < taille_mot; i++) 
    {
        hash = (hash + (mot[i] - 'a' + 1) * p_pow) % M;
        p_pow = (p_pow * P) % M;
    }
    return hash;
}

void initialiser_table(Table_hachage *table){
    table->taille = M;
    table->liste_mot = (Mot**) malloc(M*sizeof(Mot*));
    for(long long k=0;k<M;k++){
        table->liste_mot[k] = NULL;
    } 
}

void importer_mot(Table_hachage *table, char* fichier){
    FILE *fp;
    fp = fopen(fichier,"r");
    if(fp!=NULL)
    {
        char contenu[LONGUEUR_MOT];
        long long hash;
        Mot *mot;
        while(fscanf(fp,"%s",contenu)==1)
        {
            hash = cle_hash(contenu);
            if(hash>=0){
            mot = table->liste_mot[hash];
            //on vérifie si le mot est déja dans le dictionnaire
            if(mot_dans_dictionnaire(table,contenu)==1)
            {
                 while(mot!=NULL){
                    if(strcmp(contenu,mot->contenu)==0)
                    {
                        mot->frequence = mot->frequence + 1;
                        mot->date = time(NULL);
                        break;
                    }
                    mot = mot->suivant; 
                 }
            }
            else
            {
                //printf("non\n");
                inserer_dans_table(table,contenu);
            }
            }
        }
    }
    else
    {
        printf("Erreur lors de l'ouverture du ficheir\n");
    }
    fclose(fp);
}

int mot_dans_dictionnaire(Table_hachage *table, char* chercher){
    Mot *mot = table->liste_mot[cle_hash(chercher)];
    while(mot!=NULL)
    {
        if(strcmp(chercher,mot->contenu) == 0)
            return 1;
        mot = mot->suivant;
    }
    return 0;
}

void inserer_dans_table(Table_hachage *table,char* contenu){
    Mot *mot = (Mot*) malloc(sizeof(Mot));
    strcpy(mot->contenu,contenu);
    mot->frequence = 1;
    mot->date = time(NULL);
    long long hash = cle_hash(contenu);
    mot->suivant = table->liste_mot[hash];
    table->liste_mot[hash] = mot;
}

void supprimer_de_table(Table_hachage *table,char* contenu){
    Mot *mot;
    mot = table->liste_mot[cle_hash(contenu)];
    while(mot!=NULL)
    {
        if(strcmp(mot->contenu,contenu)==0 && mot->frequence >0)
        {   if(mot->frequence >0)
            {
                mot->frequence = 0;
                printf("Mot supprimé avec succés");
                goto exit;
                break;
            }
        }  
        mot=mot->suivant;

    }
    printf("\033[1;31m");
    printf("ERREUR : Ce mot est introuvable");
    printf("\033[0;37m");
    exit: ;
}

void montrer_dictionnaire(Table_hachage *table){
    Mot *mot;
    for(long long k=0;k<M;k++)
    {
        if(table->liste_mot[k] != NULL)
        {
            mot = table->liste_mot[k];
            while(mot != NULL)
            {   
                if(mot->frequence>0)
                    printf("%s\n",mot->contenu);
                mot = mot->suivant;
            }
        }
    }
}

void changer_donnees(Table_hachage *table,char* str){
    Mot *mot;
    if(mot_dans_dictionnaire(table,str)==1)
    {
        for(long long k=0;k<M;k++)
    {
        if(table->liste_mot[k] != NULL)
        {
            mot = table->liste_mot[k];
            while(mot != NULL)
            {   
                if(strcmp(str,mot->contenu)==0)
                {
                    mot->frequence = mot->frequence + 1;
                    mot->date = time(NULL);
                }
            }
        }
    }
    }
    
}
