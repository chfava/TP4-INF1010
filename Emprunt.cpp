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

ObjetEmpruntable* Emprunt::obtenirObjetEmpruntable() const
{
	return objEmprunt_;
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
Emprunt::Emprunt(std::string matricule, ObjetEmpruntable objetEmpruntable, unsigned int dateRetour) : matricule_(matricule), objEmprunt_(&objetEmpruntable), dateRetour_(dateRetour)
{
}

ObjetEmpruntable* Emprunt::obtenirObjetEmpruntable() const
{
	return objEmprunt_;
}

void Emprunt::modifierObjetEmpruntable(ObjetEmpruntable * objetEmpruntable)
{
	objEmprunt_ = objetEmpruntable;
}

ostream& operator<<(ostream& o, const ObjetEmpruntable& objetEmpruntable) {
	o << objetEmpruntable.obtenirNomClasse() << endl;
};






