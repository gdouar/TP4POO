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
	
	template <typename idType, typename contentType, typename linkType>
	void serialize(unordered_map<idType, contentType> & id2Content, 
					unordered_map<idType, unordered_map<idType, linkType>> &  id2Nodes)
	// Mode d'emploi : méthode générique permettant de générer un graphe (fichier au format GraphViz).
	// Le premier paramètre (id2Content) est une map associant à un identifiant de type idType un contenu de type contentType (noeud du graphe).
	// Cette map permet de gérer le stockage en mémoire des éléments sans multiplier inutilement les valeurs des noeuds.
	// Le second paramètre est une autre map associant à pour chaque noeud une map de ses prédécesseurs sous la forme <idPredecesseur, valeur de l'arc (de type contentType)>
	// (qui sont donc également des successeurs potentiels d'autres noeuds). 
	{
		//si 0 noeuds, afficher msg erreur
		if(id2Content.empty())
		{
			cerr << "La map est vide" << endl;
			return;
		}

		//check si le fichier existe deja : si oui faire un menu
		ifstream is_read;
		is_read.open(filename.c_str());

		if(is_read.is_open() && is_read)
		{
			cout << "Warning : Le fichier existe déjà." << endl;
			cout << "L'écraser (y/n) ?" << endl;
			char str;
			cin >> str;
			if(!(str == 'y'))
			{
				is_read.close();
				return;
			}
		}
		is_read.close();

		ofstream os;
		os.open(filename.c_str());
		
		//check si le fichier ouvert en écriture
		if(!os)
		{
			cerr << "Erreur : Fichier non ouvert en écriture" << endl;
			os.close();
			return;
		}

		//ecriture du graphe
		os << "digraph {\r\n";

		//declaration des nodes
		for(typename unordered_map<idType, contentType>::iterator it=id2Content.begin(); it != id2Content.end(); ++it)
		{
			os << "node" << it->first << " [label=\"" << it->second << "\"];\r\n" ;
		}

		//declaration des liens referers / node
		for(typename unordered_map<idType, unordered_map<idType, linkType>>::iterator itNode = id2Nodes.begin(); itNode != id2Nodes.end(); ++itNode)
		{
			for(typename unordered_map<idType, linkType>::iterator itReferers = itNode->second.begin(); itReferers != itNode->second.end(); ++itReferers)
			{
				os << "node" << itReferers->first << " -> node" << itNode->first << " [label=\"" << itReferers->second << "\"];\r\n";
			}
		}

		//fin
		os << "}\r\n";
		os.close();
		return;
	}
	

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

