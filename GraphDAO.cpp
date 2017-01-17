/*************************************************************************
                           GraphDAO  -  Classe lisant dans le fichier pour instancier un objet LOG
                             -------------------
    début                : 10/01/2017
    copyright            : (C) 2017 Lucas POISSE - Benoît ZHONG
    e-mail               : poisse.lucas@gmail.com
*************************************************************************/

//---------- Réalisation de la classe <GraphDAO> (fichier GraphDAO.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <string>
#include <iostream>
#include <fstream>
#include <list>
//------------------------------------------------------ Include personnel
#include "GraphData.h"
#include "GraphDAO.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
/*
void serialize(list<pair<int, string>> & l)
{
	return;
}//------ Fin de serialize*/


GraphDAO::GraphDAO (string $filename) : filename($filename)
{
	#ifdef MAP
		cout << "Appel au constructeur par défaut de <GraphDAO>" << endl;
	#endif
}//----- Fin de GraphDAO

template<typename idType, typename contentType, typename linkType> void GraphDAO::serialize(unordered_map<idType, contentType> & id2Content, 
					unordered_map<idType, unordered_map<idType, linkType>> &  id2Nodes, string nomFichier)
{
	//si 0 noeuds, afficher msg erreur
	if(id2Content.empty())
	{
		cerr << "La map est vide" << endl;
		return;
	}

	//check si le fichier existe deja : si oui faire un menu
	ifstream is_read;
	is_read.open(nomFichier.c_str());

	if(is_read.is_open() && is_read)
	{
		cout << "Le fichier existe déjà." << endl;
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
	os.open(nomFichier.c_str());
	
	//check si le fichier ouvert en écriture
	if(!os)
	{
		cerr << "Fichier non ouvert en écriture" << endl;
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
}//----- Fin de serialize

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

