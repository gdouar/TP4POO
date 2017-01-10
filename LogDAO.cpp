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
#include <vector>
//------------------------------------------------------ Include personnel
#include "Log.h"
#include "LogDAO.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Log* LogDAO::getNextLog()
{
	
	vector<string> v = {"a","b","c","d","e","f","12/12/2012","h","i","j"};
	
	return new Log(v[0], v[1], v[2],v[3], v[4], v[5],v[6], v[7], v[8],1,200, v[9] );
}//----- Fin de getNextLog

LogDAO::LogDAO (string $filename) : filename($filename)
{
	#ifdef MAP
		cout << "Appel au constructeur paramétré de <LogDAO>" << endl;
	#endif
}//----- Fin de LogDAO


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

