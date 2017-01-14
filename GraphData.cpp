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

bool operator >= (std::pair<int, int> & p1, std::pair<int, int> & p2)
{
	return (p1.second >= p2.second);
}  // ----- Fin de operator >=
//----------------------------------------------------- Méthodes publiques

void GraphData::addLog(Log * l)
{
/*	if(this->e && )
	{
		
	}*/
	
	return;
}

list<pair<int, string>> GraphData::get10best() const
{
	
	list<pair<int, string>> l1;
	return l1;
}

GraphData::GraphData (bool $e, int $t) : e($e), t($t)
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <GraphData>" << endl;
#endif
} //----- Fin de GraphData

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

