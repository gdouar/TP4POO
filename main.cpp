#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "GraphData.h"
#include "LogDAO.h"
#include "GraphDAO.h"
#include "Log.h"
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
	set<pair<int, int>, Sup_pair_cmp> s1;
	s1.insert(make_pair(1, 4));
	s1.insert(make_pair(0, 6));
	
	cout << s1.begin()->second << endl;
		
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
	cout << endl << ld2->CanBeIgnored();
	delete ld2;
	
	ld2 = new Log("ref", "/fradth.cs/index.js", "y", "h", "k", "j", "r", "e", "t", 3, 4);
	cout << endl << ld2->CanBeIgnored();
	delete ld2;
	
	ld2= new Log("ref", "/fradth.cs/index.bmp", "y", "h", "k", "j", "r", "e", "t", 3, 4); 
	cout << endl << ld2->CanBeIgnored();
	delete ld2;
	
	ld2= new Log("ref", "/fradth.cs/index.css", "y", "h", "k", "j", "r", "e", "t", 3, 4); 
	cout << endl << ld2->CanBeIgnored();
	delete ld2;
	
	ld2= new Log("ref", "/fradth.cs/index.png", "y", "h", "k", "j", "r", "e", "t", 3, 4); 
	cout << endl << ld2->CanBeIgnored();
	delete ld2;
}

//Affichage d'un log via operator << 
void testAffichageLogs()
{
	LogDAO ldao("anonyme.log");
	Log* ld = ldao.GetNextLog();
	cout << *ld;
	cout << endl << ld->CanBeIgnored();
	delete ld;
}

//Fonction de test de l'injection des données dans la classe de structures optimisées  (WIP...)
void testInitGraphData()
{
	
}


/*
	Procédure principale, point d'entrée de l'application
*/
int main(int argc, char* argv[])
{
	//testIgnoreExtension();
	//testChargementLog();
	//testAffichageLogs();
	//testSurchargeOpSupPaire();
	//return chargerIHM(argc, argv);
	testSetPair();
	return 0;
}