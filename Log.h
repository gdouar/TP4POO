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

//----------------------------------------------------- Méthodes publiques

   Log (string $ref, string $cible, string $heure, string $IP, 
   string $logname, string $username, string $date, string $diffGW, 
	string $method, int $status, int $dataSize, string $idClient);
    // Mode d'emploi : Constructeur paramétré de Log.
   
   Log();
    // Mode d'emploi : Constructeur par défaut de Log.
	

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

private:			//Attributs privés
	
	string ref;					//Referer de l'entrée de log
	string cible;				//Cible de l'entrée de log (ressource HTTP de la requête cliente)
	string date;				//Date de l'entrée de log
	string heure;				//Heure de l'entrée de log
	string IP;					//IP de l'entrée de log
	string logname;				//Logname de l'entrée de log
	string username;			//Nom utilisateur de l'entrée de log
	string diffGW; 				//Différence Greenwich de l'entrée de log
	string method; 				//Méthode HTTP utilisée de l'entrée de log
	int status;					//Statut de la réponse HTTP de l'entrée de log
	int dataSize;				//Taille en octets de la réponse comprise dans l'entrée de log
	string idClient;			//Identificateur du client navigateur de l'entrée de log
};

//-------------------------------- Autres définitions dépendantes de <Log>

#endif // Log_H

