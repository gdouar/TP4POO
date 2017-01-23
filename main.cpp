/*************************************************************************
						ANALOG - Application C++ d'analyse de logs Apache
                             -------------------
    début                : 10/01/2017
    copyright            : (C) 2017 Lucas POISSE - Benoît ZHONG
    e-mail               : poisse.lucas@gmail.com
*************************************************************************/

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sstream>

//------------------------------------------------------ Include personnel
#include "GraphData.h"
#include "LogDAO.h"
#include "GraphDAO.h"
#include "Log.h"
#include "LogsChecker.h"
#include "Heure.h"

//------------------------------------------------------ Fonctions utilitaires

// Fonction permettant de "parser" une chaîne de caractères à partir d'un délimiteur
// Cette fonction retourne un tableau de chaînes correspondant à chaque "morceau" de la chaîne originale

vector<string> split(const string str, char delimiter) {
  vector<string> tabStr;
  stringstream ss(str); 
  string morceau;
  
  while(getline(ss, morceau, delimiter)) {
    tabStr.push_back(morceau);
  }
  return tabStr;
}

//------------------------------------------------------ Fonction d'analyse des paramètres

//Interprète les commandes de l'utilisateur
int interpreterCmde(int & argc, char* argv[])
{
	bool enleverExtensions = false;
	bool genererGraphe = false;
	Heure sHeure;			//Par défaut, initialisée à 24:00:00 => ignorée par le programme car celui-ci attend une valeur entre 0 et 23
	string heure="";
	string nomFichierGraph;

	if(argc < 2 )				//Au moins 2 arguments sont attendus par le programme
	{
		cerr << endl << "Commande incorrecte : " << endl;
		cerr << "Usage: " << argv[0] << " [options] nomfichier.log" << endl;
		return 1;
	}
	
	for(int i=1; i< argc-1; i++)
	{
		if(strcmp(argv[i], "-e") == 0)		//Activation du filtrage par extension
		{
			enleverExtensions = true;
		}
		else if(strcmp(argv[i], "-t") == 0)		//Gestion du paramètre -t
		{
			if(i+1 < argc-1)
			{

				heure = argv[i+1];
				vector<string> parametresHeure = split(heure,':');			//Parsage du paramètre fourni par l'utilisateur
				if(parametresHeure.size() > 3)					// Si trop précis => refusé
				{
					cout << "Warning : la précision maximale de filtrage est de l'ordre de la seconde. La précision supplémentaire indiquée ne sera pas prise en compte." << endl;
				}
				int hParam, mnParam, secParam;
				stringstream str(parametresHeure[0]);
				str >> hParam;
				if(!str) 					//Formattage de l'heure
				{
					cerr << "Erreur : format de l'heure de filtrage incorrect." << endl;
					return 1;
				}
				if(hParam < 0 || hParam > 23)			//Bornes acceptées de l'heure
				{
					cerr << endl << "Erreur : l'heure doit etre comprise entre 0 et 23." << endl;				
					return 1;
				}
				sHeure.h = hParam;
				if(parametresHeure.size() >=2)
				{
					stringstream str2(parametresHeure[1]);
			
					str2 >> mnParam;
					if(!str2)				//Formattage de la minute
					{
				
						cerr << "Erreur : format de la minute de filtrage incorrect." << endl;
						return 1;
					}
					if(mnParam < 0 || mnParam > 59)		//Bornes acceptées de la minute
					{
						cerr << endl << "Erreur : la minute doit etre comprise entre 0 et 59." << endl;				
						return 1;
					}
					
					sHeure.mn = mnParam;
				}
				if(parametresHeure.size() >= 3)
				{
					stringstream str2(parametresHeure[2]);
					str2 >> secParam;
					if(!str2)					//Formattage de la seconde
					{
						cerr << "Erreur : format de la seconde de filtrage incorrect." << endl;
						return 1;
					}
					if(secParam < 0 || secParam > 59)		//Bornes acceptées de la seconde
					{
						cerr << endl << "Erreur : la seconde doit etre comprise entre 0 et 59." << endl;				
						return 1;
					}
					sHeure.sec = secParam;
				}
				i++;
			}
			else              //Il manque un paramètre
			{		
				cerr << endl <<  "Erreur : -t necessite un parametre supplementaire (heure au format HH:MM:SS)." << endl;
				cerr << "Attention, le dernier paramètre de la commande doit être le fichier de lecture." << endl;
				return 1;
			}	
		}
		else if(strcmp(argv[i], "-g") == 0)		//Génération du graphe
		{
			if(i+1 < argc-1 && ((string(argv[i+1]).substr(0, 1)).compare("-")))
			{
				genererGraphe = true;
				nomFichierGraph = argv[i+1];
				i++;
			}
			else
			{
				cerr << "Erreur : -g necessite un parametre supplementaire (nom du fichier)" << endl;
				return 1;
			}
		}
		
		else        //Paramètres inconnus ignorés
		{
			cout << "Warning : parametre inconnu non pris en compte : " << argv[i] << endl;
		}
	}

	if(enleverExtensions)			//Warnings de filtrage
	{
		cout << endl << "Warning : Images, CSS et Javascript ignorés." << endl;
	}
	
	if(sHeure.h != 24)
	{
		cout << "Warning : Logs compris entre "<< sHeure << " et " << Heure(sHeure.h+1, sHeure.mn, sHeure.sec) << " seulement pris en compte."<<endl;
	}

	string nomFichierLog(argv[argc-1]);
	if(!(nomFichierLog.substr(0,1)).compare("-"))
	{
		cerr << "Erreur : le dernier parametre doit etre le nom de fichier " << endl;
		return 1;
	}
	GraphData gData(enleverExtensions, sHeure);

	LogDAO ldao(nomFichierLog);
	if(ldao.IsReady())
	{
		Log* ld;
		while((ld = ldao.GetNextLog())!=nullptr)
		{
			gData.AddLog(ld);
		}
		if(genererGraphe)
		{
			cout << endl << "Warning : génération de graphe dans le fichier : " << nomFichierGraph  << endl; 
			gData.GenerateGraphViz(nomFichierGraph);
		}
		list<pair<int, string>> results = gData.Get10best();  
		for(list<pair<int,string >>::iterator it = results.begin();it!=results.end();++it)
		{
			cout << (*it).second << " (" << (*it).first << " hit" << (((*it).first >1) ? "s":"") << ")" <<endl;
		}
	}
	return 0;

}

