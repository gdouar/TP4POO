/*************************************************************************
                           GraphData  -  Classe rassemblant les données dans des structures adaptées (place mémoire, temps CPU)
                             -------------------
    début                : 10/01/2017
    copyright            : (C) 2017 Lucas POISSE - Benoît ZHONG
    e-mail               : poisse.lucas@gmail.com
*************************************************************************/

//---------- Réalisation de la classe <GraphData> (fichier GraphData.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
//------------------------------------------------------ Include personnel
#include "Log.h"
#include "GraphData.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//---------------------------------------------- Surcharges des opérateurs

bool operator > (std::pair<int, int> & p1, std::pair<int, int> & p2)
{
	return (p1.second > p2.second);
}  // ----- Fin de operator >

bool operator < (std::pair<int, int> & p1, std::pair<int, int> & p2)
{
	return (p1.second > p2.second);
}  // ----- Fin de operator >


bool operator >= (std::pair<int, int> & p1, std::pair<int, int> & p2)
{
	return (p1.second >= p2.second);
}  // ----- Fin de operator >=
//----------------------------------------------------- Méthodes publiques

void GraphData::AddLog(Log * l)
{
//Algorithme : le but est, dans un premier temps, de retrouver ou d'enregistrer la correspondance cible/idCible de la ligne de log via
// les maps id2URL et url2Id. Par la suite, on identifie la cible dans la map id2Referers. Si elle existe, on ajoute ou modifie le referer
//associé à la ligne de log, ainsi que le nombre total de hits de la cible. Enfin, on insère ou modifie une entrée dans le set ordonné de paires
// <idCible, nbTotalHits> urlAndHits pour maintenir la cohérence entre les deux structures de données.

	string cible = l->cible;
	// cout << endl << "Cible = " << cible << endl;
	int idCible;
	if (url2id.find(cible) == url2id.end())					//Si la cible n'existe pas dans les maps des URLs existantes, on l'ajoute
	{
		idCible = url2id.size();
		url2id.insert(make_pair(cible, idCible));
		id2Url.insert(make_pair(idCible, cible));
		// cout << "URL cible insérée. " << endl;
	}
	else
	{
		idCible = (*(url2id.find(cible))).second;				//Si elle existe, on accède à son identifiant entier
		// cout << "URL cible retrouvée. " << endl;
	}
	
	unordered_map<int, pair<unordered_map<int, int>, int>> :: iterator it;		//Pointeur sur la structure id2Referers
	int idReferer = getReferer(l->ref);						//Identifiant du referer associé
	if(((it = id2Referers.find(idCible)) != id2Referers.end()))		// Si l'URL est une cible déjà existante...
	{
		// cout << "Cible spécifique retrouvée. " << endl;
		int previousHits = ((*it).second).second;		//...on retrouve l'ancien total de Hits à partir de l'idCible pour identifier la bonne paire
		unordered_map<int, int>* map = &(((*it).second).first);		//Pointeur sur la map existante affectée à l'identifiant idCible dans id2Referers
		unordered_map<int, int>::iterator itReferer;
		if((itReferer = map->find(idReferer)) != map->end())	//Si on a trouvé le referer associé dans la map, 
																		//on incrémente son nombre associé de hits
		{
			// cout << "Referer déjà associé";
			(*itReferer).second++;
		}
		else
		{
			// cout << "Referer non déjà associé";				
			map->insert(make_pair(idReferer, 1));		//Sinon, on insère une nouvelle entrée dans la sous-map de id2Referers
		}
		((*it).second).second++;				//Dans tous les cas, le nombre total de hits est incrémenté.
		
		urlAndHits.erase(make_pair(idCible, previousHits));
									//On modifie la correspondance dans le set ordonné de paires <id, nbTotalHits>
		urlAndHits.insert(make_pair(idCible, ++previousHits));
	}
	else {
		// cout << "Cible spécifique insérée";
		unordered_map<int, int> m;		//Si la cible n'existe pas encore, on ajoute une nouvelle entrée à id2Referers
		m.insert(make_pair(idReferer, 1));		//Définition de la map (premier élément de la paire de id2Referers)
		id2Referers.insert(make_pair(idCible, make_pair(m, 1)));		//Ajout d'une nouvelle entrée à id2Referers. Le nombre total de hits est de 1.
																	//Le nombre de hits total est forcément de 1 pour la nouvelle cible
		urlAndHits.insert(make_pair(idCible, 1));
	}
	
	delete l;
	return;
}

list<pair<int, string>> GraphData::get10best()
{

	list<pair<int, string>> l1; 
	int cpt=0;
	for(set <pair<int, int>>::iterator it=urlAndHits.begin();it!=urlAndHits.end() && cpt<=10;++it, ++cpt)
	{
		
		int idURL = (*it).first;
		string url = (*(id2Url.find(idURL))).second;
		l1.push_back(make_pair((*it).second, url)); 
		cout << (*it).first << " - " << (*it).second << endl;
	}
	return l1;
}  // ------------------ Fin de get10best

GraphData::GraphData (bool $e, unsigned int $t) : ignoreExtensions($e), time($t)
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <GraphData>" << endl;
#endif
} //----- Fin de GraphData

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées


// ---------------------------------------------------- Méthodes privées

int GraphData::getReferer(string referer) 
{
	unordered_map<string, int> ::iterator it = url2id.find(referer);
	
	if(it == url2id.end())
	{
		// cout << "Referer inséré";
		int idRef = url2id.size();
		url2id.insert(make_pair(referer, idRef));
		id2Url.insert(make_pair(idRef, referer));
		return idRef;
	}
	else {
		// cout << "Referer retrouvé";
		return (*it).second;
	}
	
}

