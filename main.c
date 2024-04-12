#include <stdlib.h>
#include <stdio.h>
#include "saisie.h"
#include "utils.h"
#include <curses.h>
#include <string.h>
#include <unistd.h>

Table_hachage dict_personnel;
Table_hachage dict_fr;
int mode_prediction = 0;

void menu();
void red ();
void white();
void purple();
void blue();
void outputcolor();
void menu1();
void menu2(Table_hachage *dict_fr,Table_hachage *dict_personnel);
void menu4(Table_hachage *dict_personnel);
void menu3(Table_hachage *dict_personnel);
void menu5();

void red () {
  printf("\033[1;31m");
}

void white() {
  printf("\033[0;37m");
}

void purple() {
  printf("\033[0;32m");
}

void blue() {
  printf("\033[0;36m");
}

void outputcolor(){
  printf("\033[0;35m");
}

void menu(){
    int mode = 0;
    while(1){
        printf("\n");
        printf("  -----------------------------------------------\n");
        printf("  |\t");
        purple();
        printf(" PROGRAMME DE SAISIE INTUITIVE        ");
        white();
        printf("  |\n");
        printf("  -----------------------------------------------\n");
        printf("  |\t");
        blue();
        printf("     --- Menu Principal ---           ");
        white();
        printf("  |\n");
        printf("  |                                             |\n");
        printf("  |  1 : Accéder au clavier avec prédiction     |\n");
        printf("  |  2 : Afficher les mots d'un dictionnaire    |\n");
        printf("  |  3 : Ajouter un mot                         |\n");
        printf("  |  4 : Supprimer un mot                       |\n");
        printf("  |  5 : Paramétrer la prédiction               |\n");
        printf("  |  6 : Quitter le programme                   |\n");
        printf("  |                                             |\n");
        printf("  -----------------------------------------------\n");
        blue();
        printf("\t    --- Choisir une option ---\n");
        outputcolor();
        printf(">>> ");
        white();
        scanf("%d",&mode);
        switch(mode){
            case 1:
                menu1();
                break;
            case 2:
                menu2(&dict_fr,&dict_personnel);
                break;
            case 3:
                menu3(&dict_personnel);
                break;
                break;
            case 4:
                menu4(&dict_personnel);
                break;
            case 5:
                menu5();
                break;
            case 6:
                red();
                printf("Fermeture du programme\n");
                white();
                printf("\n");
                goto fin;
            default:
                red();
                printf("ERREUR: Cette opération n'est pas valable\n");
                white();
                break;

        }
    }
    fin: ;

}

void menu1(){
    char **pred = (char**) malloc(sizeof(char*)*100000);
    char str[100] = "";
    char tmp[25] = "";
    initscr();
    cbreak();
    noecho();
    printw("\n\n  --- Ecrivéz votre message, pour sortir appuyer sur chap ---\n\n");
    printw(" ------------------------------------------------------------------\n");
    int ch;
    do {
    ch = getch();
    concatener_string_char(str,ch);
    concatener_string_char(tmp,ch);
    if(ch==127)
        enlever_dernier_caractère(str);
    if(ch == ' ')
        strcpy(tmp,recupere_dernier_mot_avant_espace(str));
    if(ch == '1')
    {
        strcpy(tmp,pred[0]);
        remplacer_dernier_mot(str,pred[0]);
    }
    if(ch == '2')
    {
        strcpy(tmp,pred[1]);
        remplacer_dernier_mot(str,pred[0]);
    }
    if(ch == '3')
    {
        strcpy(tmp,pred[2]);
        remplacer_dernier_mot(str,pred[0]);
    }
    pred = prediction(&dict_personnel,&dict_fr,tmp,mode_prediction);
    printw("\r %s  :  | %-20s | %-20s | %-20s |",str,pred[0],pred[1],pred[2]);
    refresh();  
    } while (ch != 27);
    mettre_a_jour_mot_utilises(&dict_personnel,str);
    endwin();
    
}

void menu2(Table_hachage *dict_fr,Table_hachage *dict_personnel){
    int choix = 0;
    while(1){
        printf("\n");
        printf("  -----------------------------------------------\n");
        printf("  |     Afficher les mots d'un dictionnaire     |\n"); 
        printf("  -----------------------------------------------\n");
        printf("  |  1 : Dictionnaire francais                  |\n");
        printf("  |  2 : Dictionnaire personnel                 |\n");
        printf("  |  3 : Retour au menu principal               |\n");
        printf("  -----------------------------------------------\n");
        printf("\n");
        blue();
        printf("\t    --- Choisir une option ---\n");
        outputcolor();
        printf(">>> ");
        white();
        scanf("%d",&choix);
        switch(choix){
            case 1:
                montrer_dictionnaire(dict_fr);
                break;
            case 2:
                montrer_dictionnaire(dict_personnel);
                break;
            case 3:
                goto fin2;
                break;
            default:
                red();
                printf("ERREUR: Cette opération n'est pas valable\n");
                white();
                break;
        }
    }
    fin2: ;
}

