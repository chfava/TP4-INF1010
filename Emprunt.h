#ifndef EMPRUNT_H
#define EMPRUNT_H

#include <string>
#include "Livre.h"
#include "Dvd.h"
#include "Abonne.h"

class Emprunt : public ObjetEmpruntable
{
public:
	~Emprunt();

	std::string obtenirMatricule() const;
	unsigned int obtenirDateRetour() const;
	

	void modifierMatricule(const std::string& matricule);
	void modifierDateRetour(unsigned int date);
	


	/// _____ TP4 _____
	Emprunt(std::string matricule, ObjetEmpruntable objetEmpruntable, unsigned int dateRetour);
	ObjetEmpruntable* obtenirObjetEmpruntable() const;
	void modifierObjetEmpruntable(ObjetEmpruntable* objetEmpruntable);
	friend ostream& operator<<(ostream& o, ObjetEmpruntable objetEmpruntable);



private:
	std::string matricule_;
	unsigned int dateRetour_;

	/// _____ TP4 _____
	ObjetEmpruntable* objEmprunt_;

};

#endif