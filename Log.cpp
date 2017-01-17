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


string Log::GetReferer() const
{
	return ref;
}//----- Fin de GetReferer


string Log::GetCible() const
{
	return cible;
}//----- Fin de GetCible

string Log::GetHeure() const
{
	return heure;
}//----- Fin de GetHeure

string Log::GetIP() const
{
	return IP;
}//----- Fin de GetIP

string Log::GetLogname() const
{
	return logname;
}//----- Fin de GetLogname

string Log::GetUsername() const
{
	return username;
}//----- Fin de GetUsername

string Log::GetDate() const
{
	return date;
}//----- Fin de GetDate

string Log::GetDiffGW() const
{
	return diffGW;
}//----- Fin de GetDiffGW

string Log::GetMethod() const
{
	return method;
}//----- Fin de GetMethod

unsigned int Log::GetStatus() const
{
	return status;
}//----- Fin de GetStatus

unsigned int Log::GetDataSize() const
{
	return dataSize;
}//----- Fin de GetDataSize

		
Log::Log (string $ref, string $cible, string $heure, string $IP, 
string $logname, string $username, string $date, string $diffGW, 
string $method, unsigned int $status, unsigned int $dataSize):
ref($ref), heure($heure), IP($IP), logname($logname),
username($username), date($date), diffGW($diffGW), method($method),
status($status), dataSize($dataSize)
{
	if($ref != "-")
	{
		if($ref.find(localhost)!=string::npos)
		{
			ref = $ref.substr(31, $ref.size());
		}
		else
		{
			string sansProtocole = $ref.substr($ref.find("//")+2, $ref.size());
			ref = sansProtocole.substr(0, sansProtocole.find("/"));
		}
		ref = (ref.back() == '/') ? ref.substr(0, ref.size()-1) : ref;
	}
	
	cible = $cible;
	unsigned int positionParams=$cible.find("?");
	if(positionParams!=string::npos)
	{
		cible = cible.substr(0, positionParams);
	}
	cible = (cible.back() == '/') ? cible.substr(0, cible.size()-1) : cible;
	
	
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

Log::~Log()
{
	#ifdef MAP
		cout << "Appel au destructeur de <Log>" << endl;
	#endif
}

ostream & operator << (ostream & out, const Log & log)
{
	std::ostringstream stm;
	
	out << endl << "*** LOG *** \n Referer: " + log.ref + "\n Cible : " + log.cible + "\n Date : " + log.date 
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

