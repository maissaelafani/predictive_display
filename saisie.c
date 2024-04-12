#include "saisie.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


char** prediction(Table_hachage *table,Table_hachage *dict,char* clavier,int mode){
    char** res = (char**) malloc(sizeof(char*)*3);
    long long index = 0;
    int n = strlen(clavier);
    Mot** predictions = (Mot**) malloc(sizeof(Mot*)*100000);
    Mot *mot;
    for(long long k=0;k<M;k++)
    {   
        if(table->liste_mot[k] != NULL)
        {   
            mot = table->liste_mot[k];
            while(mot != NULL)
            {
                if(strlen(mot->contenu)>=n)
                {
                    if(strncmp(mot->contenu,clavier,n) == 0){
                        predictions[index] = mot;
                        index ++;
                    }
                    
                }
                mot=mot->suivant;
            }
        }
    }
    if(index<3)
    {   
        int mot_manquants = 3-index;
        index = ajouter_mot_manquant_dictionnaire_francais(dict,clavier,predictions,index,mot_manquants);
        res[0] = predictions[0]->contenu;
        res[1] = predictions[1]->contenu;
        res[2] = predictions[2]->contenu;
        return res;
    }
    if(mode == 0)
    {
        tri_decroissant_frequence(predictions,index);
        res[0] = predictions[0]->contenu;
        res[1] = predictions[1]->contenu;
        res[2] = predictions[2]->contenu;
        return res;
    }
    tri_decroissant_date(predictions,index);
    res[0] = predictions[0]->contenu;
    res[1] = predictions[1]->contenu;
    res[2] = predictions[2]->contenu;
    return res;
    
}

long long ajouter_mot_manquant_dictionnaire_francais(Table_hachage *dict,char* clavier, Mot** predictions,int index,int n){
    int mot_restants = n;
    int rang = index;
    Mot *mot;
    for(long long k=0;k<M;k++)
    {
        if(dict->liste_mot[k] != NULL)
        {
            mot = dict->liste_mot[k];
            while(mot != NULL)
            {
                if(strlen(mot->contenu)>=n)
                {
                    if(strncmp(mot->contenu,clavier,n) == 0){
                        predictions[rang] = mot;
                        rang++;
                        mot_restants--;
                        if(mot_restants==0)
                            return rang;
                    }
                    
                }
                mot = mot->suivant;
            }
        }
    }
    return rang;
}

void tri_decroissant_frequence(Mot** predictions,long long index){
    Mot *temp;
    for (int i=0; i<index-1; i++) {
        for (int j=i+1;j<index;j++) {
            if (predictions[i]->frequence < predictions[j]->frequence) {
                temp = predictions[i];
                predictions[i] = predictions[j];
                predictions[j] = temp;
            }
        }
    }
}

void tri_decroissant_date(Mot** predictions,long long index){
    Mot *temp;
    for (int i=0; i<index-1; i++) {
        for (int j=i+1;j<index;j++) {
            if (predictions[i]->date < predictions[j]->date) {
                temp = predictions[i];
                predictions[i] = predictions[j];
                predictions[j] = temp;
            }
        }
    }
}