//Test de la surcharge des opérateurs > et >= sur paire
void testSurchargeOpSupPaire()
{
	std::pair<int, int> p1 = make_pair(1,2);
	std::pair<int, int> p2 = make_pair(2,1);
	cout << (p1 > p2) << endl << (p1 >= p2) << endl;
	
}
/*
// Fonction de test de l'utilisation d'un set ordonné par la relation > comportant des pair<int, int>
// Requiert le foncteur Sup_pair_cmp défini dans GraphData.h
void testSetPair()
{
	set<pair<int, int>, Sup_pair_cmp> s1;
	s1.insert(make_pair(1, 4));
	s1.insert(make_pair(0, 6));
	
	cout << s1.begin()->second << endl;
		
}*/


//------------------------------------------------------ Fonctions de tests unitaires des classes métier /fonctions utilitaires

//Test de la fonction de split à partir d'un délimiteur
void testSplitString()
{
	string s = "AA:BB:CC";
	vector<string> v =  split(s, ':');
	for(unsigned int i=0;i<v.size();i++)
	{
		cout << v[i] << endl;
	}
	
}

//Lecture dans le fichier
//Temps de lecture de 100 000 entrées = 5 secondes !
void testChargementLogs()
{
	LogDAO ldao("anonyme.log");
	Log* ld;
	while((ld = ldao.GetNextLog())!=nullptr)
	{
		delete ld;
	}
}

