#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "GraphData.h"
#include "LogDAO.h"
#include "GraphDAO.h"
#include "Log.h"
#include "LogsChecker.h"
/*
//Affiche l'interface utilisateur
int chargerIHM(int & argc, char* argv)
{
	bool enleverExtensions = false;
	int heure;
	string nomFichierGraph;
	string nomFichierLog;

	if(argc < 2)
	{
		cerr << "Usage: " << argv[0] << " [options] nomfichier.log" << endl;
		return 1;
	}

	for(int i=1; i< argc-1; i++)
	{
		//cout << argv[i] << endl;
		if(strcmp(argv[i], "-e") == 0)
		{
			enleverExtensions = true;
			cout << "Images, CSS et Javascript files ignorés." << endl;
		}
		else if(strcmp(argv[i], "-t") == 0)
		{
			if(i+1 < argc-1)
			{
				heure = atoi(argv[i+1]);
				if(heure < 0 || heure > 23)
				{
					cerr << "Heure doit être compris entre 0 et 23." << endl;
					return 1;
				}
				i++;
				cout << "Heure comprise entre "<< heure << "h et " << heure+1 << "h."<<endl;
			}
			else
			{
				cerr << "-t nécessite un paramètre supplémentaire (heure)" << endl;
				return 1;
			}
			
		}
		else if(strcmp(argv[i], "-g") == 0)
		{
			if(i+1 < argc-1)
			{
				nomFichierGraph = argv[i+1];
				i++;
			}
			else
			{
				cerr << "-g nécessite un paramètre supplémentaire (nom du fichier)" << endl;
				return 1;
			}
		}
		else
		{
			cerr << "Paramètre inconnu : " << argv[i] << endl;
		}
	}

	nomFichierLog = argv[argc-1];
	return 0;
}*/

//Test de la surcharge des opérateurs > et >= sur paire
void testSurchargeOpSupPaire()
{
	std::pair<int, int> p1 = make_pair(1,2);
	std::pair<int, int> p2 = make_pair(2,1);
	cout << (p1 > p2) << endl << (p1 >= p2) << endl;
	
}

// Fonction de test de l'utilisation d'un set ordonné par la relation > comportant des pair<int, int>
// Requiert le foncteur Sup_pair_cmp défini dans GraphData.h
void testSetPair()
{
	/*set<pair<int, int>, Sup_pair_cmp> s1;
	s1.insert(make_pair(1, 4));
	s1.insert(make_pair(0, 6));
	
	cout << s1.begin()->second << endl;*/
		
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
	Log* ld2 = new Log("ref", "/fradth.cs/index.html", "y", "h", "k", "j", "r", "e", "t", 3, 4);
	cout << endl << LogsChecker::CanBeIgnored(ld2);
	delete ld2;
	
	ld2 = new Log("ref", "/fradth.cs/index.js", "y", "h", "k", "j", "r", "e", "t", 3, 4);
	cout << endl << LogsChecker::CanBeIgnored(ld2);
	delete ld2;
	
	ld2= new Log("ref", "/fradth.cs/index.bmp", "y", "h", "k", "j", "r", "e", "t", 3, 4); 
	cout << endl << LogsChecker::CanBeIgnored(ld2);
	delete ld2;
	
	ld2= new Log("ref", "/fradth.cs/index.css", "y", "h", "k", "j", "r", "e", "t", 3, 4); 
	cout << endl << LogsChecker::CanBeIgnored(ld2);
	delete ld2;
	
	ld2= new Log("ref", "/fradth.cs/index.png", "y", "h", "k", "j", "r", "e", "t", 3, 4); 
	cout << endl << LogsChecker::CanBeIgnored(ld2);
	delete ld2;
}

//Fonction de test de la méthode IsInInterval de la classe Log
void testComprisHoraire()
{
	LogDAO ldao("anonyme.log");
	Log* ld;
	for(int i = 0;i<3;i++)
	{
		 ld=ldao.GetNextLog();
		cout << *ld;
		cout << endl << LogsChecker::IsInInterval(ld, 11) << endl;
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
	
	ld = new Log("http://tt-rss.org/", "/SiteWebIF/Intranet-etudiant.php", "11:45:21", "127.0.0.1", "-", "-",
				"08/Sep/2012", "+0200", "GET", 200, 12601);
	cout << *ld;
	//cout << endl << ld->CanBeIgnored()<< endl ;
	delete ld;
	
	ld = new Log("http://tt-rss.org/", "/SiteWebIF/Intranet-etudiant.php?ticket=ST-341667-KHlNEzic9e5btb4JQ1Nw-dsi-vm03", "11:45:21", "127.0.0.1", "-", "-",
		"08/Sep/2012", "+0200", "GET", 200, 12601);
	cout << *ld;
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
	log = new Log("http://intranet-if.insa-lyon.fr/temps/4IF20.html", "/temps/4IF17.html", "11:45:21", "127.0.0.1", "-", "-",
		"08/Sep/2012", "+0200", "GET", 200, 12601);
	cout << *(log);
	gData.AddLog(log);

	
	log = new Log("http://intranet-if.insa-lyon.fr/temps/4IF20.html", "/temps/4IF17.html", "11:45:21", "127.0.0.1", "-", "-",
		"08/Sep/2012", "+0200", "GET", 200, 12601);
	cout << *(log);
	gData.AddLog(log);
	
	
	list<pair<int, string>> results = gData.get10best();  
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
	list<pair<int, string>> results = gData.get10best();  
	for(list<pair<int,string >>::iterator it = results.begin();it!=results.end();++it)
	{
		cout << endl << "URL : " << (*it).second << " - Nb hits : " << (*it).first << endl;
	}
	
}

//Test du filtrage des cibles en fonction de l'horaire fournie (ici 11h)
void testInitGraphDataFiltrageHoraire()
{
	LogDAO ldao("anonyme.log");
	GraphData gData(false, 11);
	Log* log = nullptr;
	for(int i=0; i<400; i++)
	{
		log = ldao.GetNextLog();
		gData.AddLog(log);			
	}
	list<pair<int, string>> results = gData.get10best();  
	for(list<pair<int,string >>::iterator it = results.begin();it!=results.end();++it)
	{
		cout << endl << "URL : " << (*it).second << " - Nb hits : " << (*it).first << endl;
	}
	
}


//Test du filtrage des cibles en fonction du flag -e
void testInitGraphDataFiltrageExtension()
{
	LogDAO ldao("anonyme.log");
	GraphData gData(true);
	Log* log = nullptr;
	for(int i=0; i<400; i++)
	{
		log = ldao.GetNextLog();
		gData.AddLog(log);			
	}
	list<pair<int, string>> results = gData.get10best();  
	for(list<pair<int,string >>::iterator it = results.begin();it!=results.end();++it)
	{
		cout << endl << "URL : " << (*it).second << " - Nb hits : " << (*it).first << endl;
	}
	
}

//Test du filtrage des cibles en fonction des deux options de filtrage simultanées (filtrage des extensions des cibles consultées à 11hXX)
void testInitGraphDataFiltrageBoth()
{
	LogDAO ldao("filterFile.log");
	GraphData gData(true, 11);
	Log* log=nullptr;
	while((log = ldao.GetNextLog())!=nullptr)
	{
		gData.AddLog(log);			
	}
	list<pair<int, string>> results = gData.get10best();  
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
	testInitGraphDataFiltrageBoth();
	return 0;
}