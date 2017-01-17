/*************************************************************************
                           LogsChecker  -  Classe analysant un objet Log par rapport aux arguments de lancement du programme principal
                             -------------------
    début                : 10/01/2017
    copyright            : (C) 2017 Lucas POISSE - Benoît ZHONG
    e-mail               : poisse.lucas@gmail.com
	
*************************************************************************/

//---------- Interface de la classe <LogsChecker> (fichier LogsChecker.h) ----------------
#if ! defined ( LogsChecker_H )
#define LogsChecker_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include <set>
#include "Log.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <LogsChecker>
//
//	Classe analysant un objet Log par rapport aux arguments de lancement du programme principal
//------------------------------------------------------------------------


class LogsChecker
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques
	static bool CanBeIgnored(Log * l); 
	//Méthode renvoyant vrai si le log ne doit pas être considéré par le flag -e

	static bool IsInInterval(Log * l, const unsigned int h);
	//Méthode renvoyant vrai si le log est situé dans la tranche horaire [heure, heure+1[

private :
	static set<string> ignored_extensions;		//Tableau statique des extensions ignorées par -e
};

//-------------------------------- Autres définitions dépendantes de <LogsChecker>

#endif // LogsChecker_H

