#include "table.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void concatener_string_char(char* str,char c){
    char tmp[2];
    tmp[0] = c;
    tmp[1] = '\0';
    strcat(str,tmp);

}

void enlever_dernier_caractère(char* str){
     size_t len = strlen(str);
    if (len>0) {
        str[len-2] = '\0';
    }
}

char* recupere_dernier_mot_avant_espace(char* str){
    char* last_space = strrchr(str, ' ');
    if (last_space == NULL) {
        return str;
    } else {
        return last_space + 1;
    }
}

void mettre_a_jour_mot_utilises(Table_hachage *table, char* str){
    char* token = strtok(str, " ");
    while (token != NULL) {
        changer_donnees(table,str);
        token = strtok(NULL, " ");
    }
}

void remplacer_dernier_mot(char* str, char* mot){
    if(strchr(str, ' ')!=NULL)
    {
        char* last_space = strrchr(str, ' ');
        if (last_space == NULL) {
            concatener_string_char(mot,' ');
            strcpy(str, mot);
        } else {
            strcpy(last_space + 1, mot);
        }
    }
    else
    {
        strcpy(str,mot);
    }
}
