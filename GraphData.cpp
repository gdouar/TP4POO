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
#include <multimap>
#include <unordered_map>
#include "Log.h"
//------------------------------------------------------ Include personnel
#include "GraphData.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void GraphData::addLog(Log l)
{
	return;
}

multimap<int, string> GraphData::get10best() const
 {
	multimap<int, string> m1;
	return m;
}


//------------------------------------------------- Surcharge d'opérateurs
GraphData & GraphData::operator = ( const GraphData & unXxx )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
GraphData::GraphData ( const GraphData & unGraphData )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <GraphData>" << endl;
#endif
} //----- Fin de GraphData (constructeur de copie)


GraphData::GraphData (bool e, int t)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <GraphData>" << endl;
#endif
} //----- Fin de GraphData


GraphData::~GraphData ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <GraphData>" << endl;
#endif
} //----- Fin de ~GraphData


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

