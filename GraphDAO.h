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
	
	template<typename idType, typename contentType, typename linkType>
	void serialize(unordered_map<idType, contentType> & id2Content, 
					unordered_map<idType, unordered_map<idType, linkType>> &  id2Nodes, string nomFichier);
	// Mode d'emploi : méthode générique permettant de générer un graphe (fichier au format GraphViz).
	// Le premier paramètre (id2Content) est une map associant à un identifiant de type idType un contenu de type contentType (noeud du graphe).
	// Cette map permet de gérer le stockage en mémoire des éléments sans multiplier inutilement les valeurs des noeuds.
	// Le second paramètre est une autre map associant à pour chaque noeud une map de ses prédécesseurs sous la forme <idPredecesseur, valeur de l'arc (de type contentType)>
	// (qui sont donc également des successeurs potentiels d'autres noeuds). 
	// Le troisième paramètre est le string du nom du fichier dans lequel enregistrer le fichier GraphViz.
	

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

