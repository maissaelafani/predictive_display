#include <time.h>

#define M 999983
#define LONGUEUR_MOT 30
#define P 29791

typedef struct mot{
    char contenu[LONGUEUR_MOT];
    int frequence;
    time_t date;
    struct mot *suivant;

} Mot;

typedef struct table_hachage{
    long long taille;
    Mot** liste_mot;
}Table_hachage;

long long cle_hash(char* mot);
void initialiser_table(Table_hachage *table);
int mot_dans_dictionnaire(Table_hachage *table, char* chercher);
void inserer_dans_table(Table_hachage *table,char* contenu);
void supprimer_de_table(Table_hachage *table,char* contenu);
void montrer_dictionnaire(Table_hachage *table);
void importer_mot(Table_hachage *table, char* fichier);
void changer_donnees(Table_hachage *table,char* str);
