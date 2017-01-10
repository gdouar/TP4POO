/*************************************************************************
                           LogDAO  -  Classe lisant dans le fichier pour instancier un objet LOG
                             -------------------
    début                : 10/01/2017
    copyright            : (C) 2017 Lucas POISSE - Benoît ZHONG
    e-mail               : poisse.lucas@gmail.com
*************************************************************************/

//---------- Réalisation de la classe <LogDAO> (fichier LogDAO.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <string>
#include <iostream>
#include <fstream>
//------------------------------------------------------ Include personnel
#include "Log.h"
#include "LogDAO.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Log* LogDAO::getNextLog()
{
	return nullptr;
}//----- Fin de getNextLog

LogDAO::LogDAO (ifstream  & $is) : is($is)
{
	#ifdef MAP
		cout << "Appel au constructeur par défaut de <LogDAO>" << endl;
	#endif
}//----- Fin de LogDAO




//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

