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
//------------------------------------------------------ Include personnel
#include "Log.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Log::Log (string $ref, string $cible, string $heure, string $IP, 
string $logname, string $username, string $date, string $diffGW, 
string $method, int $status, int $dataSize, string $idClient):
ref($ref), cible($cible), heure($heure), IP($IP), logname($logname),
username($username), date($date), diffGW($diffGW), method($method),
status($status), dataSize($dataSize), idClient($idClient)
{
	#ifdef MAP
		cout << "Appel au constructeur paramétré de <Log>" << endl;
	#endif
}//------ Fin de Log

Log::Log ()

{
	ref=cible=date=heure=IP=logname=username=diffGW=method=idClient="";
	status=dataSize=0;
	
	#ifdef MAP
		cout << "Appel au constructeur par défaut de <Log>" << endl;
	#endif

} //----- Fin de Log



//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