//Méthode de test de la reconnaissance du flag -e
void testIgnoreExtension()
{
	Log* ld2 = new Log("ref", "/fradth.cs/index.html", Heure(11,45,21), "h", "k", "j", "r", "e", "t", 3, 4);
	cout << endl << LogsChecker::CanBeIgnored(ld2);
	delete ld2;
	
	ld2 = new Log("ref", "/fradth.cs/index.js", Heure(11,45,21), "h", "k", "j", "r", "e", "t", 3, 4);
	cout << endl << LogsChecker::CanBeIgnored(ld2);
	delete ld2;
	
	ld2= new Log("ref", "/fradth.cs/index.bmp", Heure(11,45,21), "h", "k", "j", "r", "e", "t", 3, 4); 
	cout << endl << LogsChecker::CanBeIgnored(ld2);
	delete ld2;
	
	ld2= new Log("ref", "/fradth.cs/index.css", Heure(11,45,21), "h", "k", "j", "r", "e", "t", 3, 4); 
	cout << endl << LogsChecker::CanBeIgnored(ld2);
	delete ld2;
	
	ld2= new Log("ref", "/fradth.cs/index.png", Heure(11,45,21), "h", "k", "j", "r", "e", "t", 3, 4); 
	cout << endl << LogsChecker::CanBeIgnored(ld2);
	delete ld2;
}

//Fonction de test de la méthode IsInInterval de la classe Log
void testComprisHoraire()
{
	LogDAO ldao("anonyme.log");
	Log* ld;
	Heure h(11, 0, 0);
	for(int i = 0;i<3;i++)
	{
		 ld=ldao.GetNextLog();
		cout << *ld;
		cout << endl << LogsChecker::IsInInterval(ld, h) << endl;
		delete ld;
	}

}

//Tests affichage d'un log via operator << 
//Tests formatage des cibles et des referers
void testAffichageLogs()
{
	LogDAO ldao("anonyme.log");
	Log* ld = ldao.GetNextLog();
	cout << *ld;
	//cout << endl << ld->CanBeIgnored()<< endl ;
	delete ld;
	
	ld = ldao.GetNextLog();
	cout << *ld;
	//cout << endl << ld->CanBeIgnored()<< endl ;
	delete ld;
	
	ld = new Log("http://tt-rss.org/", "/SiteWebIF/Intranet-etudiant.php", Heure(11,45,21), "127.0.0.1", "-", "-",
				"08/Sep/2012", "+0200", "GET", 200, 12601);
	cout << *ld;
	//cout << endl << ld->CanBeIgnored()<< endl ;
	delete ld;
	
	ld = new Log("http://tt-rss.org/", "/SiteWebIF/Intranet-etudiant.php?ticket=ST-341667-KHlNEzic9e5btb4JQ1Nw-dsi-vm03", Heure(11,45,21), "127.0.0.1", "-", "-",
		"08/Sep/2012", "+0200", "GET", 200, 12601);
	cout << *ld;
	delete ld;
	
}

//Fonction de test de la séparation de caractères
void testSepareChar()
 {
	Log* ld = new Log("http://tt-rss.org/", "/cas/themes/insa/media/favicon.ico;jsessionid=371C6624392DFE7B7B84D27C96EA74C3.dsi-vm04", Heure(11,45,21), "127.0.0.1", "-", "-",
				"08/Sep/2012", "+0200", "GET", 200, 12601);
	cout << (*ld);
	delete ld;
	ld = new Log("http://intranet-if.insa-lyon.fr/cas/themes/insa/media/favicon.ico;jsessionid=371C6624392DFE7B7B84D27C96EA74C3.dsi-vm04", "/cas/themes/insa/media/favicon.ico;jsessionid=371C6624392DFE7B7B84D27C96EA74C3.dsi-vm04", Heure(11,45,21), "127.0.0.1", "-", "-",
				"08/Sep/2012", "+0200", "GET", 200, 12601);	
	cout << (*ld);		
	delete ld;			
				
 }



