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
#include <vector>
#include <fstream>
#include <utility>

#include "Log.h"
#include "Heure.h"
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

	void AddLog(Log* l);
	// Mde : ajoute un log (ou non, en fonction des paramètres de filtrage) aux structures de données du graphe.
	// Contrat : le log doit être non null !
	
	list<pair<int, string>> Get10best() const;
	//Mde: renvoie une liste correspondant aux 10 ressources les plus consultées. 
	//La liste comporte des éléments faisant correspondre une URL à un entier correspondant au nombre total de hits sur cette cible
	//La liste est ordonnée en fonction de ce nombre total, du plus grand au plus petit.
	//Elle comporte au maximum 10 éléments

    GraphData (bool $e = false, Heure $t=Heure());
    // Mode d'emploi : Constructeur par défaut de GraphData

    void GenerateGraphViz(string nomFichier);
    // Mode d'emploi : génère le fichier au format GraphViz
	
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

private:			//Attributs et fonctions privés
	
	int getReferer(string referer);
	
	vector<string> id2Url;	   //Structure tableau comportant l'identifiant et le string de l'URL
	unordered_map<int, unordered_map<int, int>> id2Referers;   //Structure MAP comportant l'identifiant de l'URL et les détails de ses referers
	unordered_map<string, int> url2id;			//Structure MAP comportant le string et l'identifiant de l'URL (le string est une clé)
	unordered_map<int, int> id2Totalhits;		//Structure MAP comportant l'ID de la cible associé à son nombre total de hits
	set <pair<int, int>, std::greater<pair<int, int>>> urlAndHits;				//Structure SET permettant de stocker des paires de valeurs (id URL, nombre de hits)
	
		
	bool ignoreExtensions;		//Booléen passant à vrai si on souhaite éviter les JS/CSS/Images
	Heure time; 		//Heure correspondant à l'heure de filtrage, si elle est renseignée. Si l'heure est égale à 24 (construction par défaut de la structure Heure) 
						//alors le paramètre n'est pas pris en compte (champ heure compris entre 23 et 24).
};

//-------------------------------- Autres déclarations dépendantes de <GraphData>
bool operator > (std::pair<int, int> & p1, std::pair<int, int> & p2);  
//Surcharge de l'opérateur > pour le type pair<int, int> : renvoie vrai si la seconde composante de
// la première paire est plus grande que la seconde composante de la seconde paire

bool operator < (std::pair<int, int> & p1, std::pair<int, int> & p2); 
//Surcharge de l'opérateur < pour le type pair<int, int> : renvoie vrai si la seconde
// composante de la première paire est plus inférieure à la seconde composante de la seconde paire

bool operator >= (std::pair<int, int> & p1, std::pair<int, int> & p2);
//Surcharge de l'opérateur > pour le type pair<int, int> : renvoie vrai si la seconde
// composante de la première paire est plus grande ou égale à la seconde composante de la seconde paire

#endif // GRAPHDATA_H

