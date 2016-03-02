#include <iostream>
#include "Emprunt.h"

using namespace std;


Emprunt::~Emprunt()
{

}

string Emprunt::obtenirMatricule() const
{
	return matricule_;
}



unsigned int Emprunt::obtenirDateRetour() const
{
	return dateRetour_;
}

void Emprunt::modifierMatricule(const string &matricule)
{
	matricule_ = matricule;
}

void Emprunt::modifierDateRetour(unsigned int date)
{
	dateRetour_ = date;
}


/// TP4









