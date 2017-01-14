/*************************************************************************
                           GraphData  -  Classe rassemblant les données dans des structures adaptées (place mémoire, temps CPU)
                             -------------------
    début                : 10/01/2017
    copyright            : (C) 2017 Lucas POISSE - Benoît ZHONG
    e-mail               : poisse.lucas@gmail.com
*************************************************************************/

//---------- Interface de la classe <GraphData> (fichier GraphData.h) ----------------
#if ! defined ( GRAPHDATA_H )
#define GRAPHDATA_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include <unordered_map>
#include <set>
#include <string>
#include <list>
#include "Log.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <GraphData>
//
// Classe rassemblant les données utilisées par l'application dans des structures de recherche et d'insertion adaptées 
//------------------------------------------------------------------------

class GraphData
{
//----------------------------------------------------------------- PUBLIC

public: 
//----------------------------------------------------- Méthodes publiques

	void addLog(Log* l);
	// Mde : ajoute un log (ou non, en fonction des paramètres de filtrage) aux structures de données du graphe.
	// Contrat : le log doit être non null !
	
	list<pair<int, string>> get10best() const;
	//Mde: renvoie une liste correspondant aux 10 ressources les plus consultées. 
	//La liste comporte des éléments faisant correspondre une URL à un entier correspondant au nombre total de hits sur cette cible
	//La liste est ordonnée en fonction de ce nombre total, du plus grand au plus petit.
	//Elle comporte au maximum 10 éléments

    GraphData (bool $e = false, int $t=-1);
    // Mode d'emploi : Constructeur par défaut de GraphData


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

private:			//Attributs privés
	
	unordered_map<int, string> id2Url;	   //Structure MAP comportant l'identifiant et le string de l'URL (l'id est une clé)
	unordered_map<int, pair<unordered_map<int, int>, int>> id2Referers;   //Structure MAP comportant l'identifiant de l'URL et les détails de ses referers
	unordered_map<string, int> url2id;			//Structure MAP comportant le string et l'identifiant de l'URL (le string est une clé)
	set <pair<int, int>> urlAndHits;				//Structure SET permettant de stocker des paires de valeurs (id URL, nombre de hits)
	
			//  => TODO : surcharge des opérateurs > / >= sur le set <int, int> => permet de ranger la collection selon la valeur du 2ème élément (nombre de hits)
	
	bool e;		//Booléen passant à vrai si on souhaite éviter les JS/CSS/Images
	int t; 		//Entier correspondant à l'heure de filtrage, si elle est renseignée (-1 étant une valeur incorrecte)
};

bool operator > (std::pair<int, int> & p1, std::pair<int, int> & p2);  
//Surcharge de l'opérateur > pour le type pair<int, int> : renvoie vrai si la seconde composante de
// la première paire est plus grande que la seconde composante de la seconde paire

bool operator >= (std::pair<int, int> & p1, std::pair<int, int> & p2);
//Surcharge de l'opérateur > pour le type pair<int, int> : renvoie vrai si la seconde
// composante de la première paire est plus grande ou égale à la seconde composante de la seconde paire


struct Sup_pair_cmp {
	bool operator () (std::pair<int, int>  p1, std::pair<int, int>  p2)
	{
		return (p1.second >= p2.second);
	}  // ----- Fin de operator ()
};	

//Définition d'un foncteur permettant au set<pair<int, int>> de pouvoir établir une relation d'ordre entre ses éléments,
// basée sur la seconde composante de la paire

//-------------------------------- Autres définitions dépendantes de <GraphData>

#endif // GRAPHDATA_H

