/*************************************************************************
                           Log  -  Classe rassemblant les données d'une ligne de Log
                             -------------------
    début                : 10/01/2017
    copyright            : (C) 2017 Lucas POISSE - Benoît ZHONG
    e-mail               : poisse.lucas@gmail.com
	
	
	<!> L'application ne manipule jamais plus d'UNE instance de cette classe, utilisée pour charger ses données dans la classe GraphData (d'où la relation d'amitié) <!>
*************************************************************************/

//---------- Interface de la classe <Log> (fichier Log.h) ----------------
#if ! defined ( Log_H )
#define Log_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include <string>
#include "Heure.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Log>
//
//	Classe rassemblant les données d'une entrée de Log.
//------------------------------------------------------------------------


class Log
{
//----------------------------------------------------------------- PUBLIC

public:

	friend ostream & operator << (ostream & out, const Log & log);

//----------------------------------------------------- Méthodes publiques (getters)

	string GetReferer() const;
	 // Getter du referer du log
	string GetCible() const;
	 // Getter de la cible du log
	Heure GetHeure() const;
	 // Getter de l'heure du log au format HH:MM:SS
	string GetIP() const;
	 // Getter de l'IP du log
	string GetLogname() const;
	 // Getter du logname du log
	string GetUsername() const;
	 // Getter de l'username du log
	string GetDate() const;
	 // Getter de la date du log au format JJ/Mon/AAAA
	string GetDiffGW() const;
	 // Getter de la différence Greenwich de l'entrée de log
	string GetMethod() const;
	 // Getter de la méthode du log
	unsigned int GetStatus() const;
	 // Getter du statut de la requête cliente
	unsigned int GetDataSize() const;
	 // Getter de la taille des données de la réponse

//----------------------------------------------------- Constructeurs/Destructeur	
	
   Log (string $ref, string $cible, Heure $heure, string $IP, 
   string $logname, string $username, string $date, string $diffGW, 
	string $method, unsigned int $status, unsigned int $dataSize);
    // Mode d'emploi : Constructeur paramétré de Log.
   
   
   Log();
    // Mode d'emploi : Constructeur par défaut de Log.
	
	virtual ~Log();
	//Destructeur de Log(inutile mais permet le tracage des destructeurs)
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

private:			//Attributs privés

	string eraseBeforeChar(string toReturn, string s) const;
								// Fonction supprimant une partie de la chaîne passée en paramètre jusqu'au caractère spécifié
	
	string ref;					//Referer de l'entrée de log
	string cible;				//Cible de l'entrée de log (ressource HTTP de la requête cliente)
	Heure heure;				//Heure de l'entrée de log
	string IP;					//IP de l'entrée de log
	string logname;				//Logname de l'entrée de log
	string username;			//Nom utilisateur de l'entrée de log
	string date;				//Date de l'entrée de log
	string diffGW; 				//Différence Greenwich de l'entrée de log
	string method; 				//Méthode HTTP utilisée de l'entrée de log
	unsigned int status;					//Statut de la réponse HTTP de l'entrée de log
	unsigned int dataSize;				//Taille en octets de la réponse comprise dans l'entrée de log
	
	const string localhost = "http://intranet-if.insa-lyon.fr";	//Le nom de l'hôte du serveur Web
};

//-------------------------------- Autres définitions dépendantes de <Log>

#endif // Log_H

