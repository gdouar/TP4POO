/*************************************************************************
                           LogsChecker  -  Classe rassemblant les données des Logs
                             -------------------
    début                : 10/01/2017
    copyright            : (C) 2017 Lucas POISSE - Benoît ZHONG
    e-mail               : poisse.lucas@gmail.com
*************************************************************************/

//---------- Réalisation de la classe <LogsChecker> (fichier LogsChecker.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <string>
#include <sstream>
//------------------------------------------------------ Include personnel
#include "LogsChecker.h"
#include "Log.h"
#include "Heure.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques

set<string> LogsChecker::ignored_extensions = {"jpeg", "png", "js", "css", "bmp", "gif", "ani", "cal",
									   "fax", "img", "jbg", "jpe", "jpg", "mac", "pbm", "tga", "ico"};
								
						
bool LogsChecker::IsInInterval(Log * l, const Heure h)
{
	if((l->GetHeure()).h == h.h)
	{
		if((l->GetHeure()).mn == h.mn)
		{
			return ((l->GetHeure().sec) >= h.sec);		//Même heure et minute => différence sur les secondes
		}
		return ((l->GetHeure().mn) > h.mn);		// Même heure => différence sur les minutes
	}
	else if((l->GetHeure()).h == (h.h)+1)		//Une heure de décalage en avant => différence sur les minutes ou les secondes
	{
		if((l->GetHeure()).mn == h.mn)
		{
			return ((l->GetHeure().sec) < h.sec);		//Même minute avec une heure en avant => différence sur les secondes
		}
		return ((l->GetHeure().mn) < h.mn);		//  Différence sur les minutes
	}
	else {
		return false;
	}
	
}// -------- Fin de IsInInterval

									  
bool LogsChecker::CanBeIgnored(Log * l)  
{
	std::string c = l->GetCible();
	std::string ext = c.substr(c.find_last_of(".")+1, c.size()); 
	return (ignored_extensions.find(ext) != ignored_extensions.end());
	
	
} //---------- Fin de IsWebContentOrImage
