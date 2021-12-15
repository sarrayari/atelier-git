#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include <gtk/gtk.h>

enum
{ 
 ENOM,
     EType,
      EJour,
       EMois,
        EAnnee,
        EQD,

 COLUMNS };

int ajouter_menu(menu m)
{
int ajoutee = 0;
FILE *f=NULL;
f=fopen("menu.txt","a+") ;
if(f!=NULL)
{
fprintf(f,"%s %s %d %d %d %s \n",m.nom,m.type,m.Jour,m.Mois,m.Annee,m.qd);
ajoutee = 1 ;
}
fclose(f);
return ajoutee ;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

void afficher_menu(GtkWidget  *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char nom[20];
	char type[20];
	int  Jour;
	int Mois;
        int Annee;
	char qd[20];

	FILE *f;

	store=gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
		renderer =gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("nom",renderer, "text",ENOM,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes(" type",renderer, "text", EType,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes(" Jour",renderer, "text", EJour,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Mois",renderer, "text",EMois,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Annee",renderer, "text",EAnnee,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("qd",renderer, "text",EQD,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_INT,  G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);
	f=fopen("menu.txt","r+");
	if(f==NULL)
	{
		return;
	}
	else
	{
	 	while(fscanf(f,"%s %s %d %d %d %s \n",nom,type,&Jour,&Mois,&Annee,qd)!=EOF)	          						  
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter,ENOM,nom,EType,type,EJour,Jour,EMois,Mois,EAnnee,Annee,EQD,qd,-1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
}

/////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
int supprimer_menu(char nom[])

{
FILE *f;
FILE *tmp;
menu m;
f=fopen("menu.txt","r");

tmp=fopen("tempo.txt","a+");


  while(fscanf(f, "%s %s %d %d %d %s \n" ,m.nom ,m.type ,&m.Jour ,&m.Mois,&m.Annee,m.qd )!=EOF)
    {
	if(strcmp(m.nom,nom)!=0)
        {fprintf(tmp,"%s %s %d %d %d %s \n" , m.nom ,m.type ,m.Jour ,m.Mois,m.Annee,m.qd );
}

    }
fclose(f);
fclose(tmp);
remove("menu.txt");
rename("tempo.txt","menu.txt");
return 1;
}
//////////////////////////////////////////////////////////////////////////////////////
int modifier_menu(menu m)
{
    char nom[20];	
    char type[20];
     int jours;
    int  mois;
    int annee;
    char qd[20];
 
	

FILE *f;
FILE *tmp;

f=fopen("menu.txt","r");
tmp=fopen("menu1.txt","a+");
while (fscanf(f,"%s %s %d %d %d %s \n",nom,type,&jours,&mois,&annee,qd)!=EOF)
{
if (strcmp(m.nom,nom)==0)
	{fprintf(tmp,"%s %s %d %d %d %s \n" , m.nom ,m.type ,m.Jour,m.Mois,m.Annee,m.qd );
}
else
	fprintf(tmp,"%s %s %d %d %d %s \n",nom,type,jours,mois,annee,qd);
}
fclose(f);
fclose(tmp);
remove("menu.txt");
rename("menu1.txt","menu.txt");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rechercher_menu(GtkWidget *liste, char nommenu[])

{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char nom[20];
	char type[20];
	int  Jour;
	int Mois;
        int Annee;
	char qd[20];
	store=NULL;

	FILE *f;

	store=gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("nom",renderer, "text",ENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("type",renderer, "text", EType,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Jour",renderer, "text", EJour,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Mois",renderer, "text",EMois,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Annee",renderer, "text",EAnnee,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("qd",renderer, "text",EQD,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_INT,  G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);
	f=fopen("menu.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
	 	while(fscanf(f,"%s %s %d %d %d %s \n",nom,type,&Jour,&Mois,&Annee,qd )!=EOF)
	          	{
            if(strcmp(nom,nommenu)==0)                						  
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, ENOM,nom,EType,type,EJour,Jour,
			EMois,Mois,EAnnee,Annee,EQD,qd,-1);
		}
                 }
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
}
}

enum
{
	EJOUR1,
	ETYPE1,
	EVALEUR,
 	COLUMN};

void afficher_dechets(GtkWidget  *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	int jour1;
        int type1;
        char valeur[10];

	
        store=NULL;

	FILE *f;

	store=gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
        renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("jour1",renderer, "text",EJOUR1,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column =gtk_tree_view_column_new_with_attributes("type1",renderer,"text",ETYPE1,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" valeur",renderer, "text",EVALEUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	}

	store=gtk_list_store_new (COLUMN,G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);
	f=fopen("dechets.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("dechets.txt","a+");
	 	       while(fscanf(f,"%d %d %s \n",&jour1,&type1,valeur)!=EOF)	          						  
		 {
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EJOUR1,jour1,ETYPE1,type1,EVALEUR,valeur,-1); 
}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
}
void dechets_menu(GtkWidget*liste)

{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

    	int jour1;
        int type1;
        char valeur[10];
	float valeurf;


	store=NULL;
	FILE *f;

	store=gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("jour1",renderer, "text",EJOUR1,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column =gtk_tree_view_column_new_with_attributes("type1",renderer,"text",ETYPE1,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" valeur",renderer, "text",EVALEUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	
	store=gtk_list_store_new (COLUMN,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING);
	f=fopen("dechets.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f=fopen("dechets.txt","a+");
	 	       while(fscanf(f,"%d %d %s\n",&jour1,&type1,valeur)!=EOF)	          						  
		{
            valeurf=atof(valeur);
            
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EJOUR1,jour1,ETYPE1,type1,EVALEUR,valeur,-1); 
                 }
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
}
}
