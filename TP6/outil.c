#include <stdio.h>   /* pour les entr�es-sorties */
#include <string.h>  /* pour les manipulations de cha�nes de caract�res */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/*   Nom : Debeve                       Pr�nom :  Axel                    */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le r�pertoire stock� en m�moire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire *rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compl�ter code ici pour tableau
	int idx;

	if (rep->nb_elts < MAX_ENREG)
	{
		*(rep->tab + rep->nb_elts) = enr; // On d�finit le dernier �l�ment de la liste avec enr
		rep->nb_elts++; // On a un �l�ment de plus
		rep->est_trie = false; // La liste n'est pas tri�e
		modif = true;
		return(OK);
	}
	else {
		return(ERROR);
	}

	
#else
#ifdef IMPL_LIST
	// compl�ter code ici pour Liste
	bool inserted = false;
	if (rep->nb_elts == 0) {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}

	}
	else {
		int i = 0;
		while ((i < rep->nb_elts) && (est_sup(enr, (GetElementAt(rep->liste, i)->pers)))) { i++ }; // On augmente un compteur tant qu'on est dans la liste et que enr est sup�rieur � l'�l�ment compteur de la liste
		InsertElementAt(rep->liste, i, enr); // On ins�re l'�l�ment � l'emplacement compteur
		rep->nb_elts++; // Incr�mentation du nombre d'�l�ments
		modif = true;
		rep->est_trie = true; // Liste tri�e
		return(OK);
	}


#endif
	
#endif


	return(OK);

} /* fin ajout */
  /**********************************************************************/
  /* supprime du r�pertoire l'enregistrement dont l'indice est donn� en */
  /*   param�tre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire *rep, int indice) {

	// compl�ter code ici pour tableau
	if (rep->nb_elts >= 1)		
	{						    // S'il y a au moins un �l�ment dans le tableau et que l'indice pointe a l'interieur
		if (indice < rep->nb_elts) {
			for (int i = indice; i < rep->nb_elts - 1; i++) {
				*(rep->tab + i) = *(rep->tab + i + 1);
			}
		}
		
		rep->nb_elts -= 1;		// Dans tous les cas il y a un �l�ment en moins
		modif = true;
	}

	return;
} /* Fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du r�pertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif � vrai                              */
  /************************************************************************/
  // complet

	int supprimer_un_contact_dans_rep_liste(Repertoire *rep, SingleLinkedListElem *elem) {
	
	int ret=DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0); 
	}
#endif
#endif


  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement sur une ligne � l'�cran  */
  /* ex Dupont, Jean                 0320304050                         */
  /**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	printf("%s, %s, %s", enr.nom, enr.prenom, enr.tel); // Affichage des champs � remplir


} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	printf("\n |%-30s|%-30s|%-20s", enr.nom, enr.prenom, enr.tel); // Affichage des champs avec une pr�sentation align�e des informations
	
} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	if (_stricmp(enr1.nom, enr2.nom) > 0) {
		return(true);
	} // Comparaison des noms, "true" si le premier est le plus grand, "false" sinon.
	if (_stricmp(enr1.nom, enr2.nom) < 0) {
		return(false);
	} 
	if (_stricmp(enr1.prenom, enr2.prenom) > 0) {
		return(true);
	} // Comparaison des pr�noms, "true" si le premier est le plus grand, "false" sinon.
	if (_stricmp(enr1.prenom, enr2.prenom) < 0) {
		return(false);
	} 
}
 
/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire *rep)
{

#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	int flag = 1; // flag servant � compter le nombre de permutations par boucle
	while (flag != 0) { // Tant que le tableau n'est pas tri�, on continue
		flag = 0; 
		for (int i = 0; i < rep->nb_elts - 1; i++) {
			if (est_sup(*(rep->tab + i), *(rep->tab + i + 1))) { // Permutation si un �l�ment est sup�rieur au suivant
				Enregistrement tmp = *(rep->tab + i);
				*(rep->tab + i) = *(rep->tab + i + 1);
				*(rep->tab + i + 1) = tmp;
				flag++;
			}
		}
	}

	


	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien � faire !
	// la liste est toujours tri�e
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le r�pertoire d'un enregistrement correspondant au  */
  /*   nom � partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au crit�re ou*/
  /*   un entier n�gatif si la recherche est n�gative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire *rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de d�but de recherche dans tableau/liste rep */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;		


#ifdef IMPL_TAB
	strcpy_s(tmp_nom, MAX_NOM, nom); // Copie du nom dans une variable locale
	_strupr_s(tmp_nom, _countof(tmp_nom)); // Mise en majuscule 
	ind_fin = rep->nb_elts; // On s'arr�te � la fin du tableau
	for (int i = ind; i < ind_fin; i++) {
		strcpy_s(tmp_nom2, MAX_NOM, rep->tab + i); // On recopie chaque �l�ment du tableau dans une variable temporaire
		_strupr_s(tmp_nom2, _countof(tmp_nom2)); // Mise en majuscule
		if (strcmp(tmp_nom, tmp_nom2) == 0) {
			return i; // On retourne l'indice quand les noms sont �gaux
		}
	}
							// ajouter code ici pour tableau
	
#else
#ifdef IMPL_LIST
							// ajouter code ici pour Liste
	
#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non num�riques de la chaines        */
  /*********************************************************************/
void compact(char *s)
{
	char tab[MAX_TEL]; //
	int j = 0; //
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			tab[j] = s[i];
			j++;
		}
	}
	tab[j] = "\0"; //
	strcpy_s(s, MAX_TEL, tab);
	return;
	// compl�ter code ici
}

/**********************************************************************/
/* sauvegarde le r�pertoire dans le fichier dont le nom est pass� en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionn� ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
#ifdef IMPL_TAB
	errno_t err = fopen_s(&fic_rep, nom_fichier, "w"); // Ouverture du fichier et stockage de la valeur de retour dans err
	if (err != 0) {
		return(ERROR);
	}
	char buffer[MAX_NOM + MAX_NOM + MAX_TEL + 2]; // On r�serve de l'espace pour nom, pr�nom, t�l et les s�parateurs dans une variable temporaire
	for (int i = 0; i < rep->nb_elts; i++) { // Le fichier �tant d�truit � l'ouverture, il faut tout r��crire
		sprintf_s(buffer, MAX_NOM + MAX_NOM + MAX_TEL + 2, "%s%c%s%c%s\n", (rep->tab + i)->nom, SEPARATEUR, (rep->tab + i)->prenom, SEPARATEUR, (rep->tab + i)->tel);
		fputs(buffer, fic_rep); // On �crit la ligne dans un fichier
	}
									// ajouter code ici pour tableau
	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le r�pertoire le contenu du fichier dont le nom est  */
  /*   pass� en argument                                                */
  /*   retourne OK si le chargement a fonctionn� et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char *char_nw_line;
	
	_set_errno(0);
	if ( ((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL) )
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element � priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
														// ajouter code implemention liste
#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */