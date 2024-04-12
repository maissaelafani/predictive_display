#include "table.h"
char** prediction(Table_hachage *table,Table_hachage *dict,char* clavier,int mode);
long long ajouter_mot_manquant_dictionnaire_francais(Table_hachage *dict,char* clavier, Mot** predictions,int index,int n);
void tri_decroissant_frequence(Mot** predictions,long long index);
void tri_decroissant_date(Mot** predictions,long long index);
