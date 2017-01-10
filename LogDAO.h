/*************************************************************************
                           LogDAO  -  Classe lisant dans le fichier pour instancier un objet LOG
                             -------------------
    début                : 10/01/2017
    copyright            : (C) 2017 Lucas POISSE - Benoît ZHONG
    e-mail               : poisse.lucas@gmail.com
	
*************************************************************************/

//---------- Interface de la classe <LogDAO> (fichier LogDAO.h) ----------------
#if ! defined ( LogDAO_H )
#define LogDAO_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <fstream>
#include <string>
#include "Log.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <LogDAO>
//
//	Classe lisant dans le fichier pour instancier un objet LOG
//------------------------------------------------------------------------

class LogDAO
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques
   LogDAO(string filename="");
    // Mode d'emploi : Constructeur par défaut de LogDAO.
	
	Log* getNextLog();
	//Méthode renvoyant un nouvel objet LOG (dont les données sont envoyées à la classe GraphData) à partir d'une ligne de fichier

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

private:			//Attributs privés

	ifstream is;	//Le flux d'entrée sur lequel lire les logs (par défaut cin)
	string filename;
};

//-------------------------------- Autres définitions dépendantes de <LogDAO>

#endif // LogDAO_H

