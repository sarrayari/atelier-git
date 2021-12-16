#define CAPTEUR_H_INCLUDED
#include <gtk/gtk.h>

typedef struct
{
	char nom[20];
	char type[20];
         int  Jour;
         int Mois;
         int Annee;
	 char qd[20];

}menu;
typedef struct dechets
{
    int jour1;
    int type1;
    char valeur[10];
}dechets;

int ajouter_menu(menu m);
int supprimer_menu(char nom[]);
int modifier_menu(menu m);
int exist_menu(char *nom);
void rechercher_menu(GtkWidget *liste, char nom[]);
void afficher_menu(GtkWidget *liste);
void dechets_menu(GtkWidget *liste);
void afficher_dechets(GtkWidget  *liste);
