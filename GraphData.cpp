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
#include <map>
#include <unordered_map>
#include <string>
//------------------------------------------------------ Include personnel
#include "Log.h"
#include "GraphData.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void GraphData::addLog(Log * l)
{
	return;
}

multimap<int, string> GraphData::get10best() const
{
	multimap<int, string> m1;
	return m1;
}

GraphData::GraphData (bool $e, int $t) : e($e), t($t)
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <GraphData>" << endl;
#endif
} //----- Fin de GraphData




//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

