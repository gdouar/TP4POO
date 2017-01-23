/*************************************************************************
                           Heure  -  Structure représentant une heure
                             -------------------
    début                : 10/01/2017
    copyright            : (C) 2017 Lucas POISSE - Benoît ZHONG
    e-mail               : poisse.lucas@gmail.com
*************************************************************************/

//---------- Réalisation des fonctions associées à <Heure> (fichier Heure.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <string>
#include <iostream>
//------------------------------------------------------ Include personnel
#include "Heure.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------- Fonctions (surcharges des opérateurs)

ostream & operator << (ostream & out, const Heure & h)
{
	out << (h.h<10 ? "0" : "") << h.h << ":" << (h.mn<10 ? "0" : "") << h.mn << ":" << (h.sec<10 ? "0" : "") << h.sec;
	return out;
	
}// ------ Fin de operator <<
