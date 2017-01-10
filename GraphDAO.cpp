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
//------------------------------------------------------ Include personnel
#include "GraphData.h"
#include "GraphDAO.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void serialize(GraphData & gd)
{
	return;
}//------ Fin de serialize


GraphDAO::GraphDAO (string $filename) : filename($filename)
{
	#ifdef MAP
		cout << "Appel au constructeur par défaut de <GraphDAO>" << endl;
	#endif
}//----- Fin de GraphDAO


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

