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
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques

set<string> LogsChecker::ignored_extensions = {"jpeg", "png", "js", "css", "bmp", "gif", "ani", "cal",
									   "fax", "img", "jbg", "jpe", "jpg", "mac", "pbm", "tga", "ico"};
								
									   
bool LogsChecker::IsInInterval(Log * l, const unsigned int h)
{
	unsigned int hLog;
	istringstream ((l->GetHeure()).substr(0, 2)) >> hLog;
	return hLog==h;
	
}// -------- Fin de IsInInterval

									  
bool LogsChecker::CanBeIgnored(Log * l)  
{
	std::string c = l->GetCible();
	std::string ext = c.substr(c.find_last_of(".")+1, c.size()); 
	return (ignored_extensions.find(ext) != ignored_extensions.end());
	
	
} //---------- Fin de IsWebContentOrImage