//Fonction de test de l'injection des données dans la classe de structures optimisées  (WIP...)
void testInitGraphData()
{
	LogDAO ldao("anonyme.log");
	GraphData gData;
	Log* log = nullptr;

	for(int i=0; i<2; i++)
	{
		log = ldao.GetNextLog();
		cout << *(log);
		gData.AddLog(log);
	}
	log = new Log("http://intranet-if.insa-lyon.fr/temps/4IF20.html", "/temps/4IF17.html", Heure(11,45,21), "127.0.0.1", "-", "-",
		"08/Sep/2012", "+0200", "GET", 200, 12601);
	cout << *(log);
	gData.AddLog(log);

	
	log = new Log("http://intranet-if.insa-lyon.fr/temps/4IF20.html", "/temps/4IF17.html", Heure(11,45,21), "127.0.0.1", "-", "-",
		"08/Sep/2012", "+0200", "GET", 200, 12601);
	cout << *(log);
	gData.AddLog(log);
	
	
	list<pair<int, string>> results = gData.Get10best();  
	for(list<pair<int,string >>::iterator it = results.begin();it!=results.end();++it)
	{
		cout << endl << "URL : " << (*it).second << " - Nb hits : " << (*it).first << endl;
	}
	
}


//Test de l'injection des données dans la structure optimisée depuis un fichier de log
void testInitGraphData2()
{
	LogDAO ldao("anonyme.log");
	GraphData gData;
	Log* log = nullptr;
	for(int i=0; i<400; i++)
	{
		log = ldao.GetNextLog();
	//	cout << *(log);
		gData.AddLog(log);
	}
	list<pair<int, string>> results = gData.Get10best();  
	for(list<pair<int,string >>::iterator it = results.begin();it!=results.end();++it)
	{
		cout << endl << "URL : " << (*it).second << " - Nb hits : " << (*it).first << endl;
	}
	
}

//Test du filtrage des cibles en fonction de l'horaire fournie (ici 15h 22mn 13sec)
void testInitGraphDataFiltrageHoraire()
{
	LogDAO ldao("fichierTestsHoraires.log");
	Heure h(15, 22, 13);
	GraphData gData(false, h);
	Log* log = nullptr;
	while((log = ldao.GetNextLog())!=nullptr)
	{
		gData.AddLog(log);			
	}
	
	list<pair<int, string>> results = gData.Get10best();  
	for(list<pair<int,string >>::iterator it = results.begin();it!=results.end();++it)
	{
		cout << endl << "URL : " << (*it).second << " - Nb hits : " << (*it).first << endl;
	}
	
}


//Test du filtrage des cibles en fonction du flag -e
void testInitGraphDataFiltrageExtension()
{
	LogDAO ldao("fichierTestsHoraires.log");
	GraphData gData(true);
	Log* log = nullptr;
	while((log = ldao.GetNextLog())!=nullptr)
	{
		gData.AddLog(log);			
	}
	
	list<pair<int, string>> results = gData.Get10best();  
	for(list<pair<int,string >>::iterator it = results.begin();it!=results.end();++it)
	{
		cout << endl << "URL : " << (*it).second << " - Nb hits : " << (*it).first << endl;
	}
	
}

//Test du filtrage des cibles en fonction des deux options de filtrage simultanées (filtrage des extensions des cibles consultées à 15h 22mn 13sec)
void testInitGraphDataFiltrageBoth()
{
	LogDAO ldao("fichierTestsHoraires.log");
	Heure h(15, 22, 13);
	GraphData gData(true, h);
	Log* log=nullptr;
	while((log = ldao.GetNextLog())!=nullptr)
	{
		gData.AddLog(log);			
	}
	list<pair<int, string>> results = gData.Get10best();  
	for(list<pair<int,string >>::iterator it = results.begin();it!=results.end();++it)
	{
		cout << endl << "URL : " << (*it).second << " - Nb hits : " << (*it).first << endl;
	}
	
}




/*
	Procédure principale, point d'entrée de l'application
*/
int main(int argc, char* argv[])
{
	//testIgnoreExtension();
	//testChargementLog();
	//testAffichageLogs();
	//testSurchargeOpPaire();
	//return chargerIHM(argc, argv);
	//testSetPair();
	//testComprisHoraire();
	// testInitGraphData();
	// testInitGraphData2();
	//testInitGraphDataFiltrageHoraire();
	//testInitGraphDataFiltrageExtension();
	//testInitGraphDataFiltrageBoth();
	//testSepareChar();
	//testSplitString();
	return interpreterCmde(argc, argv);
}
