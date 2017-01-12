#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "GraphData.h"
#include "LogDAO.h"
#include "GraphDAO.h"
#include "Log.h"

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
}

//Test de la surcharge des opérateurs > et >= sur paire
void testSurchargeOpInfPaire()
{
	std::pair<int, int> p1 = make_pair(1,2);
	std::pair<int, int> p2 = make_pair(2,1);
	cout << (p1 > p2) << endl << (p1 >= p2) << endl;
	
}


//Affichage d'un log via operator << 
void testAffichageLogs()
{
	LogDAO ldao("testlog.log");
	Log* ld = ldao.getNextLog();
	cout << (*ld);
	delete ld;
	
}




int main(int argc, char* argv[])
{
	//testAffichageLogs();
	//testSurchargeOpInfPaire();
	return chargerIHM(argc, argv);

}