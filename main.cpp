using namespace std;
#include <iostream>
#include <stdlib>
#include <string>

int main(int argc, char* argv[])
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

	for(int i=1; i< argc; i++)
	{
		if(argv[i] == "-e")
		{
			enleverExtensions = true;
		}
		else if(argv[i] == "-t")
		{
			if(i+1 < argc)
			{
				heure = atoi(argv[i+1]);
				i++;
			}
			else
			{
				cerr << "-t nécessite un paramètre supplémentaire (heure)" << endl;
			}
			
		}
		else if(argv[i] == "-g")
		{
			nomFichierGraph = str(argv[i+1]);
			i++;
		}
		else
		{
			nomFichierLog = str(arg[i]);
		}
	}

	return 0;
}