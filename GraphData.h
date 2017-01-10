/*************************************************************************
                           GraphData  -  Classe rassemblant les données dans des structures adaptées (place mémoire, temps CPU)
                             -------------------
    début                : 10/01/2017
    copyright            : (C) 2017 Lucas POISSE - Benoît ZHONG
    e-mail               : poisse.lucas@gmail.com
*************************************************************************/

//---------- Interface de la classe <Xxx> (fichier Xxx.h) ----------------
#if ! defined ( GRAPHDATA_H )
#define GRAPHDATA_H

//--------------------------------------------------- Interfaces utilisées
#include <unordered_map>
#include <multimap>
#include "Log.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <GraphData>
//
//
//------------------------------------------------------------------------

class GraphData
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes/fonctions amies

	friend class Log;

//----------------------------------------------------- Méthodes publiques

	void addLog(Log l);
	// Mde : ajoute un log (ou non, en fonction des paramètres de filtrage) aux structures de données du graphe.
	
	multimap<int, string> get10best() const;
	//Mde: renvoie une nouvelle multimap correspondant aux 10 ressources les plus consultées. Multimap = <nbHits, URL) 

//------------------------------------------------- Surcharge d'opérateurs
    GraphData & operator = ( const GraphData & unGraphData);
    // Mode d'emploi : Surcharge de l'opérateur d'affectation pour GraphData


//-------------------------------------------- Constructeurs - destructeur
    GraphData ( const GraphData & unGraphData );
    // Mode d'emploi (constructeur de copie) : Surcharge de constructeur par copie de GraphData
	
    GraphData (bool e = false, int t=-1);
    // Mode d'emploi : Constructeur par défaut de GraphData


	

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

private:			//Attributs privés
	
	unordered_map<int, String> id2Url;	   //Structure MAP comportant l'identifiant et le string de l'URL (l'id est une clé)
	unordered_map<int, pair<unordered_map<int, int>, int>> id2Referers;   //Structure MAP comportant l'identifiant de l'URL et les détails de ses referers
	unordered_map<String, int> url2id;			//Structure MAP comportant le string et l'identifiant de l'URL (le string est une clé)
	multimap<int, int> hits2id;				//Structure MultiMAP permettant de passer du nombre de 'hits' à l'identifiant de l'URL.
	bool e;		//Booléen passant à vrai si on souhaite éviter les JS/CSS/Images
	int t; 		//Entier correspondant à l'heure de filtrage, si elle est renseignée (-1 étant une valeur incorrecte)
};

//-------------------------------- Autres définitions dépendantes de <GraphData>

#endif // GRAPHDATA_H

