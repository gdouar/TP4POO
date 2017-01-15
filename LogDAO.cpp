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
#include <sstream>
#include <iterator>

//------------------------------------------------------ Include personnel
#include "Log.h"
#include "LogDAO.h"

//-------------------- Déclarations
void split(const string& str, vector<string>& cont);

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Log* LogDAO::GetNextLog()
{
	if(is)
	{
		string log;
		if(getline(is, log))
		{
			vector<string> words;
			split(log, words);
		 
			if(words.size() >=  10)
			{
				words[3] = 	words[3].substr(1, words[3].size());
				string jour	= words[3].substr(0,10);		//Infos date
				string horaire = words[3].substr(12,8);				
				words[4] = words[4].substr(0, words[4].size()-1);	//Différence Greenwich
				words[5].erase(0, 1);		//Méthode HTTP
				words[10] = words[10].substr(1, words[10].size()-2);		//Referer
				int status;
				int datasize;
				
				istringstream ((words[8])) >> status;
				istringstream ((words[9])) >> datasize;
				Log* l = new Log(words[10], words[6], horaire, words[0], words[1], words[2], jour, words[4], words[5], status, datasize);
				return l;
			}
		}
	}

	return nullptr;

}//----- Fin de getNextLog

LogDAO::LogDAO (string $filename) : filename($filename)
{
	
	is.open(filename);
	if (!is.is_open())
		cout << "Erreur à l'ouverture du fichier";
	
	#ifdef MAP
		cout << "Appel au constructeur paramétré de <LogDAO>" << endl;
	#endif
}//----- Fin de LogDAO


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void split(const string& str, vector<string>& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}
