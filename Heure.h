/*************************************************************************
                           Heure  -  Structure représentant une heure
                             -------------------
    début                : 10/01/2017
    copyright            : (C) 2017 Lucas POISSE - Benoît ZHONG
    e-mail               : poisse.lucas@gmail.com
*************************************************************************/

//---------- Interface de la structure <Heure> (fichier Heure.h) ----------------
#if ! defined ( Heure_H )
#define Heure_H

//------------------------------------------------------------------------
// Rôle de la structure <Heure>
//
//	Structure représentant une heure
//------------------------------------------------------------------------

//------------------------------------------------------------------ Types

struct Heure {
	unsigned int h, mn, sec;		// L'heure, la minute et la seconde spécifiée
	
	explicit Heure(unsigned int $h=24, unsigned int $mn = 0, unsigned int $sec=0) : h($h), mn($mn), sec($sec)
	{}		//Constructeur vide
};

//---------------------------------------------------------------- Fonctions associées

//Surcharge de l'opérateur d'affichage d'une heure sur un flux de sortie
ostream & operator << (ostream & out, const Heure & h);

#endif // Heure_H