void menu4(Table_hachage *dict_personnel){
    char mot__a_supprimer[LONGUEUR_MOT];
    int choix = 0;
    while(1){
        printf("\n");
        printf("  -----------------------------------------------\n");
        printf("  |                  Supprimer                  |\n"); 
        printf("  -----------------------------------------------\n"); 
        printf("  |  1 : Supprimer un mot                       |\n");
        printf("  |  2 : Revenir au menu principal              |\n");
        printf("  -----------------------------------------------\n"); 
        blue();
        printf("\t    --- Choisir une option ---\n");
        outputcolor();
        printf(">>> ");
        white();
        scanf("%d",&choix);
        switch(choix){
            case 1:
                blue();
                printf("\t    --- Mot à supprimer ---\n");
                outputcolor();
                printf(">>> ");
                white();
                scanf("%s",mot__a_supprimer);
                supprimer_de_table(dict_personnel,mot__a_supprimer);
                break;
            case 2:
                goto fin4;
                break;
            default:
            red();
            printf("ERREUR: Cette opération n'est pas valable\n");
            white();
            break;
        }
    }
    fin4: ;
}

void menu3(Table_hachage *dict_personnel){
    char mot__a_ajouter[LONGUEUR_MOT];
    int choix = 0;
    while(1){
        printf("\n");
        printf("  -----------------------------------------------\n");
        printf("  |                  Ajouter                    |\n"); 
        printf("  -----------------------------------------------\n"); 
        printf("  |  1 : Ajouter un mot                         |\n");
        printf("  |  2 : Revenir au menu principal              |\n");
        printf("  -----------------------------------------------\n"); 
        blue();
        printf("\t    --- Choisir une option ---\n");
        outputcolor();
        printf(">>> ");
        white();
        scanf("%d",&choix);
        switch(choix){
            case 1:
                blue();
                printf("\t    --- Mot à ajouter ---\n");
                outputcolor();
                printf(">>> ");
                white();
                scanf("%s",mot__a_ajouter);
                if (mot_dans_dictionnaire(dict_personnel, mot__a_ajouter)==1){
                    red();
                    printf("ERREUR: Cemot existe déjà\n");
                    white();
                    break;
                }
                inserer_dans_table(dict_personnel,mot__a_ajouter);
                break;
            case 2:
                goto fin3;
                break;
            default:
            red();
            printf("ERREUR: Cette opération n'est pas valable\n");
            white();
            break;
        }
    }
    fin3: ;
}

void menu5(){
     int choix = 0;
    while(1){
        printf("\n");
        printf("  -----------------------------------------------\n");
        printf("  |                  Paramères                  |\n"); 
        printf("  -----------------------------------------------\n"); 
        printf("  |  1 : Prédiction selon la fréquence          |\n");
        printf("  |  2 : Prédiction selon la date               |\n");
        printf("  |  3 : Revenir au menu principal              |\n");
        printf("  -----------------------------------------------\n"); 
        blue();
        printf("\t    --- Choisir une option ---\n");
        outputcolor();
        printf(">>> ");
        white();
        scanf("%d",&choix);
        switch(choix){
            case 1:
                mode_prediction = 0;
                printf("La prédiction par fréquence est activée\n");
                break;
            case 2:
                printf("La prédiction par date est activée\n");
                break;
            case 3:
                goto fin5;
                break;
            default:
            red();
            printf("ERREUR: Cette opération n'est pas valable\n");
            white();
            break;
        }
    }
    fin5: ;
}


int main() {
    printf("\n");
    printf("+Initialisation du programme \n");
    initialiser_table(&dict_personnel);
    initialiser_table(&dict_fr);
    sleep(0.5);
    printf("...Ok\n");
    sleep(0.5);
    printf("+Importation des dictionnaires\n");
    importer_mot(&dict_personnel,"mots_courants.txt");
    importer_mot(&dict_fr,"liste_francais.txt");
    sleep(0.5);
    printf("...Ok\n");
    sleep(0.5);
    printf("+Demarrage du programme\n");
    sleep(0.5);
    menu();
    return 0;
}


