/*************************************************************************
                           GraphDAO  -  Classe chargée de l'écriture d'un graphe dans un format GraphViz.
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
//	Classe chargée de l'écriture d'un graphe dans un format GraphViz.
//------------------------------------------------------------------------

class GraphDAO
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques
   GraphDAO(string $filename="");
    // Mode d'emploi : Constructeur par défaut de GraphDAO.
	
	template <typename contentType, typename linkType>
	void serialize(vector<contentType> & id2Content, 
					unordered_map<int, unordered_map<int, linkType>> &  id2Nodes)
	// Mode d'emploi : méthode générique permettant de générer un graphe (fichier au format GraphViz).
	// Le premier paramètre (id2Content) est un vector comportant un contenu de type contentType (noeud du graphe).
	// Celui-ci permet de lister tous les contenus possibles sans avoir à multiplier inutilement des valeurs de noeuds stockées.
	// Le second paramètre est une  map associant à pour chaque noeud une map de ses prédécesseurs sous la forme <indice correspondant du tableau, valeur de l'arc (de type contentType)>
	// (qui sont donc également des successeurs potentiels d'autres noeuds). 
	{
	
		//si 0 noeuds, afficher msg erreur
		if(id2Content.empty())
		{
			cout << "Warning : aucune entrée n'a été trouvée. Aucun fichier DOT n'a donc été généré." << endl;
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
				cout << "Fichier non écrasé." << endl;
				return;
			}
			cout << "Fichier écrasé." << endl;
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
		for(typename vector<contentType>::iterator it=id2Content.begin(); it != id2Content.end(); ++it)
		{
			os << "node" << it - id2Content.begin() << " [label=\"" << *it << "\"];\r\n" ;
		}

		//declaration des liens referers / node
		for(typename unordered_map<int, unordered_map<int, linkType>>::iterator itNode = id2Nodes.begin(); itNode != id2Nodes.end(); ++itNode)
		{
			for(typename unordered_map<int, linkType>::iterator itReferers = itNode->second.begin(); itReferers != itNode->second.end(); ++itReferers)
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

