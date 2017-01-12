/*************************************************************************
                           Log  -  Classe rassemblant les données des Logs
                             -------------------
    début                : 10/01/2017
    copyright            : (C) 2017 Lucas POISSE - Benoît ZHONG
    e-mail               : poisse.lucas@gmail.com
*************************************************************************/

//---------- Réalisation de la classe <Log> (fichier Log.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <string>
#include <iostream>
#include <sstream>
//------------------------------------------------------ Include personnel
#include "Log.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques

set<string> Log::ignored_extensions = {"jpeg", "png", "js", "css", "bmp", "gif", "ani", "cal",
									   "fax", "img", "jbg", "jpe", "jpg", "mac", "pbm", "tga"};

bool Log::CanBeIgnored() const 
{
	
	std::string ext = cible.substr(cible.find_last_of(".")+1, cible.size()); 
	return (ignored_extensions.find(ext) != ignored_extensions.end());
	
	
} //---------- Fin de IsWebContentOrImage
		

Log::Log (string $ref, string $cible, string $heure, string $IP, 
string $logname, string $username, string $date, string $diffGW, 
string $method, int $status, int $dataSize):
ref($ref), cible($cible), heure($heure), IP($IP), logname($logname),
username($username), date($date), diffGW($diffGW), method($method),
status($status), dataSize($dataSize)
{
	#ifdef MAP
		cout << "Appel au constructeur paramétré de <Log>" << endl;
	#endif
}//------ Fin de Log

Log::Log ()

{
	ref=cible=date=heure=IP=logname=username=diffGW=method="";
	status=dataSize=0;
	
	#ifdef MAP
		cout << "Appel au constructeur par défaut de <Log>" << endl;
	#endif

} //----- Fin de Log


ostream & operator << (ostream & out, const Log & log)
{
	std::ostringstream stm;
	
	out << "*** LOG *** \n Referer: " + log.ref + "\n Cible : " + log.cible + "\n Date : " + log.date 
	+ "\n Heure : " + log.heure+"\n IP : " + log.IP + "\n Logname : " + log.logname + "\n Username : " + log.username
	+ "\n Greenwich diff :" + log.diffGW + "\n Method : " + log.method + "\n Status : ";
	stm << log.status;
	out << stm.str() + "\n Data Size :";
	stm.str(std::string());
	stm << log.dataSize;
	out << stm.str();
	
	return out;
} // Fin de operator <<

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

