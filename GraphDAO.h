/*************************************************************************
                           GraphDAO  -  Classe chargée de l'écriture du graphe des visites dans un format GraphViz.
                             -------------------
    début                : 10/01/2017
    copyright            : (C) 2017 Lucas POISSE - Benoît ZHONG
    e-mail               : poisse.lucas@gmail.com
	
*************************************************************************/

//---------- Interface de la classe <GraphDAO> (fichier GraphDAO.h) ----------------
#if ! defined ( GraphDAO_H )
#define GraphDAO_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "GraphData.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <GraphDAO>
//
//	Classe chargée de l'écriture du graphe des visites dans un format GraphViz.
//------------------------------------------------------------------------

class GraphDAO
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques
   GraphDAO(string $filename="");
    // Mode d'emploi : Constructeur par défaut de GraphDAO.
	
	void serialize(list<pair<int, string>> & l);
	//Sérialise les données de la liste passée en paramètre au format GraphViz.
	//Cette liste contient au maximum 10 paires <URL, nbTotalHits> rangés suivant le nombre total de hits dans l'ordre décroissant.
	

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

private:			//Attributs privés

	string filename;  //LE nom du fichier GraphViz
	ofstream os;	//Le flux de sortie sur lequel écrire le fichier.
};

//-------------------------------- Autres définitions dépendantes de <GraphDAO>

#endif // GraphDAO_H

